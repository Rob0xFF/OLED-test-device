#include <Screens.h>

void ScreenHeader::show(void)
{
  board.TFT.fillRect(0, 0, board.TFT.width(), 15, TFT_GRAY);
  //board.TFT.drawRect(0, 0, board.TFT.width(), board.TFT.height(), TFT_GRAY);
  board.TFT.setTextSize(1);
  board.TFT.setTextColor(TFT_WHITE, TFT_GRAY);
  board.TFT.setCursor(CLOCK_POS_X, HEAD_POS_Y);
  board.TFT.print(F("00:00:00"));
  board.TFT.setCursor(TEMP_POS_X, HEAD_POS_Y);
  board.TFT.print(F("10.0C / 10.0"));
  board.TFT.setCursor(HUM_POS_X + 24, HEAD_POS_Y);
  board.TFT.print((char) 37);
}

void ScreenHeader::update(void)
{
  board.TFT.setTextSize(1);
  board.TFT.setTextColor(TFT_WHITE, TFT_GRAY);
  char oldTime[9];
  strlcpy(oldTime, timeStr, 9);
  sprintf_P(timeStr, (PGM_P) F("%02d:%02d:%02d"), board.now.hour(), board.now.minute(), board.now.second());
  board.TFT.updateCharArray(CLOCK_POS_X, HEAD_POS_Y, oldTime, timeStr, TFT_WHITE, TFT_GRAY, 1, 1);
  if (temperature != board.temperature) {
    char oldTemp[5];
    strlcpy(oldTemp, tempStr, 5);
    temperature = board.temperature;
    char newTemp[5];
    dtostrf(temperature, 4, 1, newTemp);
    strlcpy(tempStr, newTemp, 5);
    board.TFT.updateCharArray(TEMP_POS_X, HEAD_POS_Y, oldTemp, newTemp, TFT_WHITE, TFT_GRAY, 1, 1);
  }
  if (humidity != board.humidity) {
    char oldHum[5];
    strlcpy(oldHum, humStr, 5);
    humidity = board.humidity;
    char newHum[5];
    dtostrf(humidity, 4, 1, newHum);
    strlcpy(humStr, newHum, 5);
    board.TFT.updateCharArray(HUM_POS_X, HEAD_POS_Y, oldHum, newHum, TFT_WHITE, TFT_GRAY, 1, 1);
  }
  if (justStarted) {
    justStarted = 0;
    board.hotplugStatus = 0;
    if (board.isAvailable(SD_CARD)) {
      board.TFT.setTextColor(TFT_WHITE, TFT_GRAY);
      board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_GRAY);
      board.TFT.setCursor(54, board.TFT.height() - 9);
      board.TFT.print(F("Log File: "));
      board.TFT.print(board.dataFile);
    }
  }
  if (board.hotplugStatus > 0) {
    if (showHotplug == 0) {
      showHotplug = 6;
      switch (board.hotplugStatus) {
        case 1:
          board.TFT.setTextColor(TFT_WHITE, TFT_RED);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_RED);
          board.TFT.setCursor(21, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug EXT1: microscope removed."));
          break;
        case 2:
          board.TFT.setTextColor(TFT_WHITE, TFT_RED);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_RED);
          board.TFT.setCursor(15, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug EXT1: spectrometer removed."));
          break;
        case 3:
          board.TFT.setTextColor(TFT_WHITE, TFT_GREEN);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_GREEN);
          board.TFT.setCursor(18, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug EXT1: microscope attached."));
          break;
        case 4:
          board.TFT.setTextColor(TFT_WHITE, TFT_GREEN);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_GREEN);
          board.TFT.setCursor(12, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug EXT1: spectrometer attached."));
          break;
        case 5:
          board.TFT.setTextColor(TFT_WHITE, TFT_RED);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_RED);
          board.TFT.setCursor(21, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug EXT2: microscope removed."));
          break;
        case 6:
          board.TFT.setTextColor(TFT_WHITE, TFT_RED);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_RED);
          board.TFT.setCursor(15, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug EXT2: spectrometer removed."));
          break;
        case 7:
          board.TFT.setTextColor(TFT_WHITE, TFT_GREEN);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_GREEN);
          board.TFT.setCursor(18, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug EXT2: microscope attached."));
          break;
        case 8:
          board.TFT.setTextColor(TFT_WHITE, TFT_GREEN);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_GREEN);
          board.TFT.setCursor(12, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug EXT2: spectrometer attached."));
          break;
        case 9:
          board.TFT.setTextColor(TFT_WHITE, TFT_GREEN);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_GREEN);
          board.TFT.setCursor(57, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug: SD inserted."));
          break;
        case 10:
          board.TFT.setTextColor(TFT_WHITE, TFT_RED);
          board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_RED);
          board.TFT.setCursor(60, board.TFT.height() - 9);
          board.TFT.print(F("Hotplug: SD removed."));
          break;
      }
    }
    showHotplug--;
    if (showHotplug == 0) {
      board.hotplugStatus = 0;
      if (board.isAvailable(SD_CARD)) {
        board.TFT.setTextColor(TFT_WHITE, TFT_GRAY);
        board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_GRAY);
        board.TFT.setCursor(54, board.TFT.height() - 9);
        board.TFT.print(F("Log File: "));
        board.TFT.print(board.dataFile);
      } else {
        board.TFT.fillRect(0, board.TFT.height() - 10, board.TFT.width(), board.TFT.height(), TFT_BLACK);
      }
    }
  }
}

MainMenu::~MainMenu()
{
  board.TFT.fillRect(1, 16, board.TFT.width() - 2, board.TFT.height() - 27, TFT_BLACK);
}

void MainMenu::show(void)
{
  menuEntry1.show();
  menuEntry2.show();
  menuEntry3.show();
  menuEntry4.show();
  menuEntry5.show();
  menuEntry6.show();
}


QuickTest::~QuickTest()
{
  for (uint8_t i = 0; i < 6; i++) {
    board._Pixel[i].pixel.off();
  }
  board.TFT.fillRect(1, 16, board.TFT.width() - 2, board.TFT.height() - 27, TFT_BLACK);
}

void QuickTest::show(void)
{
  for (uint8_t i = 0; i < 6; i++) {
    Button[i].show();
  }
  sPButton.setPoint = 1;
  sPButton.show();
  exitButton.show();
  startButton.show();
  selector.show();
  lifeTimeButton.show();
  board.writeTimeToLog();
  board.writeToLog(F("QuickTest Session started.\n"));
  board.writeTimeToLog();
  board.writeToLog(F("OLED I[mA] U[V] Ev[Lux] ERR\n"));
  selector.update();
  lifeTimeButton.update();
  update();
}

void QuickTest::update(void)
{
  for (uint8_t i = 0; i < 6; i++) {
    Button[i].update();
  }
  if (measurementPending > 0 && measurementPending < 31) {
    measurementPending ++;
  }
  if (measurementPending == 31) {
    if ((board.isAvailable(MICROSCOPE1) || board.isAvailable(MICROSCOPE2)) && board.microscope != nullptr) {
      board.microscope->capture();
    }
    for (uint8_t i = 0; i < 6; i++) {
      if (board._Pixel[i].pixel.active) {
        board.writeTimeToLog();
        board.writeToLog((uint8_t) (i + 1));
        board.writeToLog(F(" "));
        board.writeToLog(board._Pixel[i].pixel.current);
        board.writeToLog(F(" "));
        board.writeToLog(board._Pixel[i].pixel.voltage);
        board.writeToLog(F(" "));
        board.writeToLog(board._Pixel[i].pixel.illuminance);
        board.writeToLog(F(" "));
        uint8_t err = board._Pixel[i].pixel.errStatus;
        if (err == 0) {
          board.writeToLog(F("OK"));
        }
        if (err == 1) {
          board.writeToLog(F("SHORT"));
        }
        if (err == 2) {
          board.writeToLog(F("OPEN"));
        }
        if (err == 3) {
          board.writeToLog(F("OVERTEMP_THROTTLING"));
        }
        board.writeToLog(F("\n"));
      }
    }
    if (lifeTimeButton.selected == 0) {
      if (selector.selected < 6) {
        board._Pixel[selector.selected].pixel.off();
        Button[selector.selected].update();
      } else if (selector.selected == 6) {
        board._Pixel[0].pixel.off();
        board._Pixel[1].pixel.off();
        board._Pixel[2].pixel.off();
        board._Pixel[3].pixel.off();
        board._Pixel[4].pixel.off();
        board._Pixel[5].pixel.off();
        Button[0].update();
        Button[1].update();
        Button[2].update();
        Button[3].update();
        Button[4].update();
        Button[5].update();
      }
      measurementPending = 0;
      stopButton.hide();
      startButton.show();
    } else {
      measurementPending = 1;
    }
  }
}

Characteristic::~Characteristic()
{
  board.TFT.fillRect(1, 16, board.TFT.width() - 2, board.TFT.height() - 27, TFT_BLACK);
}

void Characteristic::show(void)
{
  minButton.setPoint = 1;
  minButton.show();
  maxButton.setPoint = 10;
  maxButton.show();
  exitButton.show();
  startButton.show();
  diagram.show();
  selector.show();
  board.writeTimeToLog();
  board.writeToLog(F("I-V Measurement Session started.\n"));
  selector.update();
}

void Characteristic::update()
{
  if (measuring) {
    switch (measurementPhase) {
      case 0:
        if (minButton.setPoint > maxButton.setPoint) {
          float temp = minButton.setPoint;
          minButton.setPoint = maxButton.setPoint;
          maxButton.setPoint = temp;
          minButton.update();
          maxButton.update();
        }
        board.writeTimeToLog();
        board.writeToLog(F("Measurement started: OLED "));
        board.writeToLog((uint8_t) (selector.selected + 1));
        board.writeToLog(F("\n"));
        board.writeTimeToLog();
        board.writeToLog(F("I[mA] U[V] Ev[Lux] ERR\n"));
        current = minButton.setPoint;
        board._Pixel[selector.selected].pixel.on(current);
        measurementPhase++;
        break;
      case 1:
        measurementPhase++;
        current += (maxButton.setPoint - minButton.setPoint) / 16.0;
        break;
      case 2:
        measurementPhase++;
        break;
      case 3:
        diagram.addDatapoint(board._Pixel[selector.selected].pixel.current, board._Pixel[selector.selected].pixel.voltage, board._Pixel[selector.selected].pixel.illuminance, datapoint);
        diagram.drawData();
        board.writeTimeToLog();
        board.writeToLog(board._Pixel[selector.selected].pixel.current);
        board.writeToLog(F(" "));
        board.writeToLog(board._Pixel[selector.selected].pixel.voltage);
        board.writeToLog(F(" "));
        board.writeToLog(board._Pixel[selector.selected].pixel.illuminance);
        board.writeToLog(F(" "));
        uint8_t err = board._Pixel[selector.selected].pixel.errStatus;
        if (err == 0) {
          board.writeToLog(F("OK"));
        }
        if (err == 1) {
          board.writeToLog(F("SHORT"));
        }
        if (err == 2) {
          board.writeToLog(F("OPEN"));
        }
        if (err == 3) {
          board.writeToLog(F("OVERTEMP_THROTTLING"));
        }
        board.writeToLog(F("\n"));
        datapoint++;
        board._Pixel[selector.selected].pixel.on(current);
        measurementPhase = 1;
        break;
    }
    if ((current > maxButton.setPoint && current > minButton.setPoint) || (current < minButton.setPoint && current < maxButton.setPoint)) {
      stopMeasurement();
    }
  }
}

void Characteristic::stopMeasurement(void)
{
  datapoint = 0;
  current = minButton.setPoint;
  board._Pixel[selector.selected].pixel.off();
  measuring = 0;
  measurementPhase = 0;
  stopButton.hide();
  startButton.show();
  board.writeTimeToLog();
  board.writeToLog(F("I-V Measurement done.\n"));
}

Spectrum::~Spectrum()
{
  board.TFT.fillRect(1, 16, board.TFT.width() - 2, board.TFT.height() - 27, TFT_BLACK);
}

void Spectrum::show(void)
{
  if (board.spectrometer != nullptr) {
    captureButton.show();
  }
  diagram.show();
  diagram._myXMin = 300;
  diagram._myXMax = 890;
  diagram._myY1Min = 100;
  diagram._myY1Max = 1020;
  diagram._myY2Min = 100;
  diagram._myY2Max = 1020;
  exitButton.show();
  averagingButton.setPoint = 10;
  averagingButton.show();
  sPButton.setPoint = 1;
  sPButton.show();
  iTButton.setPoint = 100;
  iTButton.show();
  selector.show();
  selector.update();
  board.writeTimeToLog();
  board.writeToLog(F("Spectrometer Session started.\n"));
}

void Spectrum::update(void)
{
  if (measuring) {
    switch (measurementPhase) {
      case 0:
        board._Pixel[selector.selected].pixel.on(sPButton.setPoint);
        measurementPhase++;
        break;
      case 1:
        measurementPhase++;
        break;
      case 2:
        measurementPhase++;
        break;
      case 3:
        board.brightnessSetPoint = 0;
        if (board.brightnessSetPoint != board.TFT.brightness) {
          return;
        }
        board.writeTimeToLog();
        board.writeToLog(F("Data aquisition started: OLED "));
        board.writeToLog((uint8_t) (selector.selected + 1));
        board.writeToLog(F(", I = "));
        board.writeToLog(board._Pixel[selector.selected].pixel.current);
        board.writeToLog(F("mA, U = "));
        board.writeToLog(board._Pixel[selector.selected].pixel.voltage);
        board.writeToLog(F("V, ERR: "));
        uint8_t err = board._Pixel[selector.selected].pixel.errStatus;
        if (err == 0) {
          board.writeToLog(F("OK"));
        }
        if (err == 1) {
          board.writeToLog(F("SHORT"));
        }
        if (err == 2) {
          board.writeToLog(F("OPEN"));
        }
        if (err == 3) {
          board.writeToLog(F("OVERTEMP_THROTTLING"));
        }
        board.writeToLog(F(", t(integ) = "));
        board.writeToLog(iTButton.setPoint);
        board.writeToLog(F("ms"));
        board.writeToLog(F(", n(average) = "));
        board.writeToLog(averagingButton.setPoint);
        board.writeToLog(F("x"));
        board.writeToLog(F("\n\nlambda[nm] intensity[a.u.]\n"));
        diagram.clear();
        board.spectrometer -> setAveraging((uint8_t) averagingButton.setPoint);
        board.spectrometer -> setIntegTime(iTButton.setPoint / 1000.0f);
        board.spectrometer -> capture();
        board.spectrometer -> read();
        for (uint16_t i = 0; i < 288; i++) {
          long buf = pgm_read_dword(&(wavelengths[i]));
          if (board.spectrometer -> intensities[i] < 980) {
            diagram.drawDataPoint((float) (buf / 100.0), board.spectrometer -> intensities[i], 1, 1);
          } else {
            diagram.drawDataPoint((float) (buf / 100.0), board.spectrometer -> intensities[i], 2, 1);
          }
        }
        board.logSpectrum();
        board.writeToLog(F("\n"));
        stopMeasurement();
        break;
    }
  }
}

void Spectrum::stopMeasurement(void)
{
  board.brightnessSetPoint = 128;
  board._Pixel[selector.selected].pixel.off();
  measuring = 0;
  measurementPhase = 0;
  stopButton.hide();
  captureButton.show();
}

AngleScan::~AngleScan()
{
  board.TFT.fillRect(1, 16, board.TFT.width() - 2, board.TFT.height() - 27, TFT_BLACK);
  board.stepper->stop();
}

void AngleScan::show(void)
{
  startButton.show();
  exitButton.show();
}

ClockSet::~ClockSet()
{
  board.TFT.fillRect(1, 16, board.TFT.width() - 2, board.TFT.height() - 27, TFT_BLACK);
}

void ClockSet::show()
{
  exitButton.show();
  setButton.show();
  hourButton.setPoint = board.now.hour();
  minuteButton.setPoint = board.now.minute();
  secondButton.setPoint = board.now.second();
  yearButton.setPoint = board.now.year() - 2000;
  monthButton.setPoint = board.now.month();
  dayButton.setPoint = board.now.day();
  hourButton.show();
  minuteButton.show();
  secondButton.show();
  yearButton.show();
  monthButton.show();
  dayButton.show();
  text1.show();
  text2.show();
}

Info::~Info()
{
  board.TFT.fillRect(1, 16, board.TFT.width() - 2, board.TFT.height() - 27, TFT_BLACK);
}

void Info::show(void)
{
  exitButton.show();
  above.show();
  below.show();
  logo.show();
}
