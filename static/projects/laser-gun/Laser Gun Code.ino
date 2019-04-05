/**
 * Laser gun component of HCDE 439 laser tag final project.
 * 
 * The laser gun has the following features:
 *  - Fire (trigger) button fires the infrared LEDs at another player's vest
 *  - Firing mode button, switches between single and burst fire
 *  - Fire LED, lighting up while shooting
 *  - Ammo indicator LED, lighting up when needing to reload
 *  - Tilt sensor, used to initiate a reload when tilted for 2 seconds
 *  - Hall effect sensor, used to identify charging with the charging station
 *  - Piezo buzzer, used to make sound when shooting
 *  - xBee module for communicating with other devices (command center, vest, charging station)
 * 
 * The gun has an amount of ammo and an amount of charge. The player can reload to
 * max ammo as long as the gun has charge. If the gun is out of charge, it must be
 * recharged at the charging station by lining up its magnet and hall sensor with 
 * those of the charging station.
 *  
 * This project samples from the following code:
 *  - ButtonLib by Andy Davidson, providing a Button object with debouncing
 *    http://blogs.uw.edu/fizzlab/technology/libraries/buttonlib
 *  - xBee send/receive example by Blake Tsuzaki
 *    https://github.com/HCDE439/ArduinoXBeeSendReceive-Example
 *  - Adafruit's IR LED/receiver tutorial
 *    https://learn.adafruit.com/ir-sensor/making-an-intervalometer
 */

#include "Wire.h"
#include <LiquidTWI.h> // LCD interface activation
#include <SoftwareSerial.h>
#include <Button.h>

const int XBEE_TX_PIN = 2;
const int XBEE_RX_PIN = 3;
const int IR_LED_PIN = 4;
const int TILT_SENSOR_PIN = 5;
const int HALL_SENSOR_PIN = 6;
const int FIRE_LED_PIN = 7;
const int NO_AMMO_LED_PIN = 8;
const int MODE_BUTTON_PIN = 9;
const int FIRE_BUTTON_PIN = 10;
const int BUZZER_PIN = 11;

const int MAX_AMMO = 10;
const int MAX_CHARGE = 2;
const int CHARGE_TIME = 5000;
const int TEMPORARY_SCREEN_MESSAGE_TIME = 3000;
const int HIT_STUN_TIME = 1000;
const int RELOAD_TILT_TIME = 2000;

int player = 1;
int ammo = MAX_AMMO;
int charge = MAX_CHARGE;
int temporaryScreenDuration = TEMPORARY_SCREEN_MESSAGE_TIME;
bool gameRunning = true;
bool charging = false;
bool externalCharging = false;
bool validCharge = false;
bool reloading = false;
bool burstFire = false;
bool recentlyHit = false;
bool screenMessageTemporary = false;
String buff;
String pString;
unsigned long reloadTime = 0;
unsigned long magnetDetectTime = 0;
unsigned long newScreenMessageTime = 0;
unsigned long playerHitTime = 0;

LiquidTWI lcd(0);
SoftwareSerial xBee(XBEE_TX_PIN, XBEE_RX_PIN);
Button fireButton(FIRE_BUTTON_PIN, INPUT_PULLUP);
Button modeButton(MODE_BUTTON_PIN, INPUT_PULLUP);

/**
 * Sets up the gun's software and hardware components.
 */
void setup() {
  // activate serial monitor for trouble shooting and xBee
  Serial.begin(9600);
  xBee.begin(9600);
  // set up the LCD
  lcd.begin(16, 2);
  lcd.print("Infra-Raid");
  // activate laser gun components
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(FIRE_LED_PIN, OUTPUT);
  pinMode(NO_AMMO_LED_PIN, OUTPUT);
  pinMode(HALL_SENSOR_PIN, INPUT);
  pinMode(TILT_SENSOR_PIN, INPUT_PULLUP);
  buff = "";
  String p = "p";
  pString = p + player;
  delay(3000);
  // show game info after a few seconds
  if (gameRunning) {
    setHUD();
  }
  Serial.println("Starting");
}

/**
 * Core game logic. Always handle radio input, then if in game and not stunned (hit by other player),
 * handle input actions from firing mode button, fire button, tilt sensor (reload) and hall sensor (charge).
 */
void loop() {
  handleRadioInput();
  if (gameRunning) {
    handleTemporaryScreenMessage();
    if (!isStunned()) {
      handleFiringMode();
      if (ammo > 0) {
        handleFire();
      }
      handleCharging();
      if (!charging && ammo < MAX_AMMO) {
        handleReload();
      }
    }
  }
}

/**
 * Handles xBee input from command center and other devices.
 * Currently handles some messages that are not implemented across the game,
 * such as game over and game begin.
 * 
 * xBee handling skeleton courtesy of Blake Tsuzaki
 * https://github.com/HCDE439/ArduinoXBeeSendReceive-Example
 */
void handleRadioInput() {
  if (xBee.available() > 0) {
    char c = xBee.read();
    Serial.println(c);
    if (isAlphaNumeric(c) || c == ' ') {
      buff = buff + c;
    } else {
      Serial.print("Received message: ");
      Serial.println(buff);
      // Check the message for keywords
      if (buff.equals(pString + " hit")) {
        handlePlayerHitMessage(); // for use in multiple gun game
      } else if (buff.equals(pString + " charging")) {
        handleChargingMessage();
      } else if (buff.equals(pString + " charged")) {
        handleChargedMessage();
      } else if (buff.equals("Game over")) {
        handleGameOverMessage();
      } else if (buff.equals("Game begin")) {
        handleGameBeginMessage();
      }
      buff = "";
    }
  }
}

/**
 * Checks if the fire button is clicked and fires the IR LED according to
 * firing mode, deplenishing ammo appropriately.
 */
void handleFire() {
  if (fireButton.checkButtonAction() == Button::CLICKED) {
    if (burstFire) {
      // limit to `ammo` shots if fewer than 3 remain
      int shots = min(ammo, 3);
      for (int i = 0; i < shots; i++) {
        fire(25); // 3x 25ms flash for red firing indicator LED
      }
    } else {
      fire(100); // 100ms flash for red firing indicator LED
    }
    setHUD();
  }
}

/**
 * Checks if the tilt sensor is tilted and if it has been tilted for two seconds,
 * and if so, initiates a reload (ammo = max, charge--) if enough charge.
 */
void handleReload() {
  bool tilted = (digitalRead(TILT_SENSOR_PIN) == HIGH);
  if (tilted) {
    if (!reloading) { // first detect of the current tilt
      reloading = true;
      reloadTime = millis();
      Serial.println("started reloading");
    } else { // already tilted, check if tilted for long enough (2 seconds)
      if ((millis() - reloadTime) > RELOAD_TILT_TIME) {
        lcd.clear();
        if (charge > 0) {
          ammo = MAX_AMMO;
          charge--;
          Serial.println("reloaded");
          xBee.print(pString);
          xBee.println(" reloaded");
          lcd.print("Reloaded");
          lcd.setCursor(0, 1);
          lcd.print("Charge: ");
          lcd.print(charge);
        } else {
          Serial.println("not enough charge");
          lcd.print("Out of charge!");
        }
        setCurrentScreenTemporary(TEMPORARY_SCREEN_MESSAGE_TIME);
        reloading = false;
      }
    }
  } else {
    reloading = false;
  }
}

/**
 * Checks if the hall sensor detects a magnet and sets a boolean to the result.
 * The magnet must be present in order for the gun to replenish charge when receiving
 * 'charging' and 'charged' messages from the gun. This current code only works in
 * a one-gun, one-station setup.
 * 
 * The commented out code is designed for a multiple-gun setup in which the command
 * center is responsible for identifying which gun is being charged at the charging
 * station by linking the reported 'charged'/'charging' messages from the gun and
 * station and verifying that they occur at the same time, reporting the result of
 * the charge back to the gun. This approach would prevent users from cheating by
 * placing extra magnets against the gun and charging station.
 * 
 * We supplied the commented out code to the charging station for use with their sensor,
 * and a future user could uncomment and modify it slightly to allow the gun to charge
 * without the use of xBees in the game.
 */
void handleCharging() {
  charging = (digitalRead(HALL_SENSOR_PIN) == LOW);
  if (charging) {
    Serial.println("charging");
  }
//  bool magnetPresent = (digitalRead(HALL_SENSOR_PIN) == LOW);
//  if (magnetPresent) {
//    if (!charging) {
//      // identify start of charge
//      charging = true;
//      magnetDetectTime = millis();
//      xBee.print(pString);
//      xBee.println(" charging");
//      Serial.println("started charging");
//    } else {
//      // identify charging for long enough
//      if ((millis() - magnetDetectTime) > CHARGE_TIME) {
//        xBee.print(pString);
//        xBee.println(" charged");
//        Serial.println("charged");
//        charging = false;
//      }
//    }
//  } else {
//    if (charging) {
//      charging = false;
//      setHUD();
//    }
//  }
}

/**
 * Checks if the firing mode button has been clicked and sets the mode to
 * single or burst fire, flipping it from whatever it currently is.
 */
void handleFiringMode() {
  if (modeButton.checkButtonAction() == Button::CLICKED) {
    burstFire = !burstFire;
    setHUD();
  }
}

/**
 * Updates the LCD to the heads-up display that is typically shown, displaying
 * how much ammo remains and what the current firing mode is. If the gun is out
 * of ammo or charge, warning information messages are shown instead.
 * 
 * This function is called by most other functions (fire, firing mode, etc.) to
 * update the LCD only when necessary.
 */
void setHUD() {
  lcd.clear();
  if (ammo > 0) {
    digitalWrite(NO_AMMO_LED_PIN, LOW);
    lcd.print("Mode: ");
    lcd.print(burstFire ? "burst" : "single");
    lcd.setCursor(0, 1);
    lcd.print("Ammo: ");
    lcd.print(ammo);
  } else {
    digitalWrite(NO_AMMO_LED_PIN, HIGH);
    if (charge > 0) {
      lcd.print("No ammo");
      lcd.setCursor(0, 1);
      lcd.print("Must reload");
    } else {
      lcd.print("Must charge");      
    }
  }
}

/**
 * Checks if the gun was recently hit and resets it to "un-stunned" after enough time.
 * 
 * This function was designed with a multiple gun game in mind where the gun knows
 * which vest it corresponds to, but in this build, this function serves to "stun" or 
 * lock out the gun from firing after the user shoots the one vest in the game.
 */
bool isStunned() {
  if (recentlyHit) {
    if ((millis() - playerHitTime) > HIT_STUN_TIME) {
      setHUD();
      recentlyHit = false;
    }
  }
  return recentlyHit;
}

/**
 * Fires the IR LED, lights up the red LED for the given delay, sends a 'fire' message
 * via the xBee, makes a short firing sound, and decrements the ammo.
 */
int fire(int lightDelay) {
  Serial.println(ammo);
  digitalWrite(FIRE_LED_PIN, HIGH);
  delay(lightDelay);
  digitalWrite(FIRE_LED_PIN, LOW);
  xBee.print(pString);
  xBee.println(" fire");
  Serial.println("fire");
  tone(BUZZER_PIN, 440, 100);
  sendIR();
  ammo--;
}

/**
 * If the current screen message is set to temporary, checks if the message has displayed
 * for the amount of time it should be, and updates the LCD to the heads-up display if
 * that time has passed.
 */
void handleTemporaryScreenMessage() {
  if (screenMessageTemporary) {
    if ((millis() - newScreenMessageTime) > temporaryScreenDuration) {
      setHUD();
      screenMessageTemporary = false;
    }
  }
}

/**
 * Sets the current temporary screen's display duration to a given time in milliseconds.
 */
void setCurrentScreenTemporary(int duration) {
  screenMessageTemporary = true;
  newScreenMessageTime = millis();
  temporaryScreenDuration = duration;
}

/**
 * Intended for use in multiple gun game for stunning current gun when hit.
 * Currently, not implemented as such, but does report a successful hit
 * on the vest in a single-gun game (and stuns the gun from hitting the vest
 * repeatedly in quick succession.
 */
void handlePlayerHitMessage() {
  lcd.clear();
  lcd.print("Hit!");
  recentlyHit = true;
  playerHitTime = millis();
}

/**
 * If the hall sensor is currently detecting a magnet, this function handles the charging
 * message from the charging station and updates the LCD to say 'Charging'.
 * 
 * Ideally in a multiple-gun project, the command center would send verification charging
 * and charged messages after receiving charging/charged messages from both the charging
 * station and gun.
 */
void handleChargingMessage() {
  if (charging) {
    lcd.clear();
    lcd.print("Charging");
    setCurrentScreenTemporary(CHARGE_TIME);
  }
}
/**
 * If the hall sensor is currently detecting a magnet, this function handles the charged
 * message from the charging station, updates the LCD to say 'Charged', and sets the gun's
 * charge to the max charge.
 * 
 * Ideally in a multiple-gun project, the command center would send verification charging
 * and charged messages after receiving charging/charged messages from both the charging
 * station and gun.
 */
void handleChargedMessage() {
  if (charging) {
    charge = MAX_CHARGE;
    lcd.clear();
    lcd.print("Charged!");
    lcd.setCursor(0, 1);
    lcd.print("Charge: ");
    lcd.print(charge);
    setCurrentScreenTemporary(TEMPORARY_SCREEN_MESSAGE_TIME);
  }
}

/**
 * Handles a game over message and stops the loop from doing anything but handle radio input.
 * 
 * Currently not implemented across the game.
 */
void handleGameOverMessage() {
  gameRunning = false;
  lcd.clear();
  lcd.print("Game over!");
}

/**
 * Handles a game begin message and allows the loop to start running functions other than
 * radio input. Ideally, this function should set all variables to their default values
 * in order to properly start a new game fresh.
 * 
 * Currently not implemented across the game.
 */
void handleGameBeginMessage() {
  gameRunning = true;
  lcd.clear();
  setHUD();
}

/**
 * Sends a 38KHz pulse to the IR LED pin for a given number of microseconds.
 * 
 * Courtesy of Adafruit's IR LED tutorial.
 * https://learn.adafruit.com/ir-sensor/making-an-intervalometer
 */
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
  cli();  // this turns off any background interrupts
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IR_LED_PIN, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds
    digitalWrite(IR_LED_PIN, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds
    // so 26 microseconds altogether
    microsecs -= 26;
  }
  sei();  // this turns them back on
}

/**
 * Sends a specific IR code (defined by the time in microseconds of pulses
 * and the times between pulses. This IR code specifically is the code for
 * 'Volume Up' on a Samsung TV, which we used instead of defining our own.
 */
void sendIR() {
  delayMicroseconds(47112);
  pulseIR(4660);
  delayMicroseconds(4640);
  pulseIR(580);
  delayMicroseconds(1740);
  pulseIR(580);
  delayMicroseconds(1740);
  pulseIR(580);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(540);
  delayMicroseconds(1760);
  pulseIR(560);
  delayMicroseconds(1740);
  pulseIR(580);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(1740);
  pulseIR(580);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(540);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(560);
  delayMicroseconds(1760);
  pulseIR(560);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(1760);
  pulseIR(560);
  delayMicroseconds(1720);
  pulseIR(600);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(48340);
  pulseIR(4680);
  delayMicroseconds(4640);
  pulseIR(580);
  delayMicroseconds(1720);
  pulseIR(600);
  delayMicroseconds(1740);
  pulseIR(580);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(540);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(1760);
  pulseIR(560);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(1760);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(560);
  delayMicroseconds(1760);
  pulseIR(560);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(1760);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(580);
  pulseIR(580);
  delayMicroseconds(1740);
  pulseIR(580);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(1740);
  pulseIR(560);
  delayMicroseconds(1760);
  pulseIR(560);
  delayMicroseconds(1740);
  pulseIR(560);
}
