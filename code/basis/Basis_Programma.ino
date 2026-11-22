#include <Arduino.h>
#include <EEPROM.h>
#include <stdlib.h>
#include <string.h>

// Basisprogramma voor Arduino Nano (ATmega328P).
// Afzonderlijk oefenprogramma; vervangt de finale robotfirmware niet.

const byte LED_PIN = 13;
const byte START_STOP_PIN = 2;  // INT0 op Arduino Nano
const uint16_t SETTINGS_MAGIC = 0x4C46;
const int EEPROM_ADDRESS = 0;

struct Settings {
  uint16_t magic;
  uint16_t cycleTimeMs;
  uint8_t debugEnabled;
};

Settings settings;
volatile bool buttonEvent = false;
bool running = false;
bool ledState = false;
unsigned long lastCycle = 0;
unsigned long lastAcceptedButton = 0;
char serialBuffer[48];
byte serialIndex = 0;

void startStopISR() {
  // ISR bewust kort houden: geen Serial, delay of EEPROM in deze functie.
  buttonEvent = true;
}

void saveSettings() {
  settings.magic = SETTINGS_MAGIC;
  EEPROM.put(EEPROM_ADDRESS, settings);
  Serial.println(F("ACK,SAVED"));
}

void loadSettings() {
  EEPROM.get(EEPROM_ADDRESS, settings);
  if (settings.magic != SETTINGS_MAGIC ||
      settings.cycleTimeMs < 50 ||
      settings.cycleTimeMs > 5000 ||
      settings.debugEnabled > 1) {
    settings.magic = SETTINGS_MAGIC;
    settings.cycleTimeMs = 500;
    settings.debugEnabled = 1;
    saveSettings();
  }
}

void setRunning(bool state) {
  running = state;
  if (!running) {
    ledState = false;
    digitalWrite(LED_PIN, LOW);
  }
  if (settings.debugEnabled) {
    Serial.println(running ? F("STATE,RUNNING") : F("STATE,STOPPED"));
  }
}

void processCommand(char *command) {
  if (strcmp(command, "START") == 0) {
    setRunning(true);
  } else if (strcmp(command, "STOP") == 0) {
    setRunning(false);
  } else if (strncmp(command, "CYCLE,", 6) == 0) {
    long value = atol(command + 6);
    if (value >= 50 && value <= 5000) {
      settings.cycleTimeMs = (uint16_t)value;
      Serial.println(F("ACK,CYCLE"));
    } else {
      Serial.println(F("ERR,CYCLE_RANGE_50_5000"));
    }
  } else if (strncmp(command, "DEBUG,", 6) == 0) {
    int value = atoi(command + 6);
    if (value == 0 || value == 1) {
      settings.debugEnabled = (uint8_t)value;
      Serial.println(F("ACK,DEBUG"));
    } else {
      Serial.println(F("ERR,DEBUG_EXPECTS_0_OR_1"));
    }
  } else if (strcmp(command, "SAVE") == 0) {
    saveSettings();
  } else if (strcmp(command, "STATUS") == 0) {
    Serial.print(F("STATUS,"));
    Serial.print(running ? 1 : 0);
    Serial.print(',');
    Serial.print(settings.cycleTimeMs);
    Serial.print(',');
    Serial.println(settings.debugEnabled);
  } else {
    Serial.println(F("ERR,UNKNOWN_COMMAND"));
  }
}

void handleSerial() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n') {
      serialBuffer[serialIndex] = '\0';
      if (serialIndex > 0) processCommand(serialBuffer);
      serialIndex = 0;
    } else if (c != '\r') {
      if (serialIndex < sizeof(serialBuffer) - 1) {
        serialBuffer[serialIndex++] = c;
      } else {
        serialIndex = 0;
        Serial.println(F("ERR,LINE_TOO_LONG"));
      }
    }
  }
}

void handleButtonEvent() {
  bool eventReceived = false;
  noInterrupts();
  if (buttonEvent) {
    buttonEvent = false;
    eventReceived = true;
  }
  interrupts();

  if (eventReceived && millis() - lastAcceptedButton >= 200) {
    lastAcceptedButton = millis();
    setRunning(!running);
  }
}

void runCycle() {
  if (!running) return;
  unsigned long now = millis();
  if (now - lastCycle >= settings.cycleTimeMs) {
    lastCycle = now;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    if (settings.debugEnabled) Serial.println(F("EVENT,CYCLE"));
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(START_STOP_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  loadSettings();
  attachInterrupt(digitalPinToInterrupt(START_STOP_PIN), startStopISR, FALLING);
  digitalWrite(LED_PIN, LOW);
  Serial.println(F("LineFollower basisprogramma klaar"));
  Serial.println(F("Commando's: START, STOP, CYCLE,<ms>, DEBUG,0/1, SAVE, STATUS"));
}

void loop() {
  handleSerial();
  handleButtonEvent();
  runCycle();
}
