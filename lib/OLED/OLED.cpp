#include <OLED.h>

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "Arduino.h"
#include "Wire.h"

#include <TCA9548A.h>
#include <E52246.h>
#include <INA226.h>
#include <AS_BH1750.h>


OLED::OLED(TCA9548A & TCAMain, E52246 & OLEDDriver, INA226 & INA226, TCA9548A & TCAHead, AS_BH1750 & BH, uint8_t e52246_tca_pin, uint8_t e52246_pin_mask, uint8_t ina226_tca_pin, uint8_t bh_tca_pin)
  : _TCAMain(TCAMain), _OLEDDriver(OLEDDriver), _INA226(INA226), _TCAHead(TCAHead), _BH(BH), _e52246_tca_pin(e52246_tca_pin), _e52246_pin_mask(e52246_pin_mask), _ina226_tca_pin(ina226_tca_pin), _bh_tca_pin(bh_tca_pin)
{
  current = 0.0;
  voltage = 0.0;
  illuminance = 0.0;
  errStatus = 0;
  for (uint8_t i = 0; i < 8; i++) {
    if (_e52246_pin_mask & 1 << i) {
      availChannels++;
    }
  }
}

uint8_t OLED::begin(void)
{
  _OLEDDriver.begin();
  off();
  _TCAMain.enableChannel(_ina226_tca_pin);
  _INA226.begin();
  _INA226.configure(INA226_AVERAGES_128, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
  _INA226.calibrate(0.1, 0.1);
  _TCAMain.disableChannel(_ina226_tca_pin);
  _TCAHead.enableChannel(_bh_tca_pin);
  _BH.begin(RESOLUTION_HIGH, false);
  _TCAHead.disableChannel(_bh_tca_pin);
  return 1;
}

uint8_t OLED::on(float milliamps)
{
  _TCAMain.enableChannel(_e52246_tca_pin);
  uint8_t channels = 0;
  if (milliamps <= 26.5 && milliamps >= 1.0) {
    channels = 1;
  } else if (milliamps > 26.5 && milliamps <= 53.0) {
    channels = 2;
    milliamps /= 2.0;
  } else if (milliamps > 53.0 && milliamps <= 79.5 && availChannels > 2) {
    channels = 3;
    milliamps /= 3.0;
  } else {
    _TCAMain.disableChannel(_e52246_tca_pin);
    return 1; // requested current out of bounds
  }
  _OLEDDriver.setMilliamps(milliamps);
  uint8_t unused = availChannels - channels;
  // populate used driver channels
  uint8_t i = 0;
  while (channels > 0) {
    if (_e52246_pin_mask & 1 << i) {
      _OLEDDriver.enableChannel(i + 1);
      channels--;
    }
    i++;
  }
  while (unused > 0) {
    if (_e52246_pin_mask & 1 << i) {
      _OLEDDriver.disableChannel(i + 1);
      unused--;
    }
    i++;
  }
  _TCAMain.disableChannel(_e52246_tca_pin);
  _OLEDDriver.run();
  active = 1;
  return 0;
}

void OLED::off(void)
{
  _TCAMain.enableChannel(_e52246_tca_pin);
  for (uint8_t i = 0; i < 8; i++) {
    if (_e52246_pin_mask & 1 << i) {
      _OLEDDriver.disableChannel(i + 1);
    }
  }
  _TCAMain.disableChannel(_e52246_tca_pin);
  _OLEDDriver.stop();
  current = 0.0;
  voltage = 0.0;
  active = 0;
}

float OLED::updateVoltage(void)
{
  _TCAMain.enableChannel(_ina226_tca_pin);
  voltage = _INA226.readBusVoltage();
  _TCAMain.disableChannel(_ina226_tca_pin);
  return voltage;
}

float OLED::updateCurrent(void)
{
  _TCAMain.enableChannel(_ina226_tca_pin);
  current = 1000.0 * _INA226.readShuntCurrent();
  _TCAMain.disableChannel(_ina226_tca_pin);
  return current;
}

float OLED::updateIlluminance(void)
{
  _TCAHead.enableChannel(_bh_tca_pin);
  illuminance = _BH.readLightLevel();
  _TCAHead.disableChannel(_bh_tca_pin);
  return illuminance;
}

uint8_t OLED::updateErrStatus(void)
{
  _TCAMain.enableChannel(_e52246_tca_pin);
  uint8_t mask = 1 << 0;
  for (uint8_t i = 0; i < 8; i++) {
    if (_e52246_pin_mask & mask) {
      errStatus = _OLEDDriver.getErrStatus(i + 1);
      _TCAMain.disableChannel(_e52246_tca_pin);
      return errStatus;
    }
    mask <<= 1;
  }
  _TCAMain.disableChannel(_e52246_tca_pin);
  errStatus = 0;
  return errStatus;
}

void OLED::configOpenDetection(uint8_t level)
{
  _TCAMain.enableChannel(_e52246_tca_pin);
	_OLEDDriver.configOpenDetection(level);
  _TCAMain.disableChannel(_e52246_tca_pin);
}

void OLED::configShortDetection(uint8_t level)
{
  _TCAMain.enableChannel(_e52246_tca_pin);
	_OLEDDriver.configShortDetection(level);
  _TCAMain.disableChannel(_e52246_tca_pin);
}


float OLED::getConfigOpenDetection(void)
{
  _TCAMain.enableChannel(_e52246_tca_pin);
	float retVal = _OLEDDriver.getConfigOpenDetection();
  _TCAMain.disableChannel(_e52246_tca_pin);
	return retVal;
}

float OLED::getConfigShortDetection(void)
{
  _TCAMain.enableChannel(_e52246_tca_pin);
	float retVal = _OLEDDriver.getConfigShortDetection();
  _TCAMain.disableChannel(_e52246_tca_pin);
	return retVal;
}


