# WiiClassicController_daemon
Using an Arduino Uno to interface with a Wii Classic Controller and emulating joypad input via vJoy. Windows only.
# How to install
1. Upload the .ino file to your Arduino.
2. With the connector's crease facing down, wire the top-left pin to SDA, the bottom-right pin to SCL, the top-right pin to 3.3V and the bottom-left pin to GND. These instructions are for the Arduino Uno R3, but should work with other versions. *I recall seeing the Analog In 4 and 5 pins being used in place of SDA and SCL.* **You can stick jumpers in the pins if you don't have an adapter.**
3. Install vJoystick from http://vjoystick.sourceforge.net/site/
4. Configure a virtual device (possibly the first, if you can't check the Common Problems paragraph) to have two continuous POVs, no axes and 15 buttons.
5. Compile and run WiiClassicController_daemon.exe.

# Common problems

If the daemon returns with exit code -2, it's because the COM port checked for an Arduino is hard coded. I'm really sorry for this, but I can't seem to find a proper way to iterate through each port and correctly identify the board. If you need to change it, you can find the definition in main.cpp, or you can change you Arduino's COM port directly from Windows.

If the daemon returns with exit code -3, it's because the vJoy device interface with ID 1 is already in use. Its value is hardcoded, seeing little benefit from having it chosen dynamically, but all you have to do is edit the VJ_INTERFACE macro in main.cpp if that's a problem.

# How to use
The controller will now work as any other DirectInput controller would. I'm still having problems getting it recognized by some games, but I assume it's because they're expecting XInput devices instead. I've tested it on Snes9x and Retroarch, and it works just fine.
