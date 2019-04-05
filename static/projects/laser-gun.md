# Laser Tag Gun Prototype

<img id='laser-gun' src='/static/projects/laser-gun/laser-gun.jpg' alt='Laser Gun Prototype'>
<em>Laser tag gun prototype, with a view of the internal components.</em>

## Motivation

For the HCDE 439 Physical Computing final project, students were required to work in pairs in a team of a few other pairs (i.e. 3-4 pairs working together) to create a system of different Arduino-powered components communicating over XBee radio modules.

My team decided to create a laser tag game, where me and my partner created the laser gun and other pairs in our team made the body vest, charging station, and communication center modules. We wanted to design something fun yet simple enough that it could be built within a couple weeks.

## Solution

We incorporated several sensors and display components into the laser gun:

* IR LED array with 4 IR LEDs
* LCD display showing ammo and firing mode
* Out-of-ammo indicator LED
* Shot indicator LED
* Tilt sensor to detect reload by tilting back gun
* Hall sensor to detect proximity to charging station's magnet
* XBee for reporting to comms center and receiving player hit and game start/finish alerts
* USB battery pack for portability

![Assembled laser gun internals](/static/projects/laser-gun/internal.jpg)
*Internal view of the assembled laser gun.*

My role included soldering and assembling components and leading the programming of the Arduino Nano in the laser gun. I also researched IR LEDs and power consumption limits with which I compared the effective range of a single strong IR LED versus an array of lower power IR LEDs, finding that the array could be detected by the body vest from a further distance.

![Component protoboards](/static/projects/laser-gun/soldered-parts.jpg)
*Soldered protoboard components for the IR LEDs and the fire / firing mode buttons.*

## Assets

* [Laser Gun Arduino Code](/static/projects/laser-gun/Laser%20Gun%20Code.ino)
* [Laser Gun Schematic (PDF)](/static/projects/laser-gun/Laser%20Gun%20Schematic.pdf)
* [Laser Tag Project Overview](/static/projects/laser-gun/Laser%20Gun%20Project%20Overview.pdf)