# UW Course Seat Claimer

![Application interface](/static/projects/uw-class-seats/interface.png)

## Motivation

When registering for courses at the University of Washington, students may often find that the classes they desire are all filled. Rather than offer a waitlist solution for students to queue for seat openings, UW simply offers students the option to subscribe for seat notifications either via text or email. When a seat opens up, all subscribed students—numbering in the hundreds for more popular courses—then race to be the first to claim the open seat.

In order to maximize one's chances of being the first to claim a seat, students must keep a registration session open on their phone's browser and have the course form ready to submit the desired course ID, refreshing their session every few hours to ensure they stay logged in. Not a very user friendly system, in my opinion.

## Solution

To automate the registration process, I created a Java GUI application that listens to a user's email inbox for an open seat notification and register the user for the open seat. The application also supports registering for a course dependency, useful in cases where students must register for both a lecture and a quiz/discussion section. To enable users to register for another course in the meantime, the application also supports dropping specified classes that may have conflicting times with the desired classes.

Upon pressing Start, the application logs into the user's email inbox, begins listening for notification emails, and updates each course icon from an arrow to a loading animation. Upon successful registration of a course, that course icon updates to a checkmark. Upon exceptions (such as failed UW login), the respective course icon updates to a failure icon.

<div class='centered-block'>
    <img class='inline' src='/static/projects/uw-class-seats/arrow-icon.png' alt='Arrow icon'>
    <img class='inline' src='/static/projects/uw-class-seats/loading-icon.gif' alt='Loading icon'>
    <img class='inline' src='/static/projects/uw-class-seats/success-icon.png' alt='Success icon'>
    <img class='inline' src='/static/projects/uw-class-seats/failed-icon.png' alt='Failed icon'>
</div>

## Disclaimer

I learned after developing this application that programs that automate UW's class registration process are forbidden by the university. I ended up manually getting into the class I needed while working on this application, but I still decided to finish it for completion's sake. In respecting UW's rule, I will not be publishing the code online, though prospective employers may request the code or code samples at my discretion.