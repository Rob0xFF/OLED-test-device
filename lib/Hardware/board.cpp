#include <board.h>


Board::Board()
{
  temperature = 0.0;
  humidity = 0.0;
}

void Board::begin(void)
{
  Wire.begin();
  TFT.begin();
  TFT.setRotation(2);
  TFT.fillScreen(0x0000);
  TFT.setCursor(0, 0);
  TFT.setTextColor(0xFFFF);
  TFT.setTextSize(1);
  TFT.println();
  TFT.println(F("OLED test device starting"));
  TFT.println();
  TFT.println();
  TFT.print(F("> TCAmain Multiplexer"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_TCAMAIN);
  if (!Wire.endTransmission()) {
    available(TCAMAIN);
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > Check on-board connections!"));
    return;
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> TCAHead Multiplexer"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_TCAHEAD);
  if (!Wire.endTransmission()) {
    available(TCAHEAD);
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > Check on-board connections."));
    TFT.println(F("> > Is sensor head mounted correctly?"));
    return;
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> INA226 volt / current meters"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  uint8_t found = 0;
  for (auto & i : _myIna) {
    TCAmain.enableChannel(i.tcaPin);
    Wire.beginTransmission(I2C_INA226);
    if (!Wire.endTransmission()) {
      available(i.availBit);
      found++;
    }
    TCAmain.disableChannel(i.tcaPin);
  }
  if (found == 6) {
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > found "));
    TFT.println(found);
    TFT.println(F(" of 6"));
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> BH1750 light meters"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  found = 0;
  for (auto & i : _myBH) {
    TCAhead.enableChannel(i.tcaPin);
    Wire.beginTransmission(I2C_BH1750);
    if (!Wire.endTransmission()) {
      available(i.availBit);
      found++;
    }
    TCAhead.disableChannel(i.tcaPin);
  }
  if (found == 6) {
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > found "));
    TFT.println(found);
    TFT.println(F(" of 6"));
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> E52246 OLED drivers"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  found = 0;
  TCAmain.enableChannel(E52246_1_TCA_PIN);
  Wire.beginTransmission(I2C_E52246_1);
  if (!Wire.endTransmission()) {
    available(E52246_1);
    found++;
  }
  TCAmain.disableChannel(E52246_1_TCA_PIN);
  TCAmain.enableChannel(E52246_2_TCA_PIN);
  Wire.beginTransmission(I2C_E52246_2);
  if (!Wire.endTransmission()) {
    available(E52246_2);
    found++;
  }
  TCAmain.disableChannel(E52246_2_TCA_PIN);
  if (found == 2) {
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.print(F("> > found "));
    TFT.print(found);
    TFT.println(F(" of 2"));
  }
  TFT.setTextColor(0xFFFF);
  if (isAvailable(E52246_1)) {
    if ((_isAvailable & 1 << INA1) && (_isAvailable & 1 << BH1)) {
      TFT.print(F("> Pixel 1"));
      TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
      if (_Pixel[0].pixel.begin()) {
        available(PIXEL_1);
        TFT.setTextColor(0x0FF0);
        TFT.println(F("DONE"));
      } else {
        TFT.setTextColor(0xF000);
        TFT.println(F("FAIL"));
      }
      TFT.setTextColor(0xFFFF);
    }
    if ((_isAvailable & 1 << INA2) && (_isAvailable & 1 << BH2)) {
      TFT.print(F("> Pixel 2"));
      TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
      if (_Pixel[1].pixel.begin()) {
        available(PIXEL_2);
        TFT.setTextColor(0x0FF0);
        TFT.println(F("DONE"));
      } else {
        TFT.setTextColor(0xF000);
        TFT.println(F("FAIL"));
      }
      TFT.setTextColor(0xFFFF);
    }
    if ((_isAvailable & 1 << INA3) && (_isAvailable & 1 << BH3)) {
      TFT.print(F("> Pixel 3"));
      TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
      if (_Pixel[2].pixel.begin()) {
        available(PIXEL_3);
        TFT.setTextColor(0x0FF0);
        TFT.println(F("DONE"));
      } else {
        TFT.setTextColor(0xF000);
        TFT.println(F("FAIL"));
      }
      TFT.setTextColor(0xFFFF);
    }
  }
  if (_isAvailable & 1 << E52246_2) {
    if ((_isAvailable & 1 << INA4) && (_isAvailable & 1 << BH4)) {
      TFT.print(F("> Pixel 4"));
      TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
      if (_Pixel[3].pixel.begin()) {
        available(PIXEL_4);
        TFT.setTextColor(0x0FF0);
        TFT.println(F("DONE"));
      } else {
        TFT.setTextColor(0xF000);
        TFT.println(F("FAIL"));
      }
      TFT.setTextColor(0xFFFF);
    }
    if ((_isAvailable & 1 << INA5) && (_isAvailable & 1 << BH5)) {
      TFT.print(F("> Pixel 5"));
      TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
      if (_Pixel[4].pixel.begin()) {
        available(PIXEL_5);
        TFT.setTextColor(0x0FF0);
        TFT.println(F("DONE"));
      } else {
        TFT.setTextColor(0xF000);
        TFT.println(F("FAIL"));
      }
      TFT.setTextColor(0xFFFF);
    }
    if ((_isAvailable & 1 << INA6) && (_isAvailable & 1 << BH6)) {
      TFT.print(F("> Pixel 6"));
      TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
      if (_Pixel[5].pixel.begin()) {
        available(PIXEL_6);
        TFT.setTextColor(0x0FF0);
        TFT.println(F("DONE"));
      } else {
        TFT.setTextColor(0xF000);
        TFT.println(F("FAIL"));
      }
      TFT.setTextColor(0xFFFF);
    }
  }
  TFT.print(F("> HIH6130 environment monitor:"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  TCAhead.enableChannel(4); // can be left open
  Wire.beginTransmission(I2C_HIH6130);
  if (!Wire.endTransmission()) {
    available(HIH6130_TEMP_HUM);
    _myHIH.begin();
    updateTemperHum();
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> DS3231 clock"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_DS3231);
  if (!Wire.endTransmission()) {
    available(DS3231_CLOCK);
    // 1Hz clock for interrupt driven main thread
    _myClock.enableOscillator(true, false, 0);
    updateTime();
    pinMode(MCP73832_STAT, INPUT);
    if (digitalRead(MCP73832_STAT) == LOW) {
      available(CHARGING_BIT);
    }
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    return;
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> FT6206 touch sensor"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_FT6206);
  if (!Wire.endTransmission()) {
    available(FT6206);
    myTouch.begin();
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    return;
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> SD slot"));
  pinMode(SD_CARD_CHECK, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  if (digitalRead(SD_CARD_CHECK) == LOW) {
    if (card.init(SPI_HALF_SPEED, SD_CS)) {
      if (volume.init(card)) {
        SD.begin(SD_CS);
        available(SD_CARD);
        TFT.setTextColor(0x0FF0);
        TFT.setCursor(TFT.width() - 8 * 6, TFT.getCursorY());
        TFT.println(F("SD FOUND"));
        digitalWrite(LED_GREEN, HIGH);
      } else {
        TFT.setTextColor(0xF000);
        TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
        TFT.println(F("FAIL"));
        TFT.println(F("> > SD Card found, volume failed, FAT32?"));
      }
    } else {
      TFT.setTextColor(0xF000);
      TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
      TFT.println(F("FAIL"));
      TFT.println(F("> > SD Card found, init failed"));
    }
  } else {
    TFT.setTextColor(0xFC60);
    TFT.setCursor(TFT.width() - 5 * 6, TFT.getCursorY());
    TFT.println(F("NO SD"));
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> Motor Driver"));
  stepper = new (memBufferStepper) Stepper(MOTOR_ENABLE, MOTOR_STEP, MOTOR_DIR, MOTOR_LIMIT_PIN);
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  available(MOTOR);
  TFT.setTextColor(0x0FF0);
  TFT.println(F("DONE"));
  //EEPROM.write(0,0);	// reset value only at first start after EEPROM was erased
  uint8_t fileCount = EEPROM.read(0);
  sprintf_P(dataFile, (PGM_P) F("OLED-%03d.txt"), fileCount);
  if (isAvailable(SD_CARD)) {
    EEPROM.write(0, (fileCount + 1) % 256);
  }
  TFT.setTextColor(0xFFFF);
  Serial1.begin(115200);
  Serial2.begin(115200);
  TFT.println();
  TFT.setTextColor(0xFFFF, 0x0000);
  TFT.println();
  TFT.println(F("Here is, what the cow says:"));
  TFT.println();
  _delay_ms(1000);
  // That's what the cow says.
  TFT.println(F("   ----------------------------------"));
  TFT.println(F(" < Great dude. Starting in 8 seconds. >"));
  TFT.println(F("   ----------------------------------"));
  TFT.println(F("          \\   ^__^ "));
  TFT.println(F("           \\  (oo)\\_______"));
  TFT.println(F("              (__)\\       )\\/\\"));
  TFT.println(F("                  ||----w |"));
  TFT.print(F("                  ||     ||"));
  TFT.setCursor(TFT.getCursorX(), TFT.getCursorY() - 8 * 6);
  _delay_ms(1000);
  TFT.print("7");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("6");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("5");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("4");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("3");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("2");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("1");
  // TODO: check external RS232
  _delay_ms(1000);
  TFT.fillScreen(0x0000);
  writeTimeToLog();
  writeToLog(F("Session was started.\n"));
}

void dateTime(uint16_t * date, uint16_t * time)
{
  DS3231 _myClock;
  RTClib _myRTC;
  DateTime now = _myRTC.now();
  * date = FAT_DATE(now.year(), now.month(), now.day());
  * time = FAT_TIME(now.hour(), now.minute(), now.second());
}

void Board::logSpectrum(void)
{
  if (isAvailable(SD_CARD)) {
    digitalWrite(LED_RED, HIGH);
    SdFile::dateTimeCallback(dateTime);
    myFile = SD.open(dataFile, FILE_WRITE);
    for (uint16_t i = 0; i < 288; i++) {
      long buf = pgm_read_dword(&(wavelengths[i]));
      myFile.print((float) (buf / 100.0));
      myFile.print(F(" "));
      myFile.print(spectrometer -> intensities[i]);
      myFile.print(F("\n"));
    }
    myFile.close();
    digitalWrite(LED_RED, LOW);
  }
  if (Serial) {
    for (uint16_t i = 0; i < 288; i++) {
      long buf = pgm_read_dword(&(wavelengths[i]));
      Serial.print((float) (buf / 100.0));
      Serial.print(F(" "));
      Serial.print(spectrometer -> intensities[i]);
      Serial.print(F("\n"));
    }
  }
}

void Board::writeToLog(char textBuffer[])
{
  if (isAvailable(SD_CARD)) {
    digitalWrite(LED_RED, HIGH);
    SdFile::dateTimeCallback(dateTime);
    myFile = SD.open(dataFile, FILE_WRITE);
    myFile.print(textBuffer);
    myFile.close();
    digitalWrite(LED_RED, LOW);
  }
  if (Serial) {
    Serial.print(textBuffer);
  }
}

void Board::writeToLog(const __FlashStringHelper * ifsh)
{
  if (isAvailable(SD_CARD)) {
    digitalWrite(LED_RED, HIGH);
    SdFile::dateTimeCallback(dateTime);
    myFile = SD.open(dataFile, FILE_WRITE);
    PGM_P p = reinterpret_cast < PGM_P > (ifsh);
    size_t n = 0;
    while (1) {
      unsigned char c = pgm_read_byte(p++);
      if (c == 0) {
        break;
      }
      if (myFile.write(c)) {
        n++;
      } else {
        break;
      }
    }
    myFile.close();
    digitalWrite(LED_RED, LOW);
  }
  if (Serial) {
    Serial.print(ifsh);
  }
}

void Board::writeToLog(uint8_t number)
{
  if (isAvailable(SD_CARD)) {
    digitalWrite(LED_RED, HIGH);
    SdFile::dateTimeCallback(dateTime);
    myFile = SD.open(dataFile, FILE_WRITE);
    myFile.print(number);
    myFile.close();
    digitalWrite(LED_RED, LOW);
  }
  if (Serial) {
    Serial.print(number);
  }
}

void Board::writeToLog(uint16_t number)
{
  if (isAvailable(SD_CARD)) {
    digitalWrite(LED_RED, HIGH);
    SdFile::dateTimeCallback(dateTime);
    myFile = SD.open(dataFile, FILE_WRITE);
    myFile.print(number);
    myFile.close();
    digitalWrite(LED_RED, LOW);
  }
  if (Serial) {
    Serial.print(number);
  }
}

void Board::writeToLog(float number)
{
  if (isAvailable(SD_CARD)) {
    digitalWrite(LED_RED, HIGH);
    SdFile::dateTimeCallback(dateTime);
    myFile = SD.open(dataFile, FILE_WRITE);
    myFile.print(number);
    myFile.close();
    digitalWrite(LED_RED, LOW);
  }
  if (Serial) {
    Serial.print(number);
  }
}

void Board::writeTimeToLog()
{
  updateTime();
  char textBuffer[25];
  sprintf_P(textBuffer, (PGM_P) F("%02d-%02d-%02d %02d:%02d:%02d >> "), now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  if (isAvailable(SD_CARD)) {
    digitalWrite(LED_RED, HIGH);
    SdFile::dateTimeCallback(dateTime);
    myFile = SD.open(dataFile, FILE_WRITE);
    myFile.print(textBuffer);
    myFile.close();
    digitalWrite(LED_RED, LOW);
  }
  if (Serial) {
    Serial.print(textBuffer);
  }
}

// Based on https://forum.arduino.cc/index.php?topic=406416.0
void Board::saveScreenshot(void)
{
  if (isAvailable(SD_CARD)) {
    digitalWrite(LED_RED, HIGH);
    byte VH, VL;
    int i, j = 0;
    const int w = 240;
    const int h = 320;
    sprintf_P(screenshotFile, (PGM_P) F("SCRS-%03d.bmp"), screenshotCount);
    File outFile = SD.open(screenshotFile, FILE_WRITE);
    if (! outFile) {
      return;
    };
    unsigned char bmFlHdr[14] = {
      'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0
    };
    unsigned char bmInHdr[40] = {
      40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 0
    };
    unsigned long fileSize = 2ul * 240 * 320 + 54;
    bmFlHdr[ 2] = (unsigned char)(fileSize      );
    bmFlHdr[ 3] = (unsigned char)(fileSize >>  8);
    bmFlHdr[ 4] = (unsigned char)(fileSize >> 16);
    bmFlHdr[ 5] = (unsigned char)(fileSize >> 24);
    bmInHdr[ 4] = (unsigned char)(       w      );
    bmInHdr[ 5] = (unsigned char)(       w >>  8);
    bmInHdr[ 6] = (unsigned char)(       w >> 16);
    bmInHdr[ 7] = (unsigned char)(       w >> 24);
    bmInHdr[ 8] = (unsigned char)(       h      );
    bmInHdr[ 9] = (unsigned char)(       h >>  8);
    bmInHdr[10] = (unsigned char)(       h >> 16);
    bmInHdr[11] = (unsigned char)(       h >> 24);
    outFile.write(bmFlHdr, sizeof(bmFlHdr));
    outFile.write(bmInHdr, sizeof(bmInHdr));
    for (i = h; i > 0; i--) {
      for (j = 0; j < w; j++) {
        uint16_t rgb = TFT.readPixel(j, i);
        VH = (rgb & 0xFF00) >> 8;
        VL = rgb & 0x00FF;
        VL = (VH << 7) | ((VL & 0xC0) >> 1) | (VL & 0x1f);
        VH = VH >> 1;
        outFile.write(VL);
        outFile.write(VH);
      }
    }
    outFile.close();
    screenshotCount++;
    digitalWrite(LED_RED, LOW);
  }
}

void Board::checkSDSlot()
{
  if (!isAvailable(SD_CARD) && digitalRead(SD_CARD_CHECK) == LOW) {
    if (card.init(SPI_HALF_SPEED, SD_CS) && volume.init(card)) {
      uint8_t fileCount = EEPROM.read(0);
      EEPROM.write(0, (fileCount + 1) % 256);
      available(SD_CARD);
      hotplugStatus = 9;
      digitalWrite(LED_GREEN, HIGH);
      SD.begin(SD_CS);
    }
  }
  if (isAvailable(SD_CARD) && digitalRead(SD_CARD_CHECK) == HIGH) {
    unAvailable(SD_CARD);
    hotplugStatus = 10;
    digitalWrite(LED_GREEN, LOW);
  }
}

void Board::updateTemperHum()
{
  _myHIH.readRHT();
  temperature = round(_myHIH.temperature * 10.0) / 10.0;
  humidity = round(_myHIH.humidity * 10.0) / 10.0;
}

void Board::updateTime()
{
  now = _myRTC.now();
}

void Board::checkEXT()
{
  char readout = 'X';
  Serial1.print('H');
  _delay_ms(10);
  if (Serial1.available()) {
    readout = Serial1.read();
  }
  if (readout == 'X') {
    if (isAvailable(MICROSCOPE1) && microscope != nullptr) {
      microscope->~Microscope();
      unAvailable(MICROSCOPE1);
      hotplugStatus = 1;
    }
    if (isAvailable(SPEC1) && spectrometer != nullptr) {
      unAvailable(SPEC1);
      spectrometer->~Spectrometer();
      hotplugStatus = 2;
    }
  }
  if (readout == 'M') {
    if (!isAvailable(MICROSCOPE1)) {
      microscope = new (memBufferMicroscope) Microscope(Serial1);
      available(MICROSCOPE1);
      hotplugStatus = 3;
    }
  }
  if (readout == 'S') {
    if (!isAvailable(SPEC1)) {
      spectrometer = new (memBufferSpectrometer) Spectrometer(Serial1);
      available(SPEC1);
      hotplugStatus = 4;
    }
  }
  readout = 'X';
  Serial2.print('H');
  _delay_ms(10);
  if (Serial2.available()) {
    readout = Serial2.read();
  }
  if (readout == 'X') {
    if (isAvailable(MICROSCOPE2) && microscope != nullptr) {
      microscope->~Microscope();
      unAvailable(MICROSCOPE2);
      hotplugStatus = 5;
    }
    if (isAvailable(SPEC2) && spectrometer != nullptr) {
      unAvailable(SPEC2);
      spectrometer->~Spectrometer();
      hotplugStatus = 6;
    }
  }
  if (readout == 'M') {
    if (!isAvailable(MICROSCOPE2)) {
      microscope = new (memBufferMicroscope) Microscope(Serial2);
      available(MICROSCOPE2);
      hotplugStatus = 7;
    }
  }
  if (readout == 'S') {
    if (!isAvailable(SPEC2)) {
      available(SPEC2);
      spectrometer = new (memBufferSpectrometer) Spectrometer(Serial2);
      hotplugStatus = 8;
    }
  }
}

void Board::update()
{
  if (isAvailable(DS3231_CLOCK)) {
    updateTime();
  }
  if (_isAvailable & 1UL << HIH6130_TEMP_HUM) {
    updateTemperHum();
  }
  for (auto & i : _Pixel) {
    if (_isAvailable & 1UL << i.availBit) {
      if (i.pixel.active) {
        i.pixel.updateVoltage();
        i.pixel.updateCurrent();
        i.pixel.updateErrStatus();
      }
      i.pixel.updateIlluminance();
    }
  }
  checkSDSlot();
  checkEXT();
}