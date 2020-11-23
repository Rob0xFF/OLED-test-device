#ifndef STEPPER_h
#define STEPPER_h

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"

class Stepper
{
  public:

    Stepper(uint8_t nEnable, uint8_t step, uint8_t dir, uint8_t limit) : _nEnable(nEnable), _step(step), _dir(dir), _limit(limit)
    {
      pinMode(_dir, OUTPUT);
      digitalWrite(_dir, HIGH);
      pinMode(_step, OUTPUT);
      digitalWrite(_step, LOW);
      pinMode(_nEnable, OUTPUT);
      digitalWrite(_nEnable, HIGH);
      pinMode(_limit, INPUT_PULLUP);
    };

    ~Stepper()
    {
      digitalWrite(_nEnable, HIGH);
    };

    void moveTo(float degrees);

    void stop();

    float getPosition(void);

    void setDirection(uint8_t direction);

    void fastUpdate(void);

    void searchLimit(void);

  private:

    uint8_t moving = 0;

    uint8_t _nEnable, _step, _dir, _limit;

    const uint8_t microsteps = 1;

    int16_t position = 0;

    int16_t setPointPosition = 0;

};

#endif