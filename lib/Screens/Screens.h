#ifndef SCREENS_h
#define SCREENS_h

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
#include <board.h>
#include <Elements.h>

#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define TFT_GRAY 0x0000 //0x630C
#define TFT_BROWN 0x1924
#define TFT_OLIVE 0x234D
#define TFT_GREEN 0x9DAA
#define TFT_RED 0xD9E2

#define TOP_MARGIN 10
#define GRIDX 50
#define GRIDX_INTERSPACE 8
#define GRIDY 36
#define GRIDY_INTERSPACE 6

#define GRID3_INTERSPACE 10
#define GRID3 68
#define HOR 1
#define VERT 2

static uint16_t xCoord(uint8_t x){
	return x * GRIDX_INTERSPACE + (x - 1) * GRIDX;
}

static uint16_t xWidth(uint8_t w){
	return (w - 1) * GRIDX_INTERSPACE + w * GRIDX;
}

static uint16_t yCoord(uint8_t y){
	return TOP_MARGIN + y * GRIDY_INTERSPACE + (y - 1) * GRIDY;
}

static uint16_t yHeight(uint8_t h){
	return (h - 1) * GRIDY_INTERSPACE + h * GRIDY;
}

class ScreenHeader
{
  public:

    ScreenHeader(Board & myBoard): board(myBoard) {};

    void show(void);

    void update(void);

  private:

    char timeStr[9] = "00:00:00";
    char tempStr[5] = "10.0";
    char humStr[5] = "10.0";

    float temperature = 10.0;
    float humidity = 10.0;

    Board & board;
    uint8_t showHotplug = 0;
    uint8_t justStarted = 1;

};

class MainMenu
{
  public:

    MainMenu(Board & myBoard) : board(myBoard) {};

    ~MainMenu();

    void show(void);

    Board & board;

    TextBox modeBox = TextBox(board, "Mode", xCoord(1), yCoord(1), xWidth(4), yHeight(1));

    pButton menuEntry1 = pButton(board, "Quick Test", xCoord(1), yCoord(2), xWidth(2), yHeight(2), TFT_OLIVE);

    pButton menuEntry2 = pButton(board, "I-V Curve", xCoord(3), yCoord(2), xWidth(2), yHeight(2), TFT_OLIVE);

    pButton menuEntry3 = pButton(board, "Spectrum", xCoord(1), yCoord(4), xWidth(2), yHeight(2), TFT_OLIVE);

    pButton menuEntry4 = pButton(board, "Angular Scan", xCoord(3), yCoord(4), xWidth(2), yHeight(2), TFT_OLIVE);

    TextBox setupBox = TextBox(board, "Setup", xCoord(1), yCoord(6), xWidth(4), yHeight(1));

    pButton menuEntry5 = pButton(board, "Set Clock", xCoord(1), yCoord(7), xWidth(2), yHeight(1),  TFT_OLIVE);

    pButton menuEntry6 = pButton(board, "Info", xCoord(3), yCoord(7), xWidth(2), yHeight(1),  TFT_OLIVE);

  private:

};

class QuickTest
{
  public:

    QuickTest(Board & myBoard) : board(myBoard) {};

    ~QuickTest();

    void show(void);

    void update(void);

    Board & board;

    OLEDButton Button[6] =

    {
      OLEDButton(board, board._Pixel[0].pixel, xCoord(1), yCoord(1), GRID3, yHeight(2), 1),
      OLEDButton(board, board._Pixel[1].pixel, xCoord(1) + GRID3 + GRID3_INTERSPACE, yCoord(1), GRID3, yHeight(2), 2),
      OLEDButton(board, board._Pixel[2].pixel, xCoord(1) + 2 * GRID3 +  2 * GRID3_INTERSPACE, yCoord(1), GRID3, yHeight(2), 3),
      OLEDButton(board, board._Pixel[3].pixel, xCoord(1), yCoord(3), GRID3, yHeight(2), 4),
      OLEDButton(board, board._Pixel[4].pixel, xCoord(1) + GRID3 + GRID3_INTERSPACE, yCoord(3), GRID3, yHeight(2), 5),
      OLEDButton(board, board._Pixel[5].pixel, xCoord(1) + 2 * GRID3 +  2 * GRID3_INTERSPACE, yCoord(3), GRID3, yHeight(2), 6)
    };

		rButton sPButton = rButton(board, 1.0, 79.5, 0.5, "mA", "%1.1f%s", xCoord(1), yCoord(5), xWidth(4), yHeight(1), HOR);

    sButton lifeTimeButton = sButton(board, "LifeTime", xCoord(1), yCoord(6), xWidth(2), yHeight(1), TFT_OLIVE);

    rButton timeButton = rButton(board, 5.0, 60.0, 5, "s", "%1.0f%s", xCoord(3), yCoord(6), xWidth(2), yHeight(1), HOR);

    OLEDSelector selector = OLEDSelector(board, 7, xCoord(1), yCoord(7), xWidth(1), yHeight(1), TFT_OLIVE);

    pButton startButton = pButton(board, "Start", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_GREEN);

    pButton stopButton = pButton(board, "Stop", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_RED);

    pButton exitButton = pButton(board, "EXIT->", xCoord(4), yCoord(7), xWidth(1), yHeight(1), TFT_RED);

    uint8_t isLifeTime = 0;

    uint8_t measurementPending = 0;

  private:

};

class Characteristic
{
  public:

    Characteristic(Board & myBoard) : board(myBoard) {};

    ~Characteristic();

    void show(void);

    void update(void);

    void stopMeasurement(void);

    Board & board;

    XYDiagram diagram = XYDiagram(board, "I[mA]", "U[V]", "Ev[Lux]", xCoord(1), yCoord(1), xWidth(4), yHeight(4));

    rButton minButton = rButton(board, 1.0, 79.0, 0.5, "mA", "%1.1f%s", xCoord(1), yCoord(6), xWidth(2), yHeight(1), HOR);

    rButton maxButton = rButton(board, 1.5, 79.5, 0.5, "mA", "%1.1f%s", xCoord(3), yCoord(6), xWidth(2), yHeight(1), HOR);

    OLEDSelector selector = OLEDSelector(board, 6, xCoord(1), yCoord(7), xWidth(1), yHeight(1), TFT_OLIVE);

    pButton startButton = pButton(board, "Start", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_GREEN);

    pButton stopButton = pButton(board, "Stop", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_RED);

    pButton exitButton = pButton(board, "EXIT->", xCoord(4), yCoord(7), xWidth(1), yHeight(1), TFT_RED);

    float current;

    uint8_t measuring = 0;
    uint8_t measurementPhase = 0;
    uint8_t datapoint = 0;

    float minCurrent = 1.0;
    float maxCurrent = 20.0;
    float currentInterval = 1.0;

  private:

};

class Spectrum
{
  public:

    Spectrum(Board & myBoard) : board(myBoard) {};

    ~Spectrum();

    void show(void);

    void update(void);

    void stopMeasurement(void);

    Board & board;

    XYDiagram diagram = XYDiagram(board, "l[nm]", "I[a.u.]", " ", xCoord(1), yCoord(1), xWidth(4), yHeight(4));

    rButton sPButton = rButton(board, 1.0, 79.5, 0.5, "mA", "%1.1f%s", xCoord(1), yCoord(5), xWidth(4), yHeight(1), HOR);

    rButton iTButton = rButton(board, 5, 99995, 5, "ms", "%1.0f%s", xCoord(1), yCoord(6), xWidth(2), yHeight(1), HOR);

    rButton averagingButton = rButton(board, 1, 60, 1, "x", "%1.0f%s", xCoord(3), yCoord(6), xWidth(2), yHeight(1), HOR);

    OLEDSelector selector = OLEDSelector(board, 6, xCoord(1), yCoord(7), xWidth(1), yHeight(1), TFT_OLIVE);

    pButton captureButton = pButton(board, "Capture", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_GREEN);

    pButton stopButton = pButton(board, "Stop", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_RED);

    pButton exitButton = pButton(board, "Exit->", xCoord(4), yCoord(7), xWidth(1), yHeight(1), TFT_RED);

    uint8_t measuring = 0;
    uint8_t measurementPhase = 0;

  private:

};

class AngleScan
{
  public:

    AngleScan(Board & myBoard) : board(myBoard) {};

    ~AngleScan();

    void show(void);

    Board & board;

    pButton startButton = pButton(board, "Start", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_GREEN);

    pButton exitButton = pButton(board, "EXIT->", xCoord(4), yCoord(7), xWidth(1), yHeight(1), TFT_RED);

  private:

};

class ClockSet
{
  public:

    ClockSet(Board & myBoard) : board(myBoard) {};

    ~ClockSet();

    void show(void);

    Board & board;

    TextBox text1 = TextBox(board, "hh:mm:ss", xCoord(1), yCoord(1), xWidth(1), yHeight(3));

    rButton hourButton = rButton(board, 0, 23, 1, "h", "%02.0f%s", xCoord(2), yCoord(1), xWidth(1), yHeight(3), VERT);

    rButton minuteButton = rButton(board, 0, 59, 1, "m", "%02.0f%s", xCoord(3), yCoord(1), xWidth(1), yHeight(3), VERT);

    rButton secondButton = rButton(board, 0, 59, 1, "s", "%02.0f%s", xCoord(4), yCoord(1), xWidth(1), yHeight(3), VERT);

    TextBox text2 = TextBox(board, "YY:MM:DD", xCoord(1), yCoord(4), xWidth(1), yHeight(3));

    rButton yearButton = rButton(board, 20, 99, 1, "", "%02.0f%s", xCoord(2), yCoord(4), xWidth(1), yHeight(3), VERT);

    rButton monthButton = rButton(board, 1, 12, 1, "", "%02.0f%s", xCoord(3), yCoord(4), xWidth(1), yHeight(3), VERT);

    rButton dayButton = rButton(board, 1, 31, 1, "", "%02.0f%s", xCoord(4), yCoord(4), xWidth(1), yHeight(3), VERT);

    pButton setButton = pButton(board, "Set", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_GREEN);

    pButton exitButton = pButton(board, "EXIT->", xCoord(4), yCoord(7), xWidth(1), yHeight(1), TFT_RED);

  private:

};

class Info
{
  public:

    Info(Board & myBoard) : board(myBoard) {};

    ~Info();

    void show(void);

    Board & board;

    TextBox above = TextBox(board, "OLED Test Device", xCoord(1), yCoord(1), xWidth(4), yHeight(2));

    WHZLogo logo = WHZLogo(board, xCoord(2), yCoord(3));

    TextBox below = TextBox(board, "2020 AG Nano (WHZ)", xCoord(1), yCoord(6), xWidth(4), yHeight(1));

    pButton exitButton = pButton(board, "EXIT->", xCoord(2), yCoord(7), xWidth(2), yHeight(1), TFT_RED);

  private:

};

#endif