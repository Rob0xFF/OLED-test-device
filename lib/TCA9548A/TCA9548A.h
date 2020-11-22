/*!
 * @file TCA9548A.h
 *
 * This is a library for the TCA9548A I2C Multiplexer
 *
 * The TCA9548A I2C Multiplexer use I2C to communicate.
 *
 * BSD license, all text above must be included in any redistribution
 */
#ifndef TCA9548A_h
#define TCA9548A_h

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "Arduino.h"
#include "Wire.h"


/*!
 * @brief TCA9548A main class
 */
class TCA9548A
{
  public:
    /*!
    * @brief TCA9548A class constructor
    * @param I2C address of the TCA9548A
    */
    TCA9548A(uint8_t addr);

    /*!
      * @brief Enables each I2C channel independently
      * @param [1:8] to enable channel 1-8 independently
      */
    void enableChannel(uint8_t channel);

    /*!
      * @brief Disables each I2C channel independently
      * @param [1:8] to disable channel 1-8 independently
      */
    void disableChannel(uint8_t channel);

  private:
    uint8_t _addr;
    void writeRegister8(uint8_t data);
    uint8_t readRegister8();
};
#endif