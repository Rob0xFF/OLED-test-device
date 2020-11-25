#include <microscope.h>

uint8_t Microscope::zoomIn(void)
{
  serialHandler.print('Z');
  unsigned long startMillis = millis();
  do {
    if (serialHandler.available()) {
      if (serialHandler.read() == 'M') {
        return 1;
      }
    }
  } while (millis() - startMillis < serialTimeout);
  return 0;
}

uint8_t Microscope::zoomOut(void)
{
  serialHandler.print('z');
  unsigned long startMillis = millis();
  do {
    if (serialHandler.available()) {
      if (serialHandler.read() == 'M') {
        return 1;
      }
    }
  } while (millis() - startMillis < serialTimeout);
  return 0;
}

uint8_t Microscope::togglePhotoVideo(void)
{
  serialHandler.print('T');
  unsigned long startMillis = millis();
  do {
    if (serialHandler.available()) {
      if (serialHandler.read() == 'M') {
        if (_isPhoto) {
          _isPhoto = 0;
        } else {
          _isPhoto = 1;
        }
        return 1;
      }
    }
  } while (millis() - startMillis < serialTimeout);
  return 0;
}

uint8_t Microscope::capture(void)
{
  serialHandler.print('C');
  unsigned long startMillis = millis();
  do {
    if (serialHandler.available()) {
      if (serialHandler.read() == 'M') {
        if (_isPhoto == 0) {
          _isCapturingVideo = 1;
        }
        return 1;
      }
    }
  } while (millis() - startMillis < serialTimeout);
  return 0;
}

uint8_t Microscope::stopVideoCapture(void)
{
  if (_isPhoto == 0 && _isCapturingVideo == 1) {
    serialHandler.print('S');
    unsigned long startMillis = millis();
    do {
      if (serialHandler.available()) {
        if (serialHandler.read() == 'M') {
          _isCapturingVideo = 0;
          return 1;
        }
      }
    } while (millis() - startMillis < serialTimeout);
  }
  return 0;
}

uint8_t Microscope::playback(void)
{
  serialHandler.print('P');
  unsigned long startMillis = millis();
  do {
    if (serialHandler.available()) {
      if (serialHandler.read() == 'M') {
        return 1;
      }
    }
  } while (millis() - startMillis < serialTimeout);
  return 0;
}