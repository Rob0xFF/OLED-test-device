/*
  c12880.h - Library for interacting with the Hamamatsu C12880 microspectrometer
  Based on library originally created by Craig Wm. Versek, 2017-03-01
  - fixed integer overflow issue for larger integration times
  - removed Teensy specific code (not needed here)
  - optimized memory usage by replacing int by uint8_t
  - added support for channel-wise averaging of up to 60 measurements to improve SNR
*/

#ifndef C12880_H
#define C12880_H

#include <Arduino.h>

#define C12880_NUM_CHANNELS 288

class C12880 {

  public:

    C12880(const uint8_t TRG_pin, const uint8_t ST_pin, const uint8_t CLK_pin, const uint8_t VIDEO_pin) : _TRG_pin(TRG_pin), _ST_pin(ST_pin), _CLK_pin(CLK_pin), _VIDEO_pin(VIDEO_pin)
    {
    };

    void begin();

    void setIntegrationTime(float seconds);

    void setAveraging(uint8_t av);

    void readInto(uint16_t *buffer);

  private:

    inline void _pulseClock(uint8_t cycles);

    inline void _pulseClockTimed(uint32_t duration_micros);

    void _measureMinIntegMicros();

    volatile float _integTime;

    volatile uint8_t _averaging;

    uint16_t _minIntegMicros = 0;

    const uint8_t _TRG_pin;

    const uint8_t _ST_pin;

    const uint8_t _CLK_pin;

    const uint8_t _VIDEO_pin;

};

#endif
