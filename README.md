



A fun little project to animate a skeleton jaw in sync with audio files (in this case a Merry Christmas greeting, and a surprise burp). I set this up at my local Pilates studio to surprise the clients as they did their classes. The skeleton talks at random times (this can be configured in the code). The skeletons jaw can be made to move in sync with pretty much any sound, but it takes a bit of experimentation to get it right. I loaded the sound files into Clip Champ which provides a sound graph with time along the x-axis. Using the graph you can work out roughtly when each sylable starts and then use the times derived in an array (see code for the examples of this).

[[https://user-images.githubusercontent.com/25494253/212456855-65f0a4e9-69e5-4fcd-92f9-1c16e966bdc1.png | height=300px]]


Here is the outcome (make sure you turn the sound on):

https://user-images.githubusercontent.com/25494253/212453545-23ddd6fe-1c43-49a9-974a-9271c8d2dbdb.mp4

 You will need an Arduino (in my case Uno) and an mp3 player such as:
 https://www.jaycar.com.au/mp3-audio-player-module-with-6-push-button-switches-for-arduino/p/XC3748
 
I used 6 x 1.5V AA batteries to power the Uno and servo. Mp3 player is powered from the Uno. However I found that the sound didn't play properly unless I also supplied power via the Uno's usb as well (I used a usb cable attached to a phone charger.

Here is a photo of the setup:

![IMG20230114151128](https://user-images.githubusercontent.com/25494253/212456248-05d216f0-cd94-4cab-a459-d6d0b9cd6d9d.jpg)

I use Visual Studio for coding with Arduino (using the vMicro addin) but if you want to use the Arduino IDE just download the hohoho.ino file and make sure you have the required libraries installed as well.
