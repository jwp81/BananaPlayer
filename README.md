# BananaPlayer
BananaPlayer is an open source & open software Digital Music Player that provides high-quality audio in a small, portable design. Its modern design, day-long battery life, ease of use, and repairability make it perfect for anyone with a love for music!

On the inside, the heart of the player is an ESP32-S3, which controls the Display, DAC + Amp, navigation knob, haptics, and UI. The 1200mAh LiPo gives enough power for 10-12 hours of listening time, and has a standby time of 40 days.

Repairability has always been an important part of the designing process. So make repair simple, only 4 screws are needed to hold the entire player together while keeping it sturdy. This makes it possible to replace or add a part in under 2 minutes :)

Freedom in your music, designed with pride.

# **Getting Started**
## **UI navigation**
The user interface of BananaPlayer is programmed with LVGL, a lightweight UI ecosystem.
### **Basic Navigation**
To turn the player on, hold the power button for 5 seconds. Once powered on, you will be greeted with the home menu. To navigate through the menus, rotate the knob to scroll through menu lists. Press down on the knob to select, hold on the knob to go back. 
### **Control Center**
To open the control center, firmly press down on the knob until you feel a secondary click. Here, you can quickly access controls like volume, brightness, shuffle, repeat, button lock, etc. The button lock prevents accidental presses with playing music. To exit button lock, push and hold on the knob for 5 seconds.
### **Music Navigation: Now Playing screen**
In the Now Playing screen, use the knob to adjust volume and the bottom buttons to pause, play, forward track, and backward track. To scrub through music, push on push on the knob and rotate the scrub though. Press the knob again to select. To exit Now Playing, hold down on the knob. 

***Note: Adjusting volume with knob can only be done in Now Playing. To adjust volume in any other menus, navigate to the control center.***
