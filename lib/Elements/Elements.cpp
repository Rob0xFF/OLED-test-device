#include <Elements.h>

void XYDiagram::show(void)
{
  board.TFT.fillRect(_myX, _myY, _myWidth, _myHeight, 0xFFFF);
  board.TFT.setTextColor(TFT_BLACK, TFT_WHITE);
  board.TFT.setCursor(_myX + 1, _myY + 1);
  board.TFT.print(_myY1Cap);
  board.TFT.setCursor(_myX + _myWidth / 2 - 6 * strlen(_myXCap) / 2, _myY + _myHeight - 8);
  board.TFT.print(_myXCap);
  board.TFT.setTextColor(TFT_RED, TFT_WHITE);
  board.TFT.setCursor(_myX + _myWidth - 6 * strlen(_myY2Cap) - 1, _myY + 1);
  board.TFT.print(_myY2Cap);
  board.TFT.drawLine(_myX, _myY + _myHeight - 10, _myX + _myWidth, _myY + _myHeight - 10, TFT_BLACK);
}

void XYDiagram::addDatapoint(float x, float y1, float y2, uint8_t number)
{
  if (number == 0) {
    for (uint8_t i = 0; i < 16; i++) {
      for (uint8_t u = 0; u < 3; u++) {
        dataPoint[i][u] = (float) 0.0;
      }
    }
    _myXMin = x - 0.5;
    _myXMax = x + 0.5;
    _myY1Min = y1 - 0.1;
    _myY1Max = y1 + 0.1;
    _myY2Min = y2 - 0.5;
    _myY2Max = y2 + 0.5;
  } else {
    if (x < _myXMin + 0.5) {
      _myXMin = x - 0.5;
    }
    if (x > _myXMax - 0.5) {
      _myXMax = x + 0.5;
    }
    if (y1 < _myY1Min + 0.1) {
      _myY1Min = y1 - 0.1;
    }
    if (y1 > _myY1Max - 0.1) {
      _myY1Max = y1 + 0.1;
    }
    if (y2 < _myY2Min + 0.5) {
      _myY2Min = y2 - 0.5;
    }
    if (y2 > _myY2Max - 0.5) {
      _myY2Max = y2 + 0.5;
    }
  }
  dataPoint[number][0] = x;
  dataPoint[number][1] = y1;
  dataPoint[number][2] = y2;
}

void XYDiagram::drawDataPoint(float x, float y, uint8_t axis, uint8_t radius)
{
  if (x <= 0.0 || y <= 0.0) {
    return;
  }
  if (axis == 1) {
    board.TFT.fillCircle(_myX + (x - _myXMin) * _myWidth / (_myXMax - _myXMin), _myY + _myHeight - 20 - ((y - _myY1Min) * (_myHeight - 31) / (_myY1Max - _myY1Min)), radius, TFT_BLACK);
  }
  if (axis == 2) {
    board.TFT.fillCircle(_myX + (x - _myXMin) * _myWidth / (_myXMax - _myXMin), _myY + _myHeight - 20 - ((y - _myY2Min) * (_myHeight - 31) / (_myY2Max - _myY2Min)), radius, TFT_RED);
  }
}

void XYDiagram::clear(void)
{
  board.TFT.fillRect(_myX, _myY + 9, _myWidth, _myHeight - 20, 0xFFFF);
}

void XYDiagram::drawData(void)
{
  clear();
  for (uint8_t i = 0; i < 16; i++) {
    drawDataPoint(dataPoint[i][0], dataPoint[i][1], 1, 2);
    drawDataPoint(dataPoint[i][0], dataPoint[i][2], 2, 2);
  }
}

void rButton::show(void)
{
  board.TFT.drawRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_WHITE);
  board.TFT.fillRoundRect(_myX + 1, _myY + 1, _myWidth - 2, _myHeight - 2, 3, TFT_OLIVE);
  board.TFT.setTextColor(TFT_WHITE, TFT_OLIVE);
  board.TFT.setTextSize(2);
  if (_myDir == 1) { //horizontal
    board.TFT.setCursor(_myX + _myWidth / 6 - 6, _myY + _myHeight / 2 - 7);
    board.TFT.print("-");
    board.TFT.setCursor(_myX + _myWidth * 5 / 6 - 6, _myY + _myHeight / 2 - 7);
    board.TFT.print("+");
  }
  if (_myDir == 2) { //vertical
    board.TFT.setCursor(_myX + _myWidth / 2 - 6, _myY + _myHeight / 6 - 7);
    board.TFT.print("+");
    board.TFT.setCursor(_myX + _myWidth / 2 - 6, _myY + _myHeight * 5 / 6 - 7);
    board.TFT.print("-");
  }
  board.TFT.setTextSize(1);
  _textWidth = snprintf(_caption, 10, _format, setPoint, _unit);
  board.TFT.setCursor(_myX + _myWidth / 2 - 6 * _textWidth / 2, _myY + _myHeight / 2 - 4);
  board.TFT.print(_caption);
}

void rButton::update(void)
{
  board.TFT.setTextSize(1);
  board.TFT.setTextColor(TFT_WHITE, TFT_OLIVE);
  board.TFT.fillRect(_myX + _myWidth / 2 - 6 * _textWidth / 2, _myY + _myHeight / 2 - 4, 6 * _textWidth, 8, TFT_OLIVE);
  board.TFT.setTextSize(1);
  _textWidth = snprintf(_caption, 10, _format, setPoint, _unit);
  board.TFT.setCursor(_myX + _myWidth / 2 - 6 * _textWidth / 2, _myY + _myHeight / 2 - 4);
  board.TFT.print(_caption);
}

uint8_t rButton::touched(int16_t x, int16_t y)
{
  if (_myDir == 2) {
    if ((x > _myX) && (x < _myX + _myWidth)) {
      if ((y > _myY) && (y < _myY + _myHeight / 3)) {
        return 1; // +
      }
      if ((y > _myY + _myHeight * 2 / 3) && (y < _myY + _myHeight)) {
        return 2; // -
      }
    }
    return 0;
  }
  if (_myDir == 1) {
    if ((y > _myY) && (y < _myY + _myHeight)) {
      if ((x > _myX) && (x < _myX + _myWidth / 3)) {
        return 2; // -
      }
      if ((x > _myX + _myWidth * 2 / 3) && (x < _myX + _myWidth)) {
        return 1; // +
      }
    }
    return 0;
  }
}

void rButton::touchHandle(uint8_t dir)
{
  if (dir == 1 && setPoint < setPointMax) {
    setPoint += _increment;
  }
  if (dir == 2 && setPoint > setPointMin) {
    setPoint -= _increment;
  }
  update();
}

void pButton::show(void)
{
  board.TFT.drawRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_WHITE);
  board.TFT.fillRoundRect(_myX + 1, _myY + 1, _myWidth - 2, _myHeight - 2, 3, _myColor);
  board.TFT.setTextColor(TFT_WHITE, _myColor);
  board.TFT.setCursor(_myX + _myWidth / 2 - (6 * strlen(_caption) / 2), _myY + _myHeight / 2 - 4);
  board.TFT.print(_caption);
}

void pButton::hide(void)
{
  board.TFT.fillRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_BLACK);
}

uint8_t pButton::touched(int16_t x, int16_t y)
{
  if ((x > _myX) && (x < _myX + _myWidth)) {
    if ((y > _myY) && (y < _myY + _myHeight)) {
      return true;
    }
  }
  return false;
}

void TextBox::show(void)
{
  board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
  board.TFT.setCursor(_myX + _myWidth / 2 - (6 * strlen(_caption) / 2), _myY + _myHeight / 2 - 4);
  board.TFT.print(_caption);
}

void sButton::show(void)
{
  board.TFT.drawRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_WHITE);
  board.TFT.fillRoundRect(_myX + 1, _myY + 1, _myWidth - 2, _myHeight - 2, 3, _myColor);
  board.TFT.drawCircle(_myX + _myWidth / 2, _myY + _myHeight / 3, 8, TFT_WHITE);
  board.TFT.setTextColor(TFT_WHITE, _myColor);
  board.TFT.setCursor(_myX + _myWidth / 2 - (6 * strlen(_caption) / 2), _myY + 2 * _myHeight / 3);
  board.TFT.print(_caption);
}

void sButton::update(void)
{
  board.TFT.fillCircle(_myX + _myWidth / 2, _myY + _myHeight / 3, 5, _myColor);
  if (selected) {
    board.TFT.fillCircle(_myX + _myWidth / 2, _myY + _myHeight / 3, 5, TFT_WHITE);
  }
}

void sButton::hide(void)
{
  board.TFT.fillRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_BLACK);
}

uint8_t sButton::touched(int16_t x, int16_t y)
{
  if ((x > _myX) && (x < _myX + _myWidth)) {
    if ((y > _myY) && (y < _myY + _myHeight)) {
      return true;
    }
  }
  return false;
}

void sButton::touchHandle(void)
{
  if (selected == 0) {
    selected = 1;
  } else if (selected == 1) {
    selected = 0;
  }
  update();
}

void OLEDSelector::show(void)
{
  board.TFT.drawRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_WHITE);
  board.TFT.fillRoundRect(_myX + 1, _myY + 1, _myWidth - 2, _myHeight - 2, 3, _myColor);
  board.TFT.drawRect(_myX + _myWidth / 2 - 11, _myY + _myHeight / 2 - 10, 6, 8, TFT_WHITE);
  board.TFT.drawRect(_myX + _myWidth / 2 - 3, _myY + _myHeight / 2 - 10, 6, 8, TFT_WHITE);
  board.TFT.drawRect(_myX + _myWidth / 2 + 5, _myY + _myHeight / 2 - 10, 6, 8, TFT_WHITE);
  board.TFT.drawRect(_myX + _myWidth / 2 - 11, _myY + _myHeight / 2 + 2, 6, 8, TFT_WHITE);
  board.TFT.drawRect(_myX + _myWidth / 2 - 3, _myY + _myHeight / 2 + 2, 6, 8, TFT_WHITE);
  board.TFT.drawRect(_myX + _myWidth / 2 + 5, _myY + _myHeight / 2 + 2, 6, 8, TFT_WHITE);
}

void OLEDSelector::update(void)
{
  uint8_t k = 0;
  for (uint8_t i = 0; i < 2; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      board.TFT.fillRect(_myX + _myWidth / 2 + 8 * j - 10, _myY + _myHeight / 2 + 12 * i - 9, 4, 6, _myColor);
      if (k == selected || selected == 6) {
        board.TFT.fillRect(_myX + _myWidth / 2 + 8 * j - 10, _myY + _myHeight / 2 + 12 * i - 9, 4, 6, TFT_WHITE);
      }
      k++;
    }
  }
}

uint8_t OLEDSelector::touched(int16_t x, int16_t y)
{
  if ((x > _myX) && (x < _myX + _myWidth)) {
    if ((y > _myY) && (y < _myY + _myHeight)) {
      return true;
    }
  }
  return false;
}

void OLEDSelector::touchHandle(void)
{
  selected++;
  if (selected == _myPositions) {
    selected = 0;
  }
  update();
}

/*!
 *  Quick Test Menu: OLED Button
 * *****************************************
 */

#define OLED_BUTTON_PADDING_LEFT 4
#define OLED_BUTTON_PADDING_TOP 22

void OLEDButton::show()
{
  board.TFT.drawRect(_myX, _myY, _myWidth, _myHeight, TFT_WHITE);
  board.TFT.fillRect(_myX + 1, _myY + 1, _myWidth - 2, _myHeight - 2, TFT_BROWN);
  board.TFT.setTextColor(TFT_WHITE, TFT_BROWN);
  board.TFT.setCursor(_myX + OLED_BUTTON_PADDING_LEFT + 1, _myY + HEAD_POS_Y);
  board.TFT.print(F("OLED "));
  board.TFT.print(_myIndex);
  board.TFT.setTextColor(TFT_WHITE, TFT_BROWN);
  board.TFT.setCursor(_myX + OLED_BUTTON_PADDING_LEFT, _myY + OLED_BUTTON_PADDING_TOP);
  board.TFT.print(F("    0.0 V "));
  board.TFT.setCursor(_myX + OLED_BUTTON_PADDING_LEFT, _myY + OLED_BUTTON_PADDING_TOP + 1 * 9);
  board.TFT.print(F("    0.0 mA"));
  board.TFT.setCursor(_myX + OLED_BUTTON_PADDING_LEFT, _myY + OLED_BUTTON_PADDING_TOP + 2 * 9);
  board.TFT.print(F("    0.0 Lx"));
  board.TFT.fillRect(_myX + 1, _myY + _myHeight - 15, _myWidth - 2, 14, TFT_BLACK);
  board.TFT.setCursor(_myX + OLED_BUTTON_PADDING_LEFT + 1, _myY + _myHeight - 15 + HEAD_POS_Y);
  board.TFT.setTextColor(TFT_GREEN);
  board.TFT.print(F("READY"));
}

void OLEDButton::update()
{
  if (voltage != Pixel.voltage) {
    char oldVolt[8];
    strlcpy(oldVolt, voltageStr, 8);
    voltage = Pixel.voltage;
    char newVolt[8];
    dtostrf(voltage, 7, 1, newVolt);
    strlcpy(voltageStr, newVolt, 8);
    board.TFT.updateCharArray(_myX + OLED_BUTTON_PADDING_LEFT, _myY + OLED_BUTTON_PADDING_TOP, oldVolt, newVolt, TFT_WHITE, TFT_BROWN, 1, 1);
  }
  if (current != Pixel.current) {
    char oldCurr[8];
    strlcpy(oldCurr, currentStr, 8);
    current = Pixel.current;
    char newCurr[8];
    dtostrf(current, 7, 1, newCurr);
    strlcpy(currentStr, newCurr, 8);
    board.TFT.updateCharArray(_myX + OLED_BUTTON_PADDING_LEFT, _myY + OLED_BUTTON_PADDING_TOP + 1 * 9, oldCurr, newCurr, TFT_WHITE, TFT_BROWN, 1, 1);
  }
  if (illuminance != Pixel.illuminance) {
    char oldIllum[8];
    strlcpy(oldIllum, illuminanceStr, 8);
    illuminance = Pixel.illuminance;
    char newIllum[8];
    dtostrf(illuminance, 7, 1, newIllum);
    strlcpy(illuminanceStr, newIllum, 8);
    board.TFT.updateCharArray(_myX + OLED_BUTTON_PADDING_LEFT, _myY + OLED_BUTTON_PADDING_TOP + 2 * 9, oldIllum, newIllum, TFT_WHITE, TFT_BROWN, 1, 1);
  }
  board.TFT.setCursor(_myX + OLED_BUTTON_PADDING_LEFT + 1, _myY + _myHeight - 15 + HEAD_POS_Y);
  if (errStatus != Pixel.errStatus || active != Pixel.active) {
    errStatus = Pixel.errStatus;
    active = Pixel.active;
    switch (Pixel.errStatus) {
      case 0:
        if (Pixel.active == 1) {
          board.TFT.fillRect(_myX + 1, _myY + _myHeight - 15, _myWidth - 2, 14, TFT_GREEN);
          board.TFT.setTextColor(TFT_WHITE, TFT_GREEN);
          board.TFT.print(F("OK"));
        } else if (Pixel.active == 0) {
          board.TFT.fillRect(_myX + 1, _myY + _myHeight - 15, _myWidth - 2, 14, TFT_BLACK);
          board.TFT.setTextColor(TFT_GREEN, TFT_BLACK);
          board.TFT.print(F("READY"));
        }
        break;
      case 1:
        board.TFT.fillRect(_myX + 1, _myY + _myHeight - 15, _myWidth - 2, 14, TFT_RED);
        board.TFT.setTextColor(TFT_WHITE, TFT_RED);
        board.TFT.print(F("SHORT"));
        break;
      case 2:
        board.TFT.fillRect(_myX + 1, _myY + _myHeight - 15, _myWidth - 2, 14, TFT_RED);
        board.TFT.setTextColor(TFT_WHITE, TFT_RED);
        board.TFT.print(F("OPEN"));
        break;
      case 3:
        board.TFT.fillRect(_myX + 1, _myY + _myHeight - 15, _myWidth - 2, 14, TFT_BLACK);
        board.TFT.setTextColor(TFT_ORANGE, TFT_BLACK);
        board.TFT.print(F("OVERTEMP"));
        break;
    }
  }
}

void WHZLogo::show()   // 108 x 108 px
{
  board.TFT.drawLine(_myX + 53, _myY + 0, _myX + 0, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 53, _myY + 1, _myX + 1, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 54, _myY + 0, _myX + 107, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 54, _myY + 1, _myX + 107, _myY + 54, TFT_WHITE);
  board.TFT.drawLine(_myX + 1, _myY + 54, _myX + 54, _myY + 107, TFT_WHITE);
  board.TFT.drawLine(_myX + 2, _myY + 54, _myX + 54, _myY + 106, TFT_WHITE);
  board.TFT.drawLine(_myX + 55, _myY + 106, _myX + 106, _myY + 55, TFT_WHITE);
  board.TFT.drawLine(_myX + 55, _myY + 105, _myX + 106, _myY + 54, TFT_WHITE);
  board.TFT.drawLine(_myX + 54, _myY + 105, _myX + 105, _myY + 54, TFT_WHITE);
  board.TFT.drawLine(_myX + 54, _myY + 104, _myX + 105, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 53, _myY + 104, _myX + 104, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 53, _myY + 103, _myX + 104, _myY + 52, TFT_WHITE);
  board.TFT.drawLine(_myX + 36, _myY + 19, _myX + 71, _myY + 19, TFT_WHITE);
  board.TFT.drawLine(_myX + 33, _myY + 84, _myX + 71, _myY + 84, TFT_WHITE);
  board.TFT.drawLine(_myX + 32, _myY + 83, _myX + 72, _myY + 83, TFT_WHITE);
  board.TFT.drawLine(_myX + 31, _myY + 82, _myX + 73, _myY + 82, TFT_WHITE);
  board.TFT.drawLine(_myX + 32, _myY + 81, _myX + 74, _myY + 81, TFT_WHITE);
  board.TFT.drawLine(_myX + 32, _myY + 80, _myX + 75, _myY + 80, TFT_WHITE);
  board.TFT.drawLine(_myX + 35, _myY + 79, _myX + 73, _myY + 21, TFT_WHITE);
  board.TFT.drawLine(_myX + 34, _myY + 79, _myX + 72, _myY + 21, TFT_WHITE);
  board.TFT.drawLine(_myX + 33, _myY + 79, _myX + 72, _myY + 20, TFT_WHITE);
}
