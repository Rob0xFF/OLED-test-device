#include <spectrometer.h>

Spectrometer::~Spectrometer()
{
  // nothing to be done here, just destroy the object
}

uint8_t Spectrometer::setIntegTime(float integTime)
{
  serialHandler.print('T');
  serialHandler.write((byte *) & integTime, 4);
  unsigned long startMillis = millis();
  do {
    if (serialHandler.available()) {
      if (serialHandler.read() == 'S') {
        return 1;
      }
    }
  } while (millis() - startMillis < serialTimeout);
  return 0;
}

uint8_t Spectrometer::setAveraging(uint8_t av)
{
  serialHandler.print('A');
  serialHandler.write((byte *) & av, 1);
  unsigned long startMillis = millis();
  do {
    if (serialHandler.available()) {
      if (serialHandler.read() == 'S') {
        return 1;
      }
    }
  } while (millis() - startMillis < serialTimeout);
  return 0;
}

uint8_t Spectrometer::capture(void)
{
  serialHandler.print('C');
  unsigned long startMillis = millis();
  do {
    if (serialHandler.available()) {
      if (serialHandler.read() == 'S') {
        return 1;
      }
    }
  } while (millis() - startMillis < 60000);
  return 0;
}

uint8_t Spectrometer::read(void)
{
  for (uint16_t i = 0; i < 288; i++) {
    serialHandler.print('G');
    unsigned long startMillis = millis();
    do {
      if (serialHandler.available() >= 2) {
        byte readout[2];
        serialHandler.readBytes(readout, 2);
        intensities[i] = ((readout[1] & 0xFFFF)  << 8) | (readout[0] & 0xFFFF);
        break;
      }
    } while (millis() - startMillis < serialTimeout);
  }
  return 0;
}