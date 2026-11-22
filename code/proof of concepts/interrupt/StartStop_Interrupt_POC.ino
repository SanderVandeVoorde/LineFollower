#include <Arduino.h>

// Hardware-interrupt demonstratie voor Arduino Nano.
// Knop tussen D2 (INT0) en GND.

const byte BUTTON_PIN = 2;
const byte LED_PIN = 13;
volatile bool buttonEvent = false;
bool running = false;
unsigned long lastAcceptedEvent = 0;

void buttonISR() {
  // Alleen een vlag zetten; geen Serial of delay in een ISR.
  buttonEvent = true;
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  digitalWrite(LED_PIN, LOW);
  Serial.println(F("Start/stop interrupt POC klaar"));
  Serial.println(F("Druk op de knop tussen D2 en GND"));
}

void loop() {
  bool eventReceived = false;
  noInterrupts();
  if (buttonEvent) {
    buttonEvent = false;
    eventReceived = true;
  }
  interrupts();

  if (eventReceived && millis() - lastAcceptedEvent >= 200) {
    lastAcceptedEvent = millis();
    running = !running;
    digitalWrite(LED_PIN, running ? HIGH : LOW);
    Serial.println(running ? F("STATE,START") : F("STATE,STOP"));
  }
}
