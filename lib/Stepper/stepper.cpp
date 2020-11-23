#include <stepper.h>

void Stepper::moveTo(float degrees)
{
  setPointPosition = (int16_t) (degrees * microsteps / 1.8);
  if (setPointPosition > position) {
    setDirection(1);
  }
  if (setPointPosition < position) {
    setDirection(0);
  }
  digitalWrite(_nEnable, LOW);
  moving = 1;
}

void Stepper::stop(void)
{
  if (moving) {
    digitalWrite(_nEnable, HIGH);
    moving = 0;
  }
}

float Stepper::getPosition(void)
{
  return (float) (position * 1.8f / microsteps);
}

void Stepper::setDirection(uint8_t direction)
{
  if (direction == 0) {
    digitalWrite(_dir, LOW);
  }
  if (direction == 1) {
    digitalWrite(_dir, HIGH);
  }
}

void Stepper::searchLimit(void)
{
}

void Stepper::fastUpdate(void)
{
  if (setPointPosition != position) {
    digitalWrite(_step, HIGH);
    delayMicroseconds(2);
    digitalWrite(_step, LOW);
    if (setPointPosition > position) {
      position += 1;
    }
    if (setPointPosition < position) {
      position -= 1;
    }
  }
  if (setPointPosition == position && moving == 1) {
    stop();
  }
}