# Textube Desktop Utility

![Textube Settings](/static/projects/textube/settings.png)

## Motivation

Often when I'd be coding and working with another person, I found myself wanting to quickly share code snippets or files with them. When I made this project originally, my typical answer to this problem was to pull up a website like pastebin or drop a file into my Dropbox public folder, but I wanted something faster, so I created Textube.

## Solution

I made Textube as a desktop tray application paired with a PHP server application that handled file uploads and URL shortening (to the host `http://textu.be`). I developed these client and server components of Textube over a two week span to be turned in for an AP Computer Science course in high school.

I used JNA to make a system-wide key listener to bind actions to shortcuts and I created a plugin class that could be extended to create custom tools, the included tools being Upload and Evaluate.

![Upload action](/static/projects/textube/upload.gif)
*Uploading the text/file from the clipboard. (Completion notification absent).*

![Evaluate action](/static/projects/textube/evaluate.gif)
*Evaluating a math expression on the clipboard.*

## Assets

As Textube was one of my first comprehensive projects, I did not follow best coding practices in several cases. In particular, the PHP and web server code is quite bad and uses `mysql_*` functions, for example. Also notable is the "Cancel" button text being cut short in the above upload panel due to using static dimensions rather than a proper layout manager. Regardless, I've included the code split into desktop app and server app assets.

* [Textube Tray App Assets (ZIP)](/static/projects/textube/Textube%20Tray%20App%20Assets.zip)
* [Textube Server Assets (ZIP)](/static/projects/textube/Textube%20Server%20Assets.zip)