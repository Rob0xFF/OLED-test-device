PROJECT_DIR       = $(HOME)/MyArduinoProject/OLED-test-device

ARDMK_DIR         = $(PROJECT_DIR)/Makefile

ARDUINO_DIR       = /Applications/Arduino.app/Contents/Java

USER_LIB_PATH    :=  $(PROJECT_DIR)/lib

BOARD_TAG   = leonardo 

#ARDUINO_LIB_PATH = $(HOME)/Documents/Arduino/libraries

ARDUINO_LIBS = C12880 3rdParty/ElapsedMillis

OPTIMIZATION_LEVEL = s

MONITOR_PORT      = /dev/cu.usbmodem*

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
