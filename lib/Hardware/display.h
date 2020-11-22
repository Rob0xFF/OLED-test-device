#ifndef DISPLAY_h
#define DISPLAY_h

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"
#include <Arduino_GFX.h>
#include <Arduino_TFTLCD.h>
#include <Adafruit_FT6206.h>

#if defined(__AVR_ATmega2560__)
// Using Mega2560. Import Mega pin definitions.
// Use macro expansions aggressively
#include "Mega_TFT.h"
#endif


/*!
 * @brief Display main class, inherits from Arduino_TFTLCD
 */
class Display : public Arduino_TFTLCD
{
  public:

    Display(void);

    /*!
    * @brief sets rotation of the display, x = 0 ... 3
    */
    void setRotation(uint8_t x);

    void updateChar(int16_t x, int16_t y, char oldChar, char newChar, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);

    void updateCharArray(int16_t x, int16_t y, char oldChar[], char newChar[], uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);

    inline uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
    {
      return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    };

    uint16_t readPixel(int16_t x, int16_t y);

    inline void setBacklight(uint8_t setPoint);

    void smoothSetBacklight(uint8_t setPoint);

    uint8_t brightness = 128;

  private:


};
#endif