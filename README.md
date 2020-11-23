# OLED-test-device

The build environment originates from the Bare-Arduino-Project by ladislas and the awesome makefile templates provided by sudar. 

In order to build, follow the steps provided here: 

https://github.com/ladislas/Bare-Arduino-Project

https://github.com/sudar/Arduino-Makefile

Individual Makefiles are located besides the main.cpp files. In order to use all pins of the Atmega2560, not only those broken out on Arduino Boards, we rely on the Core files provided by MCUDude:

https://github.com/MCUdude/MegaCore

Additionally, we will need to manually add placement new to the core files, because for some reason this is not included in the original distribution. 
