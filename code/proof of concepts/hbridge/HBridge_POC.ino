#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

// H-brug-POC voor Arduino Nano + DRV8833.
// Test met beide aangedreven wielen vrij van de grond.
// Commando M,<links>,<rechts> regelt beide motoren onafhankelijk.
// S stopt onmiddellijk; elke rijtest stopt automatisch na 1 seconde.

const byte LEFT_IN1 = 11;
const byte LEFT_IN2 = 10;
const byte RIGHT_IN1 = 6;
const byte RIGHT_IN2 = 5;
const bool LEFT_INVERTED = true;
const bool RIGHT_INVERTED = false;

const int MAX_TEST_PWM = 160;
int testPWM = 80;
unsigned long stopAt = 0;
char serialBuffer[40];
byte serialIndex = 0;

void driveMotor(byte in1, byte in2, int speedValue, bool inverted) {
  speedValue = constrain(speedValue, -MAX_TEST_PWM, MAX_TEST_PWM);
  if (inverted) speedValue = -speedValue;
  if (speedValue > 0) {
    analogWrite(in1, speedValue);
    analogWrite(in2, 0);
  } else if (speedValue < 0) {
    analogWrite(in1, 0);
    analogWrite(in2, -speedValue);
  } else {
    analogWrite(in1, 0);
    analogWrite(in2, 0);
  }
}

void setMotors(int leftSpeed, int rightSpeed) {
  driveMotor(LEFT_IN1, LEFT_IN2, leftSpeed, LEFT_INVERTED);
  driveMotor(RIGHT_IN1, RIGHT_IN2, rightSpeed, RIGHT_INVERTED);
}

void stopMotors() {
  setMotors(0, 0);
  stopAt = 0;
}

void runTest(int leftSpeed, int rightSpeed) {
  setMotors(leftSpeed, rightSpeed);
  stopAt = millis() + 1000;
  Serial.print(F("MOTORS,"));
  Serial.print(leftSpeed);
  Serial.print(',');
  Serial.println(rightSpeed);
}

bool parseSignedValue(char *token, int &value) {
  if (token == NULL || *token == '\0') return false;
  char *end = NULL;
  long parsed = strtol(token, &end, 10);
  if (*end != '\0' || parsed < -MAX_TEST_PWM || parsed > MAX_TEST_PWM) return false;
  value = (int)parsed;
  return true;
}

void processCommand(char *command) {
  if (strcmp(command, "F") == 0 || strcmp(command, "f") == 0) {
    runTest(testPWM, testPWM);
  } else if (strcmp(command, "B") == 0 || strcmp(command, "b") == 0) {
    runTest(-testPWM, -testPWM);
  } else if (strcmp(command, "L") == 0 || strcmp(command, "l") == 0) {
    runTest(-testPWM, testPWM);
  } else if (strcmp(command, "R") == 0 || strcmp(command, "r") == 0) {
    runTest(testPWM, -testPWM);
  } else if (strcmp(command, "S") == 0 || strcmp(command, "s") == 0) {
    stopMotors();
    Serial.println(F("TEST,STOP"));
  } else if (command[0] == '+' && command[1] == '\0') {
    testPWM = min(testPWM + 10, MAX_TEST_PWM);
    Serial.print(F("PWM,"));
    Serial.println(testPWM);
  } else if (command[0] == '-' && command[1] == '\0') {
    testPWM = max(testPWM - 10, 40);
    Serial.print(F("PWM,"));
    Serial.println(testPWM);
  } else if (strncmp(command, "M,", 2) == 0) {
    char *leftToken = strtok(command + 2, ",");
    char *rightToken = strtok(NULL, ",");
    char *extraToken = strtok(NULL, ",");
    int left = 0;
    int right = 0;
    if (extraToken == NULL && parseSignedValue(leftToken, left) && parseSignedValue(rightToken, right)) {
      runTest(left, right);
    } else {
      Serial.println(F("ERR,USE_M,<left -160..160>,<right -160..160>"));
    }
  } else {
    Serial.println(F("ERR,UNKNOWN_COMMAND"));
  }
}

void setup() {
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
  Serial.begin(115200);
  stopMotors();
  Serial.println(F("DRV8833 H-brug POC"));
  Serial.println(F("F=vooruit B=achteruit L=links R=rechts S=stop"));
  Serial.println(F("M,<links>,<rechts> = onafhankelijke PWM (-160..160)"));
  Serial.println(F("Voorbeeld: M,80,0 of M,0,-100; + en - wijzigen testPWM"));
  Serial.println(F("Elke motorbeweging stopt automatisch na 1 seconde."));
}

void loop() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n') {
      serialBuffer[serialIndex] = '\0';
      if (serialIndex > 0) processCommand(serialBuffer);
      serialIndex = 0;
    } else if (c != '\r') {
      if (serialIndex < sizeof(serialBuffer) - 1) serialBuffer[serialIndex++] = c;
      else {
        serialIndex = 0;
        Serial.println(F("ERR,LINE_TOO_LONG"));
      }
    }
  }
  if (stopAt != 0 && (long)(millis() - stopAt) >= 0) {
    stopMotors();
    Serial.println(F("AUTO_STOP"));
  }
}
