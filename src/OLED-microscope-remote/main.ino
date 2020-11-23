#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

const float V_ref = 4.88;
const float V_idle = 3.32;
const float V_Z = 1.37;
const float V_z = 1.85;
const float V_T = 0.9;
const float V_C = 0.54;
const float V_P = 0.23;

uint16_t shortDuration = 100;
uint16_t longDuration = 500;

void setButton(float voltage)
{
  dac.setVoltage((int)(voltage / V_ref * 4095), false);
}

void setIdle(void)
{
  dac.setVoltage((int)(V_idle / V_ref * 4095), false);
}


void setup()
{
  Serial.begin(115200);
  dac.begin(0x61);
  dac.setVoltage((int)(V_idle / V_ref * 4095), false);
}

void loop()
{
  if (Serial.available()) {
    char read = Serial.read();
    if (read == 'H') {
      Serial.print('M');
    }
    if (read == 'Z') {
      Serial.print('M');
      setButton(V_Z);
      _delay_ms(longDuration);
      setIdle();
    }
    if (read == 'Z') {
      Serial.print('M');
      setButton(V_z);
      _delay_ms(longDuration);
      setIdle();
    }
    if (read == 'T') {
      Serial.print('M');
      setButton(V_T);
      _delay_ms(shortDuration);
      setIdle();
    }
    if (read == 'C') {
      Serial.print('M');
      setButton(V_C);
      _delay_ms(shortDuration);
      setIdle();
    }
    if (read == 'P') {
      Serial.print('M');
      setButton(V_P);
      _delay_ms(shortDuration);
      setIdle();
    }
  }
}
