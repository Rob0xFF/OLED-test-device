/*!
 * @file TCA9548A.h
 *
 * This is a library for the TCA9548A I2C Multiplexer
 *
 * The TCA9548A I2C Multiplexer use I2C to communicate.
 *
 * BSD license, all text above must be included in any redistribution
 */
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "Arduino.h"
#include "Wire.h"
#include "TCA9548A.h"


TCA9548A::TCA9548A(uint8_t addr)
{
  _addr = addr;
}

void TCA9548A::enableChannel(uint8_t channel)
{
  if (channel > 7) {
    return;
  }
  uint8_t _channelsEnabled = readRegister8();
  _channelsEnabled |= (1 << channel);
  writeRegister8(_channelsEnabled);
}

void TCA9548A::disableChannel(uint8_t channel)
{
  if (channel > 7) {
    return;
  }
  uint8_t _channelsEnabled = readRegister8();
  _channelsEnabled &= ~(1 << channel);
  writeRegister8(_channelsEnabled);
}

// ********* End of user functions **********

void TCA9548A::writeRegister8(uint8_t data)
{
  Wire.beginTransmission(_addr);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t TCA9548A::readRegister8()
{
  uint8_t data = 0;
  Wire.requestFrom(_addr, (uint8_t) 1);
  while (Wire.available())	{
    data = Wire.read();
  }
  return data;
}


