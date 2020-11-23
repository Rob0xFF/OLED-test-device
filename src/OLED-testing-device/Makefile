PROJECT_DIR       = $(HOME)/MyArduinoProject/OLED-test-device

ARDMK_DIR         = $(PROJECT_DIR)/Arduino-Makefile

ARDUINO_DIR       = /Applications/Arduino.app/Contents/Java

USER_LIB_PATH    :=  $(PROJECT_DIR)/lib

ALTERNATE_CORE    = MegaCore

BOARD_SUB         = ATmega2560

BOARD_TAG         = 2560

VARIANT = 100-pin-arduino-mega

F_CPU = 16000000L

HEX_MAXIMUM_SIZE = 261120

ALTERNATE_VAR_PATH  = $(HOME)/Library/Arduino15/packages/MegaCore/hardware/avr/2.0.3

ALTERNATE_CORE_PATH = $(HOME)/Library/Arduino15/packages/MegaCore/hardware/avr/2.0.3

AVRDUDE_ARD_BAUDRATE = 115200

AVRDUDE_ARD_PROGRAMMER = arduino

ARDUINO_LIB_PATH = $(HOME)/Documents/Arduino/libraries

ARDUINO_LIBS = Board Display E522.46 Elements GUI Microscope OLED Screens Spectrometer Stepper TCA9548A 

ARDUINO_LIBS += 3rdParty/BH1750 3rdParty/DS3231 3rdParty/EEPROM 3rdParty/FT6206 3rdParty/HIH6130 3rdParty/ILI9341TFT 3rdParty/INA226 3rdParty/MemoryFree 3rdParty/SD 3rdParty/TimerOne

ARDUINO_LIBS += Wire SPI

OPTIMIZATION_LEVEL = s

MONITOR_PORT      = /dev/cu.usbserial*

MONITOR_BAUDRATE  = 115200

AVR_TOOLS_DIR     = /usr/local

AVRDUDE           = /usr/local/bin/avrdude

AVRDUDE_OPTS      = -v -v

CFLAGS_STD        = -std=gnu11

CXXFLAGS_STD      = -std=gnu++17

CXXFLAGS         += -pedantic -Wall -Wextra 

LDFLAGS          += -fdiagnostics-color -Wl,-u,vfprintf -lprintf_flt -lm

CURRENT_DIR       = $(shell basename $(CURDIR))

OBJDIR            = $(PROJECT_DIR)/build/$(CURRENT_DIR)/$(BOARD_TAG)

include $(ARDMK_DIR)/Arduino.mk

