#include <Arduino.h>
#include <gui.h>
#include <TimerOne.h>

GUI myGUI = GUI();

const uint8_t maxTouchDuration = 250;
volatile uint32_t touchDuration = 0;
volatile uint32_t touchStart = 0;
volatile uint16_t counter = 0;
volatile uint8_t touched = false;


#define IS_RELEASED false;
void tsTouched()
{
  if (counter == 0) {
    touchStart = millis();
    touched = true;
  } else {
    touchDuration = millis() - touchStart;
    if (touchDuration > maxTouchDuration) {
      counter = 0;
      return;
    }
  }
  counter ++;
}

volatile uint8_t tick = true;
#define TOCK false;
void tickTock()
{
  tick = true;
}

volatile uint8_t fastTick = true;
#define FASTTOCK false;
void fastTickTock()
{
  fastTick = true;
}

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void ( * /*func*/ )())
{
  return 0;
}

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

//void setupUSB() __attribute__((weak));
//void setupUSB() { }

int main(void)
{
  init();
  initVariant();
  Serial.begin(115200);
  myGUI.boot();
  // interupt on touchscreen event
  pinMode(FT6206_IRQ_PIN, INPUT);
  //attachInterrupt(FT6206_INT, tsTouched, FALLING);
  attachInterrupt(FT6206_INT, tsTouched, FALLING);
  // interrupt on external 1Hz clock signal
  pinMode(DS3231_INT_PIN, INPUT);
  attachInterrupt(DS3231_INT, tickTock, FALLING);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(fastTickTock);
  for (;;) {
    if (tick) {
      myGUI.update();
      tick = TOCK;
    }
    if (fastTick) {
      myGUI.fastUpdate();
      fastTick = FASTTOCK;
    }
    if (touched) {
      myGUI.updateTouch();
      touched = IS_RELEASED;
    }
    if (serialEventRun) {
      serialEventRun();
    }
    if (Serial.available()) {
      char readout = Serial.read();
      if (readout == 'S') {
        myGUI.board.saveScreenshot();
      }
    }
  }
  return 0;
}
