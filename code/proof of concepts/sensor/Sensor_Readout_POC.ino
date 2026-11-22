#include <Arduino.h>

// Eenvoudige uitlezing van de acht analoge HY-S301-uitgangen.
// Geen calibratie, normalisatie of lijninterpolatie.

const byte sensorPins[8] = { A7, A6, A5, A4, A3, A2, A1, A0 };
unsigned long lastPrint = 0;
const unsigned long PRINT_INTERVAL_MS = 100;

void setup() {
  Serial.begin(115200);
  Serial.println(F("HY-S301 sensor readout"));
  Serial.println(F("Volgorde: D1 links, D2, D3, D4, D5, D6, D7, D8 rechts"));
}

void loop() {
  if (millis() - lastPrint < PRINT_INTERVAL_MS) return;
  lastPrint = millis();
  for (byte i = 0; i < 8; i++) {
    int value = analogRead(sensorPins[i]);
    Serial.print(F("D"));
    Serial.print(i + 1);
    Serial.print('=');
    Serial.print(value);
    if (i < 7) Serial.print(F(", "));
  }
  Serial.println();
}
