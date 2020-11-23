#include "c12880.h"

#define SPEC_TRG         A4
#define SPEC_ST          A2
#define SPEC_CLK         A1
#define SPEC_VIDEO       A5

#include <avr/pgmspace.h>

uint16_t next = 0;

uint16_t data[C12880_NUM_CHANNELS];

C12880 spec(SPEC_TRG, SPEC_ST, SPEC_CLK, SPEC_VIDEO);

const long wavelengths[] PROGMEM = {
  30859, 31130, 31400, 31671, 31940, 32210, 32480, 32749, 33017, 33286, 33554, 33822, 34090, 34357, 34624, 34890, 35157, 35423,
  35689, 35954, 36219, 36484, 36748, 37012, 37276, 37539, 37802, 38064, 38327, 38588, 38850, 39111, 39372, 39632, 39892, 40152,
  40411, 40670, 40928, 41186, 41444, 41701, 41958, 42214, 42470, 42726, 42981, 43235, 43490, 43743, 43997, 44250, 44502, 44754,
  45006, 45257, 45508, 45758, 46008, 46258, 46506, 46755, 47003, 47250, 47497, 47744, 47990, 48235, 48481, 48725, 48969, 49213,
  49456, 49699, 49941, 50182, 50423, 50664, 50904, 51144, 51383, 51621, 51859, 52097, 52334, 52570, 52806, 53041, 53276, 53510,
  53744, 53977, 54210, 54442, 54674, 54905, 55135, 55365, 55594, 55823, 56051, 56279, 56506, 56732, 56958, 57184, 57408, 57633,
  57856, 58079, 58302, 58524, 58745, 58966, 59186, 59405, 59624, 59843, 60060, 60278, 60494, 60710, 60925, 61140, 61354, 61568,
  61781, 61993, 62205, 62416, 62627, 62836, 63046, 63254, 63462, 63670, 63877, 64083, 64288, 64493, 64698, 64901, 65104, 65307,
  65509, 65710, 65910, 66110, 66310, 66508, 66706, 66904, 67100, 67296, 67492, 67687, 67881, 68075, 68268, 68460, 68652, 68843,
  69033, 69223, 69412, 69600, 69788, 69975, 70162, 70348, 70533, 70718, 70902, 71085, 71268, 71450, 71631, 71812, 71992, 72172,
  72351, 72529, 72707, 72884, 73060, 73236, 73411, 73585, 73759, 73932, 74104, 74276, 74447, 74618, 74788, 74957, 75126, 75294,
  75462, 75628, 75794, 75960, 76125, 76289, 76453, 76616, 76778, 76940, 77101, 77262, 77422, 77581, 77740, 77898, 78055, 78212,
  78368, 78524, 78679, 78833, 78987, 79140, 79293, 79445, 79596, 79747, 79897, 80047, 80196, 80345, 80492, 80640, 80786, 80932,
  81078, 81223, 81367, 81511, 81654, 81797, 81939, 82081, 82222, 82362, 82502, 82641, 82780, 82918, 83056, 83193, 83329, 83465,
  83601, 83736, 83870, 84004, 84137, 84270, 84403, 84534, 84666, 84796, 84927, 85057, 85186, 85315, 85443, 85571, 85698, 85825,
  85951, 86077, 86202, 86327, 86452, 86576, 86699, 86823, 86945, 87067, 87189, 87310, 87431, 87552, 87672, 87791, 87911, 88029
};

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  spec.begin();
}

void loop()
{
  if (Serial) {
    if (Serial.available()) {
      char readout = Serial.read();
      if (readout == 'H') {
        Serial.println('S');
      }
      if (readout == 'T') {
        unsigned long _startMillis = millis();
        do {
          if (Serial.available() >= 3) {
            float readoutf;
            readoutf = Serial.parseFloat();
            spec.setIntegrationTime(readoutf);
            Serial.println('S');
            return;
          }
        } while (millis() - _startMillis < 100);
      }
      if (readout == 'A') {
        unsigned long _startMillis = millis();
        do {
          if (Serial.available() >= 1) {
            byte readoutf;
            readoutf = Serial.read();
            spec.setAveraging((uint8_t) readoutf);
            Serial.println('S');
            return;
          }
        } while (millis() - _startMillis < 100);
      }
      if (readout == 'C') {
        spec.readInto(data);
        Serial.println('S');
      }
      if (readout == 'G') {
        Serial.println("lambda[nm] intensity[a.u.]");
        for (uint16_t i = 0; i < C12880_NUM_CHANNELS; i++) {
          long buf = pgm_read_dword(&(wavelengths[i]));
          Serial.print((float) buf / 100.0f);
          Serial.print(" ");
          Serial.println(data[i]);
        }
      }
    }
  }
  if (Serial1.available()) {
    char readout = Serial1.read();
    if (readout == 'H') {
      Serial1.print('S');
    }
    if (readout == 'T') {
      unsigned long _startMillis = millis();
      do {
        if (Serial1.available() >= 4) {
          byte readoutf[4];
          Serial1.readBytes(readoutf, 4);
          uint32_t newIntegTime;
          newIntegTime = ((readoutf[3] & 0xFFFFFF) << 24 | (readoutf[2] & 0xFFFFFF) << 16 | (readoutf[1] & 0xFFFFFF) << 8 | (readoutf[0] & 0xFFFFFF));
          spec.setIntegrationTime(*(float *) & newIntegTime);
          Serial1.print('S');
          return;
        }
      } while (millis() - _startMillis < 100);
    }
    if (readout == 'A') {
      unsigned long _startMillis = millis();
      do {
        if (Serial1.available() >= 1) {
          byte readoutf[1];
          Serial1.readBytes(readoutf, 1);
          spec.setAveraging((uint8_t) readoutf[0]);
          Serial1.print('S');
          return;
        }
      } while (millis() - _startMillis < 100);
    }
    if (readout == 'C') {
      spec.readInto(data);
      next = 0;
      Serial1.print('S');
    }
    if (readout == 'G') {
      Serial1.write((byte *) & data[next], 2);
      Serial.println(data[next]);
      next++;
      if (next >= C12880_NUM_CHANNELS) {
        next = 0;
      }
    }
  }
}
