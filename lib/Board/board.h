#ifndef BOARD_h
#define BOARD_h

#include <OLED.h>
#include <stdint.h>
#include <new.h>
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
#include <Adafruit_FT6206.h>
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>
#include <MemoryFree.h>
#include <microscope.h>
#include <spectrometer.h>
#include "stepper.h"

#define I2C_TCAMAIN 0x70 // Main I2C Multiplexer
#define I2C_TCAHEAD 0x74 // Secondary I2C Multiplexer
#define I2C_INA226 0x40 // U/I Meter
#define INA1_TCA_PIN 0
#define INA2_TCA_PIN 1
#define INA3_TCA_PIN 2
#define INA4_TCA_PIN 5
#define INA5_TCA_PIN 6
#define INA6_TCA_PIN 7
#define I2C_E52246_1 0x3C // OLED Driver 1
#define E52246_1_RUN 33 // OLED Driver 1 Run pin
#define E52246_1_INT_PIN 32
#define E52246_1_TCA_PIN 3
#define E52246_1_PROGEN 31
#define I2C_E52246_2 0x3D
#define E52246_2_RUN 37
#define E52246_2_INT_PIN 34
#define E52246_2_TCA_PIN 4
#define E52246_2_PROGEN 35
#define I2C_BH1750 0x5C
#define BH1_TCA_PIN 7
#define BH2_TCA_PIN 6
#define BH3_TCA_PIN 5
#define BH4_TCA_PIN 2
#define BH5_TCA_PIN 1
#define BH6_TCA_PIN 0
#define I2C_HIH6130 0x27
#define I2C_DS3231 0x68
#define DS3231_INT_PIN 72
#define DS3231_INT 7
#define MCP73832_STAT 7
#define TFT_CS A3 // Chip Select goes to Analog 3
#define TFT_CD A2 // Command/Data goes to Analog 2
#define TFT_WR A1 // LCD Write goes to Analog 1
#define TFT_RD A0 // LCD Read goes to Analog 0
#define TFT_BACKLIGHT 4
#define I2C_FT6206 0x38
#define FT6206_IRQ_PIN 71
#define FT6206_INT 6
#define SD_CARD_CHECK 36
#define SD_CS 41
#define LED_GREEN 9
#define LED_RED 8
#define MOTOR_DIR 70
#define MOTOR_STEP 5
#define MOTOR_ENABLE 2
#define MOTOR_LIMIT_PIN 3
#define MOTOR_LIMIT_INT 5
#define TCAMAIN 0
#define TCAHEAD 1
#define INA1 2
#define INA2 3
#define INA3 4
#define INA4 5
#define INA5 6
#define INA6 7
#define E52246_1 8
#define E52246_2 9
#define BH1 10
#define BH2 11
#define BH3 12
#define BH4 13
#define BH5 14
#define BH6 15
#define PIXEL_1 16
#define PIXEL_2 17
#define PIXEL_3 18
#define PIXEL_4 19
#define PIXEL_5 20
#define PIXEL_6 21
#define HIH6130_TEMP_HUM 22
#define DS3231_CLOCK 23
#define FT6206 24
#define SD_CARD 25
#define MOTOR 26
#define MICROSCOPE1 27
#define MICROSCOPE2 28
#define SPEC1 29
#define SPEC2 30
#define CHARGING_BIT 31

/*!
 * @brief Board main class, manages the mainboard of the OLED testing device
 */
class Board
{
  public:
    /*!
     * @brief Board class constructor
     */
    Board();
    /*!
     * @brief Mainboard boot sequence,
     * @brief checks and registers all sensors and devices using low level access
     * @brief must be called first
     */
    void begin(void);

    /*!
     * @brief check SD Slot and initialize SD card if present
     */
    void checkSDSlot();

    /*!
     * @brief update temperature and humidity
     */
    void updateTemperHum();

    /*!
     * @brief update time
     */
    void updateTime();

    uint16_t getFreeMemory();

    /*!
     * @brief update all relevant parameters
     * @brief to be called once a second
     */
    void update();

    void checkEXT();

    /*!
     * @brief manage availability of hardware
     */
    inline void available(uint8_t bit)
    {
      _isAvailable |= 1UL << bit;
    };
    inline void unAvailable(uint8_t bit)
    {
      _isAvailable &= ~(1UL << bit);
    };
    inline uint8_t isAvailable(uint8_t bit)
    {
      if (_isAvailable & 1UL << bit) {
        return 1;
      } else {
        return 0;
      }
    };

    char dataFile[13];

    void logSpectrum(void);
    void writeToLog(char textBuffer[]);
    void writeToLog(const __FlashStringHelper * );
    void writeToLog(float number);
    void writeToLog(uint8_t number);
    void writeToLog(uint16_t number);
    void writeTimeToLog();

    void saveScreenshot(void);
    uint8_t screenshotCount = 0;
    char screenshotFile[13];

    float temperature;
    float humidity;
    DateTime now;

    uint8_t brightnessSetPoint = 128;

    uint8_t hotplugStatus = 0;

    File myFile;

    // create instances for the clock
    DS3231 _myClock;
    RTClib _myRTC; // now

    // create instances for the touch screen
    Adafruit_FT6206 myTouch = Adafruit_FT6206();

    // create instance for the TFT monitor
    //Adafruit_TFTLCD TFT = Adafruit_TFTLCD(TFT_CS, TFT_CD, TFT_WR, TFT_RD, -1);
    Display TFT;

    uint8_t memBufferMicroscope[sizeof(Microscope)];
    Microscope * microscope;

    uint8_t memBufferSpectrometer[sizeof(Spectrometer)];
    Spectrometer * spectrometer;

    uint8_t memBufferStepper[sizeof(Stepper)];
    Stepper * stepper;

    // create instances for the OLED pixels, hold them in a struct with their main properties
    struct OLEDPixel {
      OLED pixel;
      uint8_t tcaPin;
      uint8_t availBit;
    };

    OLEDPixel _Pixel[6] = {
      {
        OLED(TCAmain, OLEDDriver1, _myIna[2].sensor, TCAhead, _myBH[2].sensor, E52246_1_TCA_PIN, 0xC0, INA3_TCA_PIN, BH3_TCA_PIN), E52246_1_TCA_PIN, PIXEL_3
      },
      {
        OLED(TCAmain, OLEDDriver1, _myIna[1].sensor, TCAhead, _myBH[1].sensor, E52246_1_TCA_PIN, 0x38, INA2_TCA_PIN, BH2_TCA_PIN), E52246_1_TCA_PIN, PIXEL_2
      },
      {
        OLED(TCAmain, OLEDDriver1, _myIna[0].sensor, TCAhead, _myBH[0].sensor, E52246_1_TCA_PIN, 0x07, INA1_TCA_PIN, BH1_TCA_PIN), E52246_1_TCA_PIN, PIXEL_1
      },
      {
        OLED(TCAmain, OLEDDriver2, _myIna[3].sensor, TCAhead, _myBH[3].sensor, E52246_2_TCA_PIN, 0x07, INA4_TCA_PIN, BH4_TCA_PIN), E52246_2_TCA_PIN, PIXEL_4
      },
      {
        OLED(TCAmain, OLEDDriver2, _myIna[4].sensor, TCAhead, _myBH[4].sensor, E52246_2_TCA_PIN, 0x38, INA5_TCA_PIN, BH5_TCA_PIN), E52246_2_TCA_PIN, PIXEL_5
      },
      {
        OLED(TCAmain, OLEDDriver2, _myIna[5].sensor, TCAhead, _myBH[5].sensor, E52246_2_TCA_PIN, 0xC0, INA6_TCA_PIN, BH6_TCA_PIN), E52246_2_TCA_PIN, PIXEL_6
      },
    };

  private:

    // create instances for the I2C multiplexers
    TCA9548A TCAmain = TCA9548A(I2C_TCAMAIN);
    TCA9548A TCAhead = TCA9548A(I2C_TCAHEAD);

    // create instances for the OLED Drivers
    E52246 OLEDDriver1 = E52246(I2C_E52246_1, E52246_1_RUN);
    E52246 OLEDDriver2 = E52246(I2C_E52246_2, E52246_2_RUN);

    // create instance for the environment monitor
    HIH6130 _myHIH = HIH6130(I2C_HIH6130);

    // create instances for the voltage / current sensors, hold them in a struct with their main properties
    struct InaSensors {
      INA226 sensor;
      uint8_t tcaPin;
      uint8_t availBit;
    };

    InaSensors _myIna[6] {
      {
        INA226(), INA1_TCA_PIN, INA1
      }, {
        INA226(),
        INA2_TCA_PIN,
        INA2
      }, {
        INA226(),
        INA3_TCA_PIN,
        INA3
      }, {
        INA226(),
        INA4_TCA_PIN,
        INA4
      }, {
        INA226(),
        INA5_TCA_PIN,
        INA5
      }, {
        INA226(),
        INA6_TCA_PIN,
        INA6
      }
    };

    // create instances for the illuminance sensors, hold them in a struct with their main properties
    struct BHSensors {
      AS_BH1750 sensor;
      uint8_t tcaPin;
      uint8_t availBit;
    };

    BHSensors _myBH[6] = {
      {
        AS_BH1750(I2C_BH1750), BH1_TCA_PIN, BH1
      },
      {
        AS_BH1750(I2C_BH1750),
        BH2_TCA_PIN,
        BH2
      },
      {
        AS_BH1750(I2C_BH1750),
        BH3_TCA_PIN,
        BH3
      },
      {
        AS_BH1750(I2C_BH1750),
        BH4_TCA_PIN,
        BH4
      },
      {
        AS_BH1750(I2C_BH1750),
        BH5_TCA_PIN,
        BH5
      },
      {
        AS_BH1750(I2C_BH1750),
        BH6_TCA_PIN,
        BH6
      }
    };

    Sd2Card card;
    SdVolume volume;
    SdFile root;

    /*!
     *	stores all avaliable devices
     *	LSB		0	TCAmain
     *	 |		1	TCAhead
     *	 |		2	Ina1
     *	 |		3	Ina2
     *	 |		4	Ina3
     *	 |		5	Ina4
     *	 |		6	Ina5
     *	 |		7	Ina6
     *	 |		8	E52246_1
     *	 |		9	E52246_2
     *	 |		10	BH1
     *	 |		11	BH2
     *	 |		12	BH3
     *	 |		13	BH4
     *	 |		14	BH5
     *	 |		15	BH6
     *	 |		16	Pixel_1
     *	 |		17	Pixel_2
     *	 |		18	Pixel_3
     *	 |		19	Pixel_4
     *	 |		20	Pixel_5
     *	 |		21	Pixel_6
     *	 |		22	HIH6130
     *	 |		23	DS3231
     *	 |		24	FT6206
     *	 |		25	SD_CARD
     *	 |		26	MOTOR
     *	 |		27	MICROSCOPE1
     *	 |		28	MICROSCOPE2
     *	 |		29	SPEC1
     *	 |		30	SPEC2
     *   MSB		31	CHARGING
     */

    volatile uint32_t _isAvailable = 0x00000000;

};
#endif