# FRLGBlindDeaf
Arduino Code to run Pokemon LeafGreen or FireRed on an Arduino

CompressedControl.ino includes the headers, and can be uploaded to Arduino Due or Mega using the Arduino IDE. The pins corresponding to each button are listed at the very top of the CompressedControl file, and can be edited based on your preferences (if for some reason you decide to do this yourself).

The program will not run on an Arduino Uno in its current form, as the Uno has only 32 kB of program memory. Extreme compression which would allow running on this microcontroller is probably possible, but would require significant work (or the use of an external SD card to load in the instructions, available from Adafruit).
