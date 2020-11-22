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

#define TOP_MARGIN 15
#define TOP_MARGIN6 20
#define GRID6_INTERSPACE 6
#define GRID6 33
#define GRID5_INTERSPACE 5
#define GRID5 42
#define GRID4_INTERSPACE 8
#define GRID4 50
#define GRID3_INTERSPACE 10
#define GRID3 68
#define HOR 1
#define VERT 2

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

    pButton menuEntry1 = pButton(board, "Quick Test", GRID4_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE, GRID4_INTERSPACE + 2 * GRID4, GRID4_INTERSPACE + 2 * GRID4, TFT_OLIVE);

    pButton menuEntry2 = pButton(board, "I-V Curve", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN + GRID4_INTERSPACE, GRID4_INTERSPACE + 2 * GRID4, GRID4_INTERSPACE + 2 * GRID4, TFT_OLIVE);

    pButton menuEntry3 = pButton(board, "Spectrum", GRID4_INTERSPACE, TOP_MARGIN + 3 * GRID4_INTERSPACE + 2 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4_INTERSPACE + 2 * GRID4, TFT_OLIVE);

    pButton menuEntry4 = pButton(board, "Angular Scan", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN + 3 * GRID4_INTERSPACE + 2 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4_INTERSPACE + 2 * GRID4, TFT_OLIVE);

    pButton menuEntry5 = pButton(board, "Set Clock", GRID4_INTERSPACE, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4,  TFT_OLIVE);

    pButton menuEntry6 = pButton(board, "Info", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4,  TFT_OLIVE);

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
      OLEDButton(board, board._Pixel[0].pixel, GRID4_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE, GRID3, GRID3, 1),
      OLEDButton(board, board._Pixel[1].pixel, GRID4_INTERSPACE + GRID3 + GRID3_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE, GRID3, GRID3, 2),
      OLEDButton(board, board._Pixel[2].pixel, GRID4_INTERSPACE + 2 * GRID3 +  2 * GRID3_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE, GRID3, GRID3, 3),
      OLEDButton(board, board._Pixel[3].pixel, GRID4_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE + GRID3 + GRID3_INTERSPACE, GRID3, GRID3, 4),
      OLEDButton(board, board._Pixel[4].pixel, GRID4_INTERSPACE + GRID3 + GRID3_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE + GRID3 + GRID3_INTERSPACE, GRID3, GRID3, 5),
      OLEDButton(board, board._Pixel[5].pixel, GRID4_INTERSPACE + 2 * GRID3 +  2 * GRID3_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE + GRID3 + GRID3_INTERSPACE, GRID3, GRID3, 6)
    };


    pButton startButton = pButton(board, "Start", 2 * GRID4_INTERSPACE + GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4, TFT_GREEN);

    pButton stopButton = pButton(board, "Stop", 2 * GRID4_INTERSPACE + GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4, TFT_RED);

    pButton exitButton = pButton(board, "EXIT->", 4 * GRID4_INTERSPACE + 3 * GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4, GRID4, TFT_RED);

    sButton lifeTimeButton = sButton(board, "LifeTime", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN + 4 * GRID4_INTERSPACE + 3 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4, TFT_OLIVE);

    rButton sPButton = rButton(board, 1.0, 79.5, 0.5, "mA", "%1.1f%s", GRID4_INTERSPACE, TOP_MARGIN + 4 * GRID4_INTERSPACE + 3 * GRID4, GRID4_INTERSPACE + 2 * GRID4,  GRID4, HOR);

    OLEDSelector selector = OLEDSelector(board, 7, GRID4_INTERSPACE, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4, GRID4, TFT_OLIVE);

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

    XYDiagram diagram = XYDiagram(board, "I[mA]", "U[V]", "Ev[Lux]", GRID4_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE, 3 * GRID4_INTERSPACE + 4 * GRID4, 2 * GRID4_INTERSPACE + 3 * GRID4);

    pButton exitButton = pButton(board, "EXIT->", 4 * GRID4_INTERSPACE + 3 * GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4, GRID4, TFT_RED);

    pButton startButton = pButton(board, "Start", 2 * GRID4_INTERSPACE +  GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4, TFT_GREEN);

    pButton stopButton = pButton(board, "Stop", 2 * GRID4_INTERSPACE +  GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4, TFT_RED);

    rButton minButton = rButton(board, 1.0, 79.0, 0.5, "mA", "%1.1f%s", GRID4_INTERSPACE, TOP_MARGIN + 4 * GRID4_INTERSPACE + 3 * GRID4, GRID4_INTERSPACE + 2 * GRID4,  GRID4, HOR);

    rButton maxButton = rButton(board, 1.5, 79.5, 0.5, "mA", "%1.1f%s", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN + 4 * GRID4_INTERSPACE + 3 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4, HOR);

    OLEDSelector selector = OLEDSelector(board, 6, GRID4_INTERSPACE, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4, GRID4, TFT_OLIVE);

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

    XYDiagram diagram = XYDiagram(board, "l[nm]", "I[a.u.]", " ", GRID4_INTERSPACE, TOP_MARGIN6 + GRID6_INTERSPACE, 3 * GRID4_INTERSPACE + 4 * GRID4, 3 * GRID6_INTERSPACE + 4 * GRID6);

    pButton captureButton = pButton(board, "Capture", 2 * GRID4_INTERSPACE + GRID4, TOP_MARGIN6 + 7 * GRID6_INTERSPACE + 6 * GRID6, 1 * GRID4_INTERSPACE + 2 * GRID4, GRID6, TFT_GREEN);

    pButton stopButton = pButton(board, "Stop", 2 * GRID4_INTERSPACE + GRID4, TOP_MARGIN6 + 7 * GRID6_INTERSPACE + 6 * GRID6, 1 * GRID4_INTERSPACE + 2 * GRID4, GRID6, TFT_RED);

    pButton exitButton = pButton(board, "->", 4 * GRID4_INTERSPACE + 3 * GRID4, TOP_MARGIN6 + 7 * GRID6_INTERSPACE + 6 * GRID6, GRID4, GRID6, TFT_RED);

    rButton averagingButton = rButton(board, 1, 60, 1, "x", "%1.0f%s", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN6 + 5 * GRID6_INTERSPACE + 4 * GRID6, GRID4_INTERSPACE + 2 * GRID4, GRID6, HOR);

    rButton sPButton = rButton(board, 1.0, 79.5, 0.5, "mA", "%1.1f%s", GRID4_INTERSPACE, TOP_MARGIN6 + 6 * GRID6_INTERSPACE + 5 * GRID6, GRID4_INTERSPACE + 2 * GRID4,  GRID6, HOR);

    rButton iTButton = rButton(board, 5, 99995, 5, "ms", "%1.0f%s", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN6 + 6 * GRID6_INTERSPACE + 5 * GRID6, GRID4_INTERSPACE + 2 * GRID4,  GRID6, HOR);

    OLEDSelector selector = OLEDSelector(board, 6, GRID4_INTERSPACE, TOP_MARGIN6 + 7 * GRID6_INTERSPACE + 6 * GRID6, GRID4, GRID6, TFT_OLIVE);

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

    pButton startButton = pButton(board, "Start", 2 * GRID4_INTERSPACE + GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4, TFT_GREEN);

    pButton exitButton = pButton(board, "EXIT->", 4 * GRID4_INTERSPACE + 3 * GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4, GRID4, TFT_RED);

  private:

};

class ClockSet
{
  public:

    ClockSet(Board & myBoard) : board(myBoard) {};

    ~ClockSet();

    void show(void);

    Board & board;

    rButton hourButton = rButton(board, 0, 23, 1, "h", "%02.0f%s", GRID4_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE, GRID4, GRID4_INTERSPACE + 2 * GRID4, VERT);

    rButton minuteButton = rButton(board, 0, 59, 1, "m", "%02.0f%s", 2 * GRID4_INTERSPACE + GRID4, TOP_MARGIN + GRID4_INTERSPACE, GRID4, GRID4_INTERSPACE + 2 * GRID4, VERT);

    rButton secondButton = rButton(board, 0, 59, 1, "s", "%02.0f%s", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN + GRID4_INTERSPACE, GRID4, GRID4_INTERSPACE + 2 * GRID4, VERT);

    rButton yearButton = rButton(board, 20, 99, 1, "", "%02.0f%s", GRID4_INTERSPACE, TOP_MARGIN + 3 * GRID4_INTERSPACE + 2 * GRID4, GRID4, GRID4_INTERSPACE + 2 * GRID4, VERT);

    rButton monthButton = rButton(board, 1, 12, 1, "", "%02.0f%s", 2 * GRID4_INTERSPACE + GRID4, TOP_MARGIN + 3 * GRID4_INTERSPACE + 2 * GRID4, GRID4, GRID4_INTERSPACE + 2 * GRID4, VERT);

    rButton dayButton = rButton(board, 1, 31, 1, "", "%02.0f%s", 3 * GRID4_INTERSPACE + 2 * GRID4, TOP_MARGIN + 3 * GRID4_INTERSPACE + 2 * GRID4, GRID4, GRID4_INTERSPACE + 2 * GRID4, VERT);

    TextBox text1 = TextBox(board, "hh:mm:ss", 4 * GRID4_INTERSPACE + 3 * GRID4, TOP_MARGIN + GRID4_INTERSPACE, GRID4, GRID4_INTERSPACE + 2 * GRID4);

    TextBox text2 = TextBox(board, "YY:MM:DD", 4 * GRID4_INTERSPACE + 3 * GRID4, TOP_MARGIN + 3 * GRID4_INTERSPACE + 2 * GRID4, GRID4, GRID4_INTERSPACE + 2 * GRID4);

    pButton setButton = pButton(board, "Set", GRID4_INTERSPACE, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, 2 * GRID4_INTERSPACE + 3 * GRID4, GRID4, TFT_GREEN);

    pButton exitButton = pButton(board, "EXIT->", 4 * GRID4_INTERSPACE + 3 * GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4, GRID4, TFT_RED);

  private:

};

class Info
{
  public:

    Info(Board & myBoard) : board(myBoard) {};

    ~Info();

    void show(void);

    Board & board;

    TextBox above = TextBox(board, "OLED Test Device", GRID4_INTERSPACE, TOP_MARGIN + GRID4_INTERSPACE, 3 * GRID4_INTERSPACE + 4 * GRID4, GRID4);

    WHZLogo logo = WHZLogo(board, 2 * GRID4_INTERSPACE + GRID4, TOP_MARGIN + 2 * GRID4_INTERSPACE + GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4_INTERSPACE + 2 * GRID4);

    TextBox below = TextBox(board, "2020 AG Nano (WHZ)", GRID4_INTERSPACE, TOP_MARGIN + 4 * GRID4_INTERSPACE + 3 * GRID4, 3 * GRID4_INTERSPACE + 4 * GRID4, GRID4);

    pButton exitButton = pButton(board, "EXIT->", 2 * GRID4_INTERSPACE + 1 * GRID4, TOP_MARGIN + 5 * GRID4_INTERSPACE + 4 * GRID4, GRID4_INTERSPACE + 2 * GRID4, GRID4, TFT_RED);

  private:

};

#endif