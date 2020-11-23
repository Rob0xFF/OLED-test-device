#include <Arduino.h>

#include <elapsedMillis.h>

#include "c12880.h"

inline void C12880::_pulseClock(uint8_t cycles) 
{
  for (uint8_t i = 0; i < cycles; i++) 
  {
    digitalWrite(_CLK_pin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_CLK_pin, LOW);
    delayMicroseconds(1);
  }
}

inline void C12880::_pulseClockTimed(uint32_t durationMicros) 
{
  elapsedMicros sinceStartMicros = 0;
  while (sinceStartMicros < durationMicros) 
  {
    digitalWrite(_CLK_pin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_CLK_pin, LOW);
    delayMicroseconds(1);
  }
}

void C12880::begin() 
{
  pinMode(_CLK_pin, OUTPUT);
  pinMode(_ST_pin, OUTPUT);
  pinMode(_TRG_pin, INPUT);
  digitalWrite(_CLK_pin, LOW);
  digitalWrite(_ST_pin, LOW);
  setIntegrationTime(0.020);
  setAveraging(10);
  _measureMinIntegMicros();
}

void C12880::_measureMinIntegMicros() 
{
  elapsedMicros sinceStartMicros = 0;
  _pulseClock(48);
  _minIntegMicros = sinceStartMicros;
}

void C12880::setIntegrationTime(float seconds) 
{
  _integTime = max(seconds, 0);
}

void C12880::setAveraging(uint8_t av) 
{
  _averaging = max(av, 1);
  if (_averaging > 60) _averaging = 60;
}

void C12880::readInto(uint16_t *buffer) 
{
  uint32_t durationMicros = (uint32_t) (_integTime * 1000000.0);
  durationMicros -= _minIntegMicros;
  durationMicros = max(durationMicros, 0);
  for (int i = 0; i < C12880_NUM_CHANNELS; i++) 
  {
    buffer[i] = 0;
  }
  for (uint8_t i = 0; i < _averaging; i++) 
  {
    digitalWrite(_CLK_pin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_CLK_pin, LOW);
    digitalWrite(_ST_pin, HIGH);
    delayMicroseconds(1);
    _pulseClock(3);
    _pulseClockTimed(durationMicros);
    digitalWrite(_ST_pin, LOW);
    _pulseClock(88);
    for (int i = 0; i < C12880_NUM_CHANNELS; i++) 
    {
      while (digitalRead(_TRG_pin) == LOW) {};
      buffer[i] += analogRead(_VIDEO_pin);
      _pulseClock(1);
    }
  }
  for (int i = 0; i < C12880_NUM_CHANNELS; i++) 
  {
    buffer[i] /= _averaging;
  }
}
