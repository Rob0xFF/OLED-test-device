/*!
 * @file E52246.cpp
 *
 * This is a library for the E52.246 LED/OLED driver from Elmos Semiconductor SE
 *
 * The ELMOS E52.246 use I2C to communicate, additionally this library adds the
 * possibility to toggle the output via the RUN pin.
 *
 * BSD license, all text above must be included in any redistribution
 */
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "Arduino.h"
#include "Wire.h"
#include "E52246.h"


E52246::E52246(uint8_t addr, uint8_t runPin = -1)
{
  _addr = addr;
  if (runPin > 0) {
    _runPin = runPin;
  }
}

void E52246::begin(void)
{
  if (_runPin > 0) {
    pinMode(_runPin, OUTPUT);
    digitalWrite(_runPin, LOW);
  }
}

void E52246::run(void)
{
  if (_runPin > 0) {
    digitalWrite(_runPin, HIGH);
  } else {
    return;
  }
}

void E52246::stop(void)
{
  if (_runPin > 0) {
    digitalWrite(_runPin, LOW);
  } else {
    return;
  }
}

void E52246::enableChannel(uint8_t channel = 0)
{
  if (channel > 8) {
    return;
  }
  uint8_t _channelsEnabled = readRegister8(SETUP_LED_ENABLE);
  if (channel) {
    _channelsEnabled |= (1 << channel - 1);
  } else {
    _channelsEnabled = 0xFF;
  }
  writeRegister8(SETUP_LED_ENABLE, _channelsEnabled);
}

void E52246::disableChannel(uint8_t channel = 0)
{
  if (channel > 8) {
    return;
  }
  uint8_t _channelsEnabled = readRegister8(SETUP_LED_ENABLE);
  if (channel) {
    _channelsEnabled &= ~(1 << channel - 1);
  } else {
    _channelsEnabled = 0x00;
  }
  writeRegister8(SETUP_LED_ENABLE, _channelsEnabled);
}

void E52246::setMilliamps(float milliamps)
{
  milliamps = min(milliamps, 26.5);
  milliamps = max(milliamps, 1.0);
  uint8_t _currentRange = readRegister8(LED_CURR_RANGE);
  if (milliamps < 5.0 && _currentRange == 1) {
    _currentRange = 0;
    writeRegister8(LED_CURR_RANGE, _currentRange);
  }
  if (milliamps >= 5.0 && _currentRange == 0) {
    _currentRange = 1;
    writeRegister8(LED_CURR_RANGE, _currentRange);
  }
  uint8_t dacVal;
  if (_currentRange == 0) {
    dacVal = (uint8_t)((milliamps - 0.25) / 0.025);
  }
  if (_currentRange == 1) {
    dacVal = (uint8_t)((milliamps - 1.0) / 0.1);
  }
  writeRegister8(LED_DAC_VAL, dacVal);
}

void E52246::setPWM(uint8_t channel = 0, uint8_t duty = 255)
{
  switch (channel) {
    case 0:
      writeRegister8(LED_TRIM_ALL, duty);
      break;
    case 1:
      writeRegister8(LED1_TRIM, duty);
      break;
    case 2:
      writeRegister8(LED2_TRIM, duty);
      break;
    case 3:
      writeRegister8(LED3_TRIM, duty);
      break;
    case 4:
      writeRegister8(LED4_TRIM, duty);
      break;
    case 5:
      writeRegister8(LED5_TRIM, duty);
      break;
    case 6:
      writeRegister8(LED6_TRIM, duty);
      break;
    case 7:
      writeRegister8(LED7_TRIM, duty);
      break;
    case 8:
      writeRegister8(LED8_TRIM, duty);
      break;
    default:
      break;
  }
}

float E52246::getSupplyVoltage(void)
{
  float voltage;
  voltage = 33.0 * (readRegister8(VSUP)) / 255.0;
  return voltage;
}

float E52246::getTemp(void)
{
  float temp;
  temp = 25.0 + 1.5 * (206 - readRegister8(TEMP));
  return temp;
}

float E52246::getVoltage(uint8_t channel)
{
  float _voltage = 0.0;
  switch (channel) {
    case 1:
      _voltage = 33.0 * readRegister8(LED1_VOLTAGE) / 256.0;
      return _voltage;
      break;
    case 2:
      _voltage = 33.0 * readRegister8(LED2_VOLTAGE) / 256.0;
      return _voltage;
      break;
    case 3:
      _voltage = 33.0 * readRegister8(LED3_VOLTAGE) / 256.0;
      return _voltage;
      break;
    case 4:
      _voltage = 33.0 * readRegister8(LED4_VOLTAGE) / 256.0;
      return _voltage;
      break;
    case 5:
      _voltage = 33.0 * readRegister8(LED5_VOLTAGE) / 256.0;
      return _voltage;
      break;
    case 6:
      _voltage = 33.0 * readRegister8(LED6_VOLTAGE) / 256.0;
      return _voltage;
      break;
    case 7:
      _voltage = 33.0 * readRegister8(LED7_VOLTAGE) / 256.0;
      return _voltage;
      break;
    case 8:
      _voltage = 33.0 * readRegister8(LED8_VOLTAGE) / 256.0;
      return _voltage;
      break;
    default:
      return _voltage;
      break;
  }
}

uint8_t E52246::getErrStatus(uint8_t channel)
{
  uint8_t _deratingFlag = readRegister8(ERROR_STATUS);
  if (_deratingFlag & 1 << 1) {
    return 3;
  }
  uint16_t _errFlag = readRegister16(LED_STATUS);
  // test for open condition first
  if (_errFlag & 1 << channel - 1) {
    return 2;
  }
  // test for short condition
  if (_errFlag & 1 << channel + 7) {
    return 1;
  }
  return 0;
}

// ********* End of user functions **********

void E52246::writeRegister8(uint8_t reg, uint8_t data)
{
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t E52246::readRegister8(uint8_t reg)
{
  uint8_t data = 0;
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.endTransmission(false); // hold the line, send sR -> argument FALSE
  Wire.requestFrom(_addr, (uint8_t) 1);
  while (Wire.available())	{
    data = Wire.read();
  }
  return data;
}

uint16_t E52246::readRegister16(uint8_t reg)
{
  uint16_t data = 0;
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.endTransmission(false); // hold the line, send RS -> argument FALSE
  Wire.requestFrom(_addr, (uint8_t) 2);
  data = Wire.read();	// read MSB
  data <<= 8;
  data |= Wire.read(); // read LSB
  return data;
}

// Write to E2PROM. The E2PROM programming/erasing voltage must be externally provided via the ADIM pin.

uint8_t E52246::writeEEPROM()
{
  Wire.beginTransmission(_addr);
  Wire.write(EE_PROG);
  Wire.endTransmission();
}