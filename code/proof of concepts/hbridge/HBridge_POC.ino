#include <Arduino.h>

// H-brugtest voor Arduino Nano + DRV8833.
// Test met de aangedreven wielen vrij van de grond.

const byte LEFT_IN1 = 11;
const byte LEFT_IN2 = 10;
const byte RIGHT_IN1 = 6;
const byte RIGHT_IN2 = 5;
const bool LEFT_INVERTED = true;
const bool RIGHT_INVERTED = false;

int testPWM = 80;
unsigned long stopAt = 0;

void driveMotor(byte in1, byte in2, int speedValue, bool inverted) {
  speedValue = constrain(speedValue, -255, 255);
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
  stopAt = millis() + 1000;  // automatische veiligheidsstop na 1 seconde
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
  Serial.println(F("+=PWM +10, -=PWM -10; elke beweging stopt na 1 seconde"));
}

void loop() {
  while (Serial.available() > 0) {
    char command = (char)Serial.read();
    switch (command) {
      case 'F': case 'f': runTest(testPWM, testPWM); Serial.println(F("TEST,FORWARD")); break;
      case 'B': case 'b': runTest(-testPWM, -testPWM); Serial.println(F("TEST,REVERSE")); break;
      case 'L': case 'l': runTest(-testPWM, testPWM); Serial.println(F("TEST,LEFT")); break;
      case 'R': case 'r': runTest(testPWM, -testPWM); Serial.println(F("TEST,RIGHT")); break;
      case 'S': case 's': stopMotors(); Serial.println(F("TEST,STOP")); break;
      case '+': testPWM = min(testPWM + 10, 160); Serial.print(F("PWM,")); Serial.println(testPWM); break;
      case '-': testPWM = max(testPWM - 10, 40); Serial.print(F("PWM,")); Serial.println(testPWM); break;
    }
  }
  if (stopAt != 0 && (long)(millis() - stopAt) >= 0) {
    stopMotors();
    Serial.println(F("AUTO_STOP"));
  }
}
