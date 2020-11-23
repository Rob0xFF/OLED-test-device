#include <display.h>

#include "glcdfont.c"

#define TFT_BACKLIGHT 4

Display::Display(void): Arduino_TFTLCD()
{
  pinMode(TFT_BACKLIGHT, OUTPUT);
  analogWrite(TFT_BACKLIGHT, brightness);
}

// based on Adafruit_TFTLCD function
void Display::setRotation(uint8_t x)
{
  rotation = (x & 3);
  switch (rotation) {
    case 0:
    case 2:
      _width = WIDTH;
      _height = HEIGHT;
      break;
    case 1:
    case 3:
      _width = HEIGHT;
      _height = WIDTH;
      break;
  }
  // perform hardware-specific rotation operations...
  CS_ACTIVE;
  uint16_t t = 0;
  switch (rotation) {
    case 2:
      t = ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR;
      break;
    case 3:
      t = ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
      break;
    case 0:
      t = ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR;
      break;
    case 1:
      t = ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV |
          ILI9341_MADCTL_BGR;
      break;
  }
  CD_COMMAND;
  write8(ILI9341_MADCTL);
  CD_DATA;
  write8(t);
  SET_WINDOW(0, 0, _width - 1, _height - 1);
}

void Display::updateChar(int16_t x, int16_t y, char oldChar, char newChar,
                         uint16_t color, uint16_t bg, uint8_t size_x,
                         uint8_t size_y)
{
  for (int8_t i = 0; i < 5; i++) { // Char bitmap = 5 columns
    uint8_t oldline = pgm_read_byte( & font[oldChar * 5 + i]);
    uint8_t newline = pgm_read_byte( & font[newChar * 5 + i]);
    uint8_t include = ~(oldline & newline);
    for (int8_t j = 0; j < 8; j++, oldline >>= 1, newline >>= 1, include >>= 1) {
      if (newline & 1 && include & 1) {
        if (size_x == 1 && size_y == 1) {
          drawPixel(x + i, y + j, color);
        } else
          fillRect(x + i * size_x, y + j * size_y, size_x, size_y,
                   color);
      } else if (bg != color && oldline & 1 && include & 1) {
        if (size_x == 1 && size_y == 1) {
          drawPixel(x + i, y + j, bg);
        } else {
          fillRect(x + i * size_x, y + j * size_y, size_x, size_y, bg);
        }
      }
    }
  }
}

void Display::updateCharArray(int16_t x, int16_t y, char oldChar[], char newChar[],
                              uint16_t color, uint16_t bg, uint8_t size_x,
                              uint8_t size_y)
{
  if (strlen((char * ) oldChar) == strlen((char * ) newChar)) {
    for (uint8_t i = 0; i < strlen((char * ) oldChar); i++) {
      if (oldChar[i] != newChar[i]) {
        updateChar(x + i * 6 * size_x, y, oldChar[i], newChar[i], color, bg, size_x, size_y);
      }
    }
  }
}

uint16_t Display::readPixel(int16_t x, int16_t y)
{
  uint8_t rgb[3];
  SET_XY_LOCATION(x, y);
  START_READING();
  SEND_DATA;
  READY_READ;
  rgb[0] = PERMUTED_QUICK_READ;
  SEND_DATA;
  READY_READ;
  rgb[1] = PERMUTED_QUICK_READ;
  SEND_DATA;
  READY_READ;
  rgb[2] = PERMUTED_QUICK_READ;
  STOP_READING();
  return color565(rgb[0], rgb[1], rgb[2]);
}

void Display::setBacklight(uint8_t setPoint)
{
  brightness = setPoint;
  analogWrite(TFT_BACKLIGHT, brightness);
}

void Display::smoothSetBacklight(uint8_t setPoint)
{
  if (brightness > setPoint) {
    brightness--;
    analogWrite(TFT_BACKLIGHT, brightness);
  }
  if (brightness < setPoint) {
    brightness++;
    analogWrite(TFT_BACKLIGHT, brightness);
  }
}