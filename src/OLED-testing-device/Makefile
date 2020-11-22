### DISCLAIMER
### This is an example Makefile and it MUST be configured to suit your needs.
### For detailed explanations about all the available options,
### please refer to https://github.com/sudar/Arduino-Makefile/blob/master/arduino-mk-vars.md

### PROJECT_DIR
### This is the path to where you have created/cloned your project
PROJECT_DIR       = $(HOME)/MyArduinoProject/OLED-test-device

### ARDMK_DIR
### Path to the Arduino-Makefile directory.
ARDMK_DIR         = $(PROJECT_DIR)/Arduino-Makefile

### ARDUINO_DIR
### Path to the Arduino application and resources directory.
### For Arduino IDE 1.0.x
# ARDUINO_DIR       = /Applications/Arduino.app/Contents/Resources/Java
### For Arduino IDE 1.6.x ++
ARDUINO_DIR       = /Applications/Arduino.app/Contents/Java

### USER_LIB_PATH
### Path to where the your project's libraries are stored.
USER_LIB_PATH    :=  $(PROJECT_DIR)/lib

### BOARD_TAG & BOARD_SUB
### For Arduino IDE 1.0.x
### Only BOARD_TAG is needed. It must be set to the board you are currently using. (i.e uno, mega2560, etc.)
# BOARD_TAG         = mega2560
### For Arduino IDE 1.6.x
### Both BOARD_TAG and BOARD_SUB are needed. They must be set to the board you are currently using. (i.e BOARD_TAG = uno, mega, etc. & BOARD_SUB = atmega2560, etc.)
### Note: for the Arduino Uno, only BOARD_TAG is mandatory and BOARD_SUB can be equal to anything
# BOARD_TAG         = mega
# BOARD_SUB         = atmega2560

BOARD_TAG         = 2560
ALTERNATE_CORE    = MegaCore
BOARD_SUB         = ATmega2560
F_CPU = 16000000L
ALTERNATE_VAR_PATH  = $(HOME)/Library/Arduino15/packages/MegaCore/hardware/avr/2.0.3
ALTERNATE_CORE_PATH = $(HOME)/Library/Arduino15/packages/MegaCore/hardware/avr/2.0.3
VARIANT = 100-pin-arduino-mega
AVRDUDE_ARD_BAUDRATE = 115200
AVRDUDE_ARD_PROGRAMMER = arduino
HEX_MAXIMUM_SIZE = 261120
ARDUINO_LIB_PATH = $(HOME)/Documents/Arduino/libraries
ARDUINO_LIBS = GUI OLED Wire TCA9548A E522.46 3rdParty/INA226 3rdParty/BH1750 3rdParty/HIH6130 3rdParty/DS3231 Hardware 3rdParty/ILI9341TFT 3rdParty/FT6206 SPI 3rdParty/SD 3rdParty/EEPROM 3rdParty/MemoryFree 3rdParty/TimerOne
OPTIMIZATION_LEVEL = s

### MONITOR_PORT
### The port your board is connected to. Using an '*' tries all the ports and finds the right one.
MONITOR_PORT      = /dev/cu.usbserial*

### MONITOR_BAUDRATE
### It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE  = 115200

### AVR_TOOLS_DIR
### Path to the AVR tools directory such as avr-gcc, avr-g++, etc.
AVR_TOOLS_DIR     = /usr/local

### AVRDUDE
### Path to avrdude directory.
AVRDUDE           = /usr/local/bin/avrdude
AVRDUDE_OPTS      = -v -v

### CFLAGS_STD
CFLAGS_STD        = -std=gnu11

### CXXFLAGS_STD
### You can choose wich ever you like
# CXXFLAGS_STD      = -std=gnu++11
CXXFLAGS_STD      = -std=gnu++17

### CPPFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
CXXFLAGS         += -pedantic -Wall -Wextra 
LDFLAGS          += -fdiagnostics-color -Wl,-u,vfprintf -lprintf_flt -lm

### OBJDIR
### Don't touch this!
### This is were you put the binaries you just compile using 'make'
CURRENT_DIR       = $(shell basename $(CURDIR))
OBJDIR            = $(PROJECT_DIR)/build/$(CURRENT_DIR)/$(BOARD_TAG)

### path to Arduino.mk, inside the ARDMK_DIR, don't touch.
include $(ARDMK_DIR)/Arduino.mk

