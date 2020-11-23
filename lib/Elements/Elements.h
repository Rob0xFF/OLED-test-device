#ifndef ELEMENTS_h
#define ELEMENTS_h

#include <OLED.h>
#include <new.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"
#include <TCA9548A.h>
#include <E52246.h>
#include <INA226.h>
#include <AS_BH1750.h>
#include <HIH6130.h>
#include <DS3231.h>
#include <display.h>
#include "glcdfont.c"
#include <Adafruit_FT6206.h>

#define HEAD_POS_Y 4
#define CLOCK_POS_X 3
#define TEMP_POS_X	156
#define HUM_POS_X  204

#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define TFT_GRAY 0x0000//0x630C
#define TFT_BROWN 0x1924
#define TFT_OLIVE 0x234D
#define TFT_GREEN 0x9DAA
#define TFT_RED 0xD9E2
#define TFT_ORANGE 0xFC60

#include <board.h>

class XYDiagram
{
  public:

    XYDiagram(Board & myBoard, const char * xCap, const char * y1Cap, const char * y2Cap, const int16_t x, const int16_t y, const int16_t width, const int16_t height) : board(myBoard), _myXCap(xCap), _myY1Cap(y1Cap), _myY2Cap(y2Cap), _myX(x), _myY(y), _myWidth(width), _myHeight(height) {};

    void show(void);

    void addDatapoint(float x, float y1, float y2, uint8_t number);

    void drawDataPoint(float x, float y, uint8_t axis, uint8_t radius);

    void drawData();

    void update(void);

    void clear(void);

    Board & board;

    float _myXMin = 0;
    float _myXMax = 0;
    float _myY1Min = 0;
    float _myY1Max = 0;
    float _myY2Min = 0;
    float _myY2Max = 0;

    float dataPoint[16][3];

  private:

    const char * _myXCap;
    const char * _myY1Cap;
    const char * _myY2Cap;

    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;

};

class rButton
{
  public:

    rButton(Board & myBoard, const float setPointMin, const float setPointMax, const float increment, const char * unit, const char * format, const int16_t x, const int16_t y, const int16_t width, const int16_t height, const uint8_t dir) : board(myBoard), setPointMin(setPointMin), setPointMax(setPointMax), _increment(increment), _unit(unit), _format(format), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myDir(dir)
    {
    };

    void show(void);

    void update(void);

    uint8_t touched(int16_t x, int16_t y);

    void touchHandle(uint8_t dir);

    Board & board;

    float setPoint = 0;

  private:

    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;

    const float setPointMin;
    const float setPointMax;
    const float _increment;
    const uint8_t _myDir;
    const char * _unit;
    const char * _format;
    char _caption[10];
    uint8_t _textWidth;

};

class pButton
{
  public:

    pButton(Board & myboard, const char * caption, const int16_t x, const int16_t y, const int16_t width, const int16_t height, const uint16_t color) : board(myboard), _caption(caption), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myColor(color) {};

    void show(void);

    void hide(void);

    uint8_t touched(int16_t x, int16_t y);

    Board & board;

  private:

    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;
    const uint16_t _myColor;
    const char * _caption;

};

class TextBox
{
  public:

    TextBox(Board & myboard, const char * caption, const int16_t x, const int16_t y, const int16_t width, const int16_t height) : board(myboard), _caption(caption), _myX(x), _myY(y), _myWidth(width), _myHeight(height) {};

    void show(void);

    Board & board;

  private:

    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;
    const char * _caption;

};

class sButton
{
  public:

    sButton(Board & myboard, const char * caption, const int16_t x, const int16_t y, const int16_t width, const int16_t height, const uint16_t color) : board(myboard), _caption(caption), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myColor(color) {};

    void show(void);

    void update(void);

    void hide(void);

    uint8_t touched(int16_t x, int16_t y);

    void touchHandle(void);

    Board & board;

    uint8_t selected = 0;

  private:

    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;
    const uint16_t _myColor;
    const char * _caption;

};

class OLEDSelector
{
  public:

    OLEDSelector(Board & myboard, uint8_t positions, int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) : board(myboard), _myPositions(positions), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myColor(color) {};

    void show(void);

    void update(void);

    uint8_t selectedCorr();

    uint8_t touched(int16_t x, int16_t y);

    void touchHandle(void);

    Board & board;

    uint8_t selected = 0;

  private:

    int16_t _myX;
    int16_t _myY;
    int16_t _myWidth;
    int16_t _myHeight;
    uint16_t _myColor;
    uint8_t _myPositions;

};

class OLEDButton
{
  public:

    OLEDButton(Board & myBoard, OLED & OLED, int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t index) : board(myBoard), Pixel(OLED), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myIndex(index) {};

    void show(void);

    void update(void);

    Board & board;

    OLED & Pixel;

  private:

    int16_t _myX;
    int16_t _myY;
    int16_t _myWidth;
    int16_t _myHeight;
    uint8_t _myIndex;

    float voltage = 0.0;
    char voltageStr[8] = "    0.0";
    float current = 0.0;
    char currentStr[8] = "    0.0";
    float illuminance = 0.0;
    char illuminanceStr[8] = "    0.0";
    uint8_t errStatus = 0;
    uint8_t active = 0;
};

class WHZLogo
{
  public:

    WHZLogo(Board & myBoard, int16_t x, int16_t y, int16_t width, int16_t height): board(myBoard), _myX(x), _myY(y), _myWidth(width), _myHeight(height) {};

    void show(void);

    Board & board;

  private:

    int16_t _myX;
    int16_t _myY;
    int16_t _myWidth;
    int16_t _myHeight;
};

#endif