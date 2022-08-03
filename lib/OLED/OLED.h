#ifndef OLED_h
#define OLED_h

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"
#include <TCA9548A.h>
#include <E52246.h>
#include <INA226.h>
#include <AS_BH1750.h>

class OLED
{
  public:
    /*!
      * @brief OLED class constructor
      * @param Reference to TCA9548A Object (main board)
      * @param Reference to the E52246 Object assigned to the OLED
      * @param Reference to the INA226 Object assigned to the OLED
      * @param Reference to TCA9548A Object (sensor head)
      * @param E52246 output Pins, bitmask
      * @param TCA9548A pin the E52246 is connected to (Mainboard)
      * @param TCA9548A pin of the INA226 assigned to the OLED
      */
    OLED(TCA9548A & TCAMain, E52246 & OLEDDriver, INA226 & INA226, TCA9548A & TCAHead, AS_BH1750 & BH, uint8_t e52246_tca_pin, uint8_t e52246_pin_mask, uint8_t ina226_tca_pin, uint8_t bh_tca_pin);

    /*!
      * @brief starts and configures all periphery assigned to the OLED, must be called first
      */
    uint8_t begin(void);

    /*!
      * @brief fires OLED with given mA, other OLED on same E52246 must be disabled first.
    * @param OLED current in mA, must be between 1 - 53 mA for 2 connected channels, between 1 - 79.5 mA for 3 connected channels
    * @return returns 0 if successful, 1 - requested current out of bounds, see parameter
      */
    uint8_t on(float milliamps);

    /*!
      * @brief disables OLED
      */
    void off(void);

    /*!
      * @brief request voltage measurement
    * @return returns voltage in V
      */
    float updateVoltage(void);

    /*!
      * @brief request current measurement
    * @return returns current in mA
      */
    float updateCurrent(void);

    /*!
      * @brief request intensity measurement (not implemented yet)
    * @return returns illuminance (luminous flux per unit area) in lx
      */
    float updateIlluminance(void);

    /*!
      * @brief request error reading (not implemented yet)
    * @return returns error status of OLED
      */
    uint8_t updateErrStatus(void);

    /*!
      * @brief Configures plausibility check level for open detection
    * @param [1:8] level (V_s = 33V * level / 256)
      */
    void configOpenDetection(uint8_t level);

    /*!
      * @brief Configures check level for short detection
    * @param [1:8] level (V_s = 33V * level / 256)
      */
    void configShortDetection(uint8_t level);

    /*!
      * @brief get plausibility check level for open detection
      */
    float getConfigOpenDetection(void);

    /*!
      * @brief get check level for short detection
      */
    float getConfigShortDetection(void);

    uint8_t availChannels;
    volatile float current;
    volatile float voltage;
    volatile float illuminance;
    volatile uint8_t errStatus;
    volatile uint8_t active;

  private:

    TCA9548A & _TCAMain;
    E52246 & _OLEDDriver;
    INA226 & _INA226;
    TCA9548A & _TCAHead;
    AS_BH1750 & _BH;
    const uint8_t _e52246_tca_pin;
    const uint8_t _e52246_pin_mask;
    const uint8_t _ina226_tca_pin;
    const uint8_t _bh_tca_pin;

};

#endif