# WiiClassicController_daemon
Using an Arduino Uno to interface with a Wii Classic Controller and emulating joypad input via vJoy. Windows only.
# How to install
1. Upload the .ino file to your Arduino.
2. With the connector's crease facing down, wire the top-left pin to SDA, the bottom-right pin to SCL, the top-right pin to 3.3V and the bottom-left pin to GND. These instructions are for the Arduino Uno R3, but should work with other versions. *I recall seeing the Analog In 4 and 5 pins being used in place of SDA and SCL.*
3. Compile and run WiiClassicController_daemon.exe.
# How to use
The controller will now work as any other DirectInput controller would. I'm still having problems getting it recognized by some games, but I assume it's because they're expecting XInput devices instead. I've tested it on Snes9x and Retroarch, and it works just fine.
