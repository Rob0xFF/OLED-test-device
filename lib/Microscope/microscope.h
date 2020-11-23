#ifndef MICROSCOPE_h
#define MICROSCOPE_h

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"

class Microscope
{
  public:

    Microscope(HardwareSerial & sHandler) : serialHandler(sHandler)
    {
    };

    ~Microscope()
    {
    };

    uint8_t zoomIn(void);

    uint8_t zoomOut(void);

    uint8_t togglePhotoVideo(void);

    uint8_t capture(void);

    uint8_t stopVideoCapture(void);

    uint8_t playback(void);

    HardwareSerial & serialHandler;

  private:

    uint8_t _isCapturingVideo = 0;

    uint8_t _isPhoto = 1;

    const uint8_t serialTimeout = 100;

};

#endif