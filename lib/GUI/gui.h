#ifndef GUI_h
#define GUI_h

#include <OLED.h>
#include <new.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"
#include <TCA9548A.h>
#include <E52246.h>
#include <INA226.h>
#include <AS_BH1750.h>
#include <HIH6130.h>
#include <DS3231.h>
#include <display.h>
#include "glcdfont.c"
#include <Adafruit_FT6206.h>
#include <board.h>
#include <Screens.h>

class GUI
{
  public:
    /*!
      * @brief GUI class constructor.
      */
    GUI() {};
    /*!
      * @brief GUI boot sequence, boots hardware, shows main menu when ready.
      */
    void boot(void);
    /*!
      * @brief Here, we keep things going, calls mainboard update and screen updates, this is called each second by the main thread external timer interrupt.
      */
    void update(void);
    /*!
      * @brief Here, we keep things going, hich require high frequency updates, like LCD dimming and motor drive steps, this is called each millisecond by the main thread timer interrupt.
      */
    void fastUpdate(void);
    /*!
      * @brief Here, we assign touch events to their respective handlers, this is called by the main thread touch event interrupt once per touch event.
      */
    void updateTouch();
    /*!
      * @brief The GUI holds the instance of the motherboard hardware to operate with.
      */
    Board board = Board();

  private:

    /*!
      * @brief This is the screen header including clock, temperature, humidity and status. This instance will never be destroyed.
      */
    ScreenHeader _screenheader = ScreenHeader(board);

    //uint8_t memBuffer[sizeof(Characteristic)];


    /*!
      * @brief Pointers to the menu items. Instance is created/destroyed/recreated during runtime on user interaction. Placed onto fixed memBuffer to avoid memory fragmenation.
      */
    uint8_t memBufferMainMenu[sizeof(MainMenu)];
    MainMenu * mainMenu;

    uint8_t memBufferQuickTest[sizeof(QuickTest)];
    QuickTest * quickTest;

    uint8_t memBufferCharacteristic[sizeof(Characteristic)];
    Characteristic * characteristic;

    uint8_t memBufferSpectrum[sizeof(Spectrum)];
    Spectrum * spectrum;

    uint8_t memBufferAngleScan[sizeof(AngleScan)];
    AngleScan * angleScan;

    uint8_t memBufferClockSet[sizeof(ClockSet)];
    ClockSet * clockScreen;

    uint8_t memBufferInfo[sizeof(Info)];
    Info * info;

    int16_t TouchX;
    int16_t TouchY;

    uint8_t currentScreen;

};

#endif