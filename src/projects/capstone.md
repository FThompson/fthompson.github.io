# Smart Prescription Management Device Capstone

For my Human-Centered Design & Engineering (HCDE) capstone project, I worked with a team of three other HCDE students to prototype a smart device and companion app to help postoperative patients follow their pain management prescriptions as they go through the postoperative recovery process. Our project was sponsored by The University of Washington and Seattle Children's Hospital, including Dr. Lance Patak and resident doctors Stuart Solomon and Jacob Gross.

![Quickstart Guide](/static/projects/capstone/quickstart.png)

<video controls muted autoplay loop>
    <source src='/static/projects/capstone/device.webm' type='video/webm'>
    <source src='/static/projects/capstone/device.mp4' type='video/mp4'>
    <p>Your device does not support embed video playback. View the device overview video <a href='/static/projects/capstone/device.mp4' title='Capstone device'>here</a>.</p>
</video>

![App Screens](/static/projects/capstone/app-screens.png)
*Companion app screens.*

![Device Screens](/static/projects/capstone/device-screens.png)
*Physical device screens.*

## Overview

Opioids provide necessary pain relief to postoperative patients. However, opioids can be addictive, dangerous, and are often subject to misuse. Our project, an in-home oral Patient-Controlled Analgesia (PCA) device, seeks to address these issues by providing patients with the guidance they need to manage their pain effectively during their postoperative recovery.

Our team researched, designed, prototyped, evaluated, and iterated a PCA device and companion app that monitor and manage opioid prescriptions while connecting patients to doctors throughout the postoperative recovery phase.

## Our Design Process

My team's capstone project took place over two quarters: the first quarter encompassed teambuilding and planning two week sprints and goals to be delivered during the second quarter of the capstone. Each team member acted as project manager for one sprint phase.

![Our design process: Design, Prototype, Evaluate, and Iterate](/static/projects/capstone/design-process.png)

Following the Iteration phase, we designed a poster and quickstart guide (pictured at the top of this page) and presented our project at the HCDE Capstone Open House, open to the public.

## My Role

For this project, I was responsible for purchasing and soldering electrical components, developing device code, and managing the Evaluation sprint in which we conducted a usability research study to evaluate our first prototype. These primary contributions were in addition to working with my team to define our project plan, sketch and polish ideas in the Design phase, and more.

### First Prototype (Arduino & C/C++)

<img id='first-prototype-parts' class='right' src='/static/projects/capstone/first-prototype-parts.jpg' alt='Disassembled first prototype'>

For the first version of our prototype, we used an Arduino called the TinyDuino, which has a footprint around the size of a nickel. I ordered and assembled the necessary components:
 * TinyDuino with battery
 * 3.5" touchscreen by Adafruit
 * Two servo motors
 * Two indicator LEDs
 * Speaker and amplifier

As I explored Adafruit's graphics libraries for the touchscreen, I found they offered no way to combine graphics and interaction, so I wrote my own Component superclass with which I could define when a component is valid and how that component should act when painted, pressed, or clicked. I also wrote touch handling code to discern whether the current touch is a press or a click, as Adafruit's library supplied the current touch only as a point on the screen when a touch is present. I also wrote objects to handle a Pill Door mechanism and to handle a Prescription with *x* doses every *n* hours, to name a few.

[See the full version 1 code on GitHub.](https://github.com/FThompson/SmartPCA-Capstone-v1)

### Usability Evaluation

For the third sprint, my team conducted a usability evaluation of our first prototype. I was project manager of this sprint, the Evaluation phase. To provide our usability evaluations with purpose, I defined a set of research questions split into device and companion app.

#### Device
1. Do users encounter errors, either as a result of hardware of software design, that impact their ability to successfully acquiure medication from the device?
2. Do users understand the dose information on the at-a-glance display?
3. Do users desire any features (additional prescription info, settings, etc.) that we do not have implemented?
4. Are users satisfied with their ability to acquire medication from the device?
5. Do users understand the wording of the pain questions?

#### Companion App
1. Do users understand the concept of the historical data chart display and prescription progress gradient (the weaning graph)?
2. Do users understand the information hierarchy in the app?
3. Do users desire any features (additional prescription info, settings, etc.) that we do not have implemented?

#### Approach

We conducted 6 usability evaluation sessions in private rooms in UW libraries, where each member of the team had a role: one moderator, one video recorder, and two notetakers. Each participant followed a set of tasks we defined to try and answer our research questions. At the end of each session, we gave each participant a $5 Amazon gift card as compensation for their time.

Once we had conducted all of the sessions, we translated the data into key findings by coding our data with notable events we observed and how many participants encountered each notable event. We classified our findings by severity to allow us to prioritize design recommendation by impact, useful in case we did not have time to implement all recommendations.

#### Design Recommendations

![Device Recommendations](/static/projects/capstone/device-design-recs.png)
*Device design recommendations.*

![Companion App Recommendations](/static/projects/capstone/app-design-recs.png)
*Companion app design recommendations.*

[See the full Evaluation phase report here.](/static/projects/capstone/Milestone%203%20Report%20-%20Evaluate.pdf)

### Second Prototype (Raspberry Pi & Python)

<img id='second-prototype-parts' class='right' src='/static/projects/capstone/second-prototype-parts.jpg' alt='Disassembled second prototype'>

While the Arduino worked well for a first prototype, it is a fairly weak microcontroller, as shown by the screen taking 1-2 seconds to refresh on every touch. For the second prototype, I made the decision to use a Raspberry Pi Zero W:
 * Much more powerful, allowing for a quick, responsive screen
 * Support for Python, which I am more familiar with than C/C++ and it offers better graphical libraries
 * WiFi connectivity for uplaoding prescription use data and connecting to the companion app
 * The Pi mounts directly onto the screen, allowing for a smaller electronic footprint

For this implementation, I rebuilt the entire codebase in Python with cleaner, more maintainable code using [pigpio](http://abyz.me.uk/rpi/pigpio/) and [pygame](https://www.pygame.org/docs/). Pygame offers useful graphics, audio, and input functions but lacks an object-oriented approach to UI/UX design, so I recreated my component architecture from the first prototype and added a scene object to handle input and components for each screen (scene) of the application.

[See the full version 2 code on GitHub.](https://github.com/FThompson/SmartPCA-Capstone-v2)

## Assets

* [Finn Thompson - Process Book (PDF)](/static/projects/capstone/Finn%20-%20Process%20Book.pdf)
* Code
    * [Version 1 Code Repository (Arduino & C/C++)](https://github.com/FThompson/SmartPCA-Capstone-v1)
    * [Version 2 Code Repository (Raspberry Pi & Python)](https://github.com/FThompson/SmartPCA-Capstone-v2)
* [Project Proposal (PDF)](/static/projects/capstone/Project%20Proposal.pdf)
* Sprint Reports
    * [Milestone 1 Report - Design (PDF)](/static/projects/capstone/Milestone%201%20Report%20-%20Design.pdf)
    * [Milestone 2 Report - Prototype (PDF)](/static/projects/capstone/Milestone%202%20Report%20-%20Prototype.pdf)
    * [Milestone 3 Report - Evaluate (PDF)](/static/projects/capstone/Milestone%203%20Report%20-%20Evaluate.pdf)
    * [Milestone 4 Report - Iterate (PDF)](/static/projects/capstone/Milestone%204%20Report%20-%20Iterate.pdf)
* [Presentation Poster (PDF)](/static/projects/capstone/Poster.pdf)
* [Quickstart Guide (PDF)](/static/projects/capstone/Quickstart%20Guide.pdf)
* [All PDF assets (ZIP)](/static/projects/capstone/Finn%20-%20Capstone%20Assets.zip)