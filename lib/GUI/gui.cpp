#include <gui.h>

void GUI::boot(void)
{
  board.begin();
  _screenheader.show();
  currentScreen = 0; // MainMenu
  mainMenu = new (memBufferMainMenu) MainMenu(board);
  //mainMenu = new(memBuffer) MainMenu(board);
  mainMenu -> show();
//   Serial.print("Size of MainMenu Object: ");
//   Serial.print(sizeof(MainMenu));
//   Serial.println(" bytes");
//   Serial.print("Size of QuickTest Object: ");
//   Serial.print(sizeof(QuickTest));
//   Serial.println(" bytes");
//   Serial.print("Size of Characteristic Object: ");
//   Serial.print(sizeof(Characteristic));
//   Serial.println(" bytes");
//   Serial.print("Size of Spectrum Object: ");
//   Serial.print(sizeof(Spectrum));
//   Serial.println(" bytes");
//   Serial.print("Size of AngleScan Object: ");
//   Serial.print(sizeof(AngleScan));
//   Serial.println(" bytes");
//   Serial.print("Size of ClockSet Object: ");
//   Serial.print(sizeof(ClockSet));
//   Serial.println(" bytes");
//   Serial.print("Size of Info Object: ");
//   Serial.print(sizeof(Info));
//   Serial.println(" bytes");
}

void GUI::update(void)
{
  board.update();
  _screenheader.update();
  switch (currentScreen) {
    case 0: //MainMenu
      break;
    case 1: //Quick Test
      if (quickTest != nullptr) {
        quickTest -> update();
      }
      break;
    case 2: // Characteristic
      if (characteristic != nullptr) {
        characteristic -> update();
      }
      break;
    case 3: //Spec
      if (spectrum != nullptr) {
        spectrum -> update();
      }
      break;
  }
}

void GUI::fastUpdate(void)
{
  if (board.brightnessSetPoint != board.TFT.brightness) {
    board.TFT.smoothSetBacklight(board.brightnessSetPoint);
  }
  board.stepper->fastUpdate();
}

void GUI::updateTouch()
{
  TS_Point p = board.myTouch.getPoint();
  TouchY = board.TFT.height() - p.y; //board.TFT.height() - p.x;
  TouchX = board.TFT.width() - p.x; //p.y;
  if (currentScreen == 0 && mainMenu != nullptr) { // Main Menu
    if (mainMenu -> menuEntry1.touched(TouchX, TouchY)) { // Quick Test
      mainMenu -> ~MainMenu();
      currentScreen = 1;
      quickTest = new (memBufferQuickTest) QuickTest(board);
      //quickTest = new(memBuffer) QuickTest(board);
      quickTest -> show();
    }
    if (mainMenu -> menuEntry2.touched(TouchX, TouchY)) { // I-U Curve
      mainMenu -> ~MainMenu();
      currentScreen = 2;
      characteristic = new (memBufferCharacteristic) Characteristic(board);
      //characteristic = new(memBuffer) Characteristic(board);
      characteristic -> show();
    }
    if (mainMenu -> menuEntry3.touched(TouchX, TouchY)) { // Spectrum
      mainMenu -> ~MainMenu();
      currentScreen = 3;
      spectrum = new (memBufferSpectrum) Spectrum(board);
      //characteristic = new(memBuffer) Characteristic(board);
      spectrum -> show();
    }
    if (mainMenu -> menuEntry4.touched(TouchX, TouchY)) { // AngleScan
      mainMenu -> ~MainMenu();
      currentScreen = 4;
      angleScan = new (memBufferAngleScan) AngleScan(board);
      //characteristic = new(memBuffer) Characteristic(board);
      angleScan -> show();
    }
    if (mainMenu -> menuEntry5.touched(TouchX, TouchY)) { // I-U Curve
      mainMenu -> ~MainMenu();
      currentScreen = 5;
      clockScreen = new (memBufferClockSet) ClockSet(board);
      //characteristic = new(memBuffer) Characteristic(board);
      clockScreen -> show();
    }
    if (mainMenu -> menuEntry6.touched(TouchX, TouchY)) { // Info
      mainMenu -> ~MainMenu();
      currentScreen = 6;
      info = new (memBufferInfo) Info(board);
      //characteristic = new(memBuffer) Characteristic(board);
      info -> show();
    }
    return;
  }
  if (currentScreen == 1 && quickTest != nullptr) { // QuickTest
    if (quickTest -> sPButton.touched(TouchX, TouchY) && quickTest -> measurementPending == 0) {
      quickTest -> sPButton.touchHandle(quickTest -> sPButton.touched(TouchX, TouchY));
      return;
    }
    if (quickTest -> timeButton.touched(TouchX, TouchY) && quickTest -> measurementPending == 0) {
      quickTest -> timeButton.touchHandle(quickTest -> timeButton.touched(TouchX, TouchY));
      return;
    }
    if (quickTest -> exitButton.touched(TouchX, TouchY) && quickTest -> measurementPending == 0) {
      quickTest -> ~QuickTest();
      currentScreen = 0;
      mainMenu = new (memBufferMainMenu) MainMenu(board);
      //mainMenu = new(memBuffer) MainMenu(board);
      mainMenu -> show();
      return;
    }
    if (quickTest -> lifeTimeButton.touched(TouchX, TouchY) && quickTest -> measurementPending == 0) {
      quickTest -> lifeTimeButton.touchHandle();
      return;
    }
    if (quickTest -> selector.touched(TouchX, TouchY) && quickTest -> measurementPending == 0) {
      quickTest -> selector.touchHandle();
      return;
    }
    if (quickTest -> startButton.touched(TouchX, TouchY) && quickTest -> measurementPending == 0) {
      if (quickTest -> selector.selected < 6) {
        board._Pixel[quickTest -> selector.selected].pixel.on(quickTest -> sPButton.setPoint);
        quickTest -> Button[quickTest -> selector.selected].update();
      } else if (quickTest -> selector.selected == 6) {
        board._Pixel[0].pixel.on(quickTest -> sPButton.setPoint);
        board._Pixel[1].pixel.on(quickTest -> sPButton.setPoint);
        board._Pixel[2].pixel.on(quickTest -> sPButton.setPoint);
        board._Pixel[3].pixel.on(quickTest -> sPButton.setPoint);
        board._Pixel[4].pixel.on(quickTest -> sPButton.setPoint);
        board._Pixel[5].pixel.on(quickTest -> sPButton.setPoint);
        quickTest -> Button[0].update();
        quickTest -> Button[1].update();
        quickTest -> Button[2].update();
        quickTest -> Button[3].update();
        quickTest -> Button[4].update();
        quickTest -> Button[5].update();
      }
      quickTest -> measurementPending = (uint8_t) quickTest -> timeButton.setPoint - 2;
      quickTest -> startButton.hide();
      quickTest -> stopButton.show();
      return;
    }
    if (quickTest -> stopButton.touched(TouchX, TouchY) && quickTest -> measurementPending > 0) {
      if (quickTest -> selector.selected < 6) {
        board._Pixel[quickTest -> selector.selected].pixel.off();
        quickTest -> Button[quickTest -> selector.selected].update();
      } else if (quickTest -> selector.selected == 6) {
        board._Pixel[0].pixel.off();
        board._Pixel[1].pixel.off();
        board._Pixel[2].pixel.off();
        board._Pixel[3].pixel.off();
        board._Pixel[4].pixel.off();
        board._Pixel[5].pixel.off();
        quickTest -> Button[0].update();
        quickTest -> Button[1].update();
        quickTest -> Button[2].update();
        quickTest -> Button[3].update();
        quickTest -> Button[4].update();
        quickTest -> Button[5].update();
      }
      quickTest -> measurementPending = 0;
      quickTest -> stopButton.hide();
      quickTest -> startButton.show();
      return;
    }
  }
  if (currentScreen == 2 && characteristic != nullptr) { // I-V characteristic
    if (characteristic -> startButton.touched(TouchX, TouchY) && characteristic -> measuring == 0) {
      characteristic -> startButton.hide();
      characteristic -> stopButton.show();
      characteristic -> measuring = 1;
      return;
    }
    if (characteristic -> stopButton.touched(TouchX, TouchY) && characteristic -> measuring == 1) {
      characteristic -> stopMeasurement();
      return;
    }
    if (characteristic -> selector.touched(TouchX, TouchY) && characteristic -> measuring == 0) {
      characteristic -> selector.touchHandle();
      return;
    }
    if (characteristic -> exitButton.touched(TouchX, TouchY) && characteristic -> measuring == 0) {
      characteristic -> ~Characteristic();
      currentScreen = 0;
      //mainMenu = new(memBuffer) MainMenu(board);
      mainMenu = new (memBufferMainMenu) MainMenu(board);
      mainMenu -> show();
      return;
    }
    if (characteristic -> numButton.touched(TouchX, TouchY) && characteristic -> measuring == 0) {
      characteristic -> numButton.touchHandle(characteristic -> numButton.touched(TouchX, TouchY));
      return;
    }
    if (characteristic -> minButton.touched(TouchX, TouchY) && characteristic -> measuring == 0) {
      characteristic -> minButton.touchHandle(characteristic -> minButton.touched(TouchX, TouchY));
      return;
    }
    if (characteristic -> maxButton.touched(TouchX, TouchY) && characteristic -> measuring == 0) {
      characteristic -> maxButton.touchHandle(characteristic -> maxButton.touched(TouchX, TouchY));
      return;
    }
  }
  if (currentScreen == 3 && spectrum != nullptr) { // Spectrum
    if (spectrum -> captureButton.touched(TouchX, TouchY) && board.spectrometer != nullptr && spectrum -> measuring == 0) {
      spectrum -> captureButton.hide();
      spectrum -> stopButton.show();
      spectrum -> measuring = 1;
      update();
      return;
    }
    if (spectrum -> stopButton.touched(TouchX, TouchY) && spectrum -> measuring == 1) {
      spectrum -> stopMeasurement();
      return;
    }
    if (spectrum -> selector.touched(TouchX, TouchY) && spectrum -> measuring == 0) {
      spectrum -> selector.touchHandle();
      return;
    }
    if (spectrum -> averagingButton.touched(TouchX, TouchY)) {
      spectrum -> averagingButton.touchHandle(spectrum -> averagingButton.touched(TouchX, TouchY));
      return;
    }
    if (spectrum -> sPButton.touched(TouchX, TouchY) && spectrum -> measuring == 0) {
      spectrum -> sPButton.touchHandle(spectrum -> sPButton.touched(TouchX, TouchY));
      return;
    }
    if (spectrum -> iTButton.touched(TouchX, TouchY) && spectrum -> measuring == 0) {
      spectrum -> iTButton.touchHandle(spectrum -> iTButton.touched(TouchX, TouchY));
      return;
    }
    if (spectrum -> exitButton.touched(TouchX, TouchY) && spectrum -> measuring == 0) {
      //mainMenu = new(memBuffer) MainMenu(board);
      spectrum -> ~Spectrum();
      currentScreen = 0;
      mainMenu = new (memBufferMainMenu) MainMenu(board);
      mainMenu -> show();
      return;
    }
  }
  if (currentScreen == 4 && angleScan != nullptr) { // AngleScan
    if (angleScan -> exitButton.touched(TouchX, TouchY)) {
      //mainMenu = new(memBuffer) MainMenu(board);
      angleScan -> ~AngleScan();
      currentScreen = 0;
      mainMenu = new (memBufferMainMenu) MainMenu(board);
      mainMenu -> show();
      return;
    }
    if (angleScan -> startButton.touched(TouchX, TouchY)) {
      board.stepper->moveTo(board.stepper->getPosition() + 180.0);
    }
  }
  if (currentScreen == 5 && clockScreen != nullptr) { // Clockscreen
    if (clockScreen -> exitButton.touched(TouchX, TouchY)) {
      //mainMenu = new(memBuffer) MainMenu(board);
      clockScreen -> ~ClockSet();
      currentScreen = 0;
      mainMenu = new (memBufferMainMenu) MainMenu(board);
      mainMenu -> show();
      return;
    }
    if (clockScreen -> hourButton.touched(TouchX, TouchY)) {
      clockScreen -> hourButton.touchHandle(clockScreen -> hourButton.touched(TouchX, TouchY));
      return;
    }
    if (clockScreen -> minuteButton.touched(TouchX, TouchY)) {
      clockScreen -> minuteButton.touchHandle(clockScreen -> minuteButton.touched(TouchX, TouchY));
      return;
    }
    if (clockScreen -> secondButton.touched(TouchX, TouchY)) {
      clockScreen -> secondButton.touchHandle(clockScreen -> secondButton.touched(TouchX, TouchY));
      return;
    }
    if (clockScreen -> yearButton.touched(TouchX, TouchY)) {
      clockScreen -> yearButton.touchHandle(clockScreen -> yearButton.touched(TouchX, TouchY));
      return;
    }
    if (clockScreen -> monthButton.touched(TouchX, TouchY)) {
      clockScreen -> monthButton.touchHandle(clockScreen -> monthButton.touched(TouchX, TouchY));
      return;
    }
    if (clockScreen -> dayButton.touched(TouchX, TouchY)) {
      clockScreen -> dayButton.touchHandle(clockScreen -> dayButton.touched(TouchX, TouchY));
      return;
    }
    if (clockScreen -> setButton.touched(TouchX, TouchY)) {
      board.writeTimeToLog();
      board._myClock.setHour((int) clockScreen -> hourButton.setPoint);
      board._myClock.setMinute((int) clockScreen -> minuteButton.setPoint);
      board._myClock.setSecond((int) clockScreen -> secondButton.setPoint);
      board._myClock.setYear((int) clockScreen -> yearButton.setPoint);
      board._myClock.setMonth((int) clockScreen -> monthButton.setPoint);
      board._myClock.setDate((int) clockScreen -> dayButton.setPoint);
      board.writeTimeToLog();
      board.writeToLog(F("new Date / Time set.\n"));
      return;
    }
  }
  if (currentScreen == 6 && info != nullptr) { // Info
		if (info -> shortButton.touched(TouchX, TouchY)) {
			info -> shortButton.touchHandle(info -> shortButton.touched(TouchX, TouchY));
      return;		
		}
		if (info -> openButton.touched(TouchX, TouchY)) {
			info -> openButton.touchHandle(info -> openButton.touched(TouchX, TouchY));
      return;		
		}
    if (info -> exitButton.touched(TouchX, TouchY)) {
			board._Pixel[0].pixel.configShortDetection((uint8_t) (0.5 + 256.0 * info -> shortButton.setPoint / 33.0));
			board._Pixel[3].pixel.configShortDetection((uint8_t) (0.5 + 256.0 * info -> shortButton.setPoint / 33.0));
			board._Pixel[0].pixel.configOpenDetection((uint8_t) (0.5 + 256.0 * info -> openButton.setPoint / 33.0));
			board._Pixel[3].pixel.configOpenDetection((uint8_t) (0.5 + 256.0 * info -> openButton.setPoint / 33.0));
      //mainMenu = new(memBuffer) MainMenu(board);
      info -> ~Info();
      currentScreen = 0;
      mainMenu = new (memBufferMainMenu) MainMenu(board);
      mainMenu -> show();
      return;
    }
  }
}