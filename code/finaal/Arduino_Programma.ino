#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

const byte LEFT_IN1 = 11;
const byte LEFT_IN2 = 10;

const byte RIGHT_IN1 = 6;
const byte RIGHT_IN2 = 5;

const byte BUTTON_PIN = 8;
const byte LED_PIN = 13;

// Physical order: HY-S301 D1 (left) -> A0 ... D8 (right) -> A7.
const byte sensorPins[8] = {
  A0, A1, A2, A3, A4, A5, A6, A7
};

const byte LEFT_ENCODER_A = 3;
const byte LEFT_ENCODER_B = 4;

const byte RIGHT_ENCODER_A = 9;
const byte RIGHT_ENCODER_B = 7;

const bool LEFT_INVERTED = true;
const bool RIGHT_INVERTED = false;

const int LEFT_ENCODER_SIGN = -1;
const int RIGHT_ENCODER_SIGN = 1;

const int whiteValues[8] = {
  688, 618, 643, 568,
  590, 560, 588, 651
};

const int blackValues[8] = {
  1009, 994, 1003, 990,
  997, 996, 994, 1005
};

const int sensorPositions[8] = {
  -3500, -2500, -1500, -500,
    500,  1500,  2500, 3500
};

float baseSpeed = 70.0;
int maxPWM = 160;
int minMotorPWM = 0;

float Kp = 30.0;
float Ki = 0.0;
float Kd = 0.0;

float turnSlowdown = 0.0;

unsigned long lineLostTimeout = 80;

bool speedPIEnabled = false;

float targetPPS = 800.0;
float speedKp = 0.05;
float speedKi = 0.01;

const int SENSOR_NOISE_LIMIT = 150;
const int MIN_LINE_STRENGTH = 300;

bool robotRunning = false;
bool lineDetectedNow = false;

int sensorValues[8];
int normalizedValues[8];

int currentError = 0;
int lastError = 0;

int currentLeftSpeed = 0;
int currentRightSpeed = 0;

unsigned long lastLineSeen = 0;


// Startknop
unsigned long lastButtonTime = 0;
const unsigned long BUTTON_DEBOUNCE = 50;

bool lastButtonReading = HIGH;
bool stableButtonState = HIGH;


// PID
float pidIntegral = 0.0;
float previousPidError = 0.0;
unsigned long lastPidMicros = 0;


// =========================================================
// 7. ENCODERS
// =========================================================

volatile long leftEncoderRaw = 0;
volatile long rightEncoderRaw = 0;

long previousLeftCount = 0;
long previousRightCount = 0;

float leftPulsesPerSecond = 0.0;
float rightPulsesPerSecond = 0.0;

unsigned long lastEncoderUpdate = 0;


// PI snelheidsregeling
float leftSpeedIntegral = 0.0;
float rightSpeedIntegral = 0.0;

float leftTargetPPS = 0.0;
float rightTargetPPS = 0.0;

unsigned long lastSpeedControl = 0;


// =========================================================
// 8. TELEMETRIE
// =========================================================

unsigned long lastTelemetry = 0;
const unsigned long TELEMETRY_INTERVAL = 100;


// =========================================================
// 9. ENCODER INTERRUPTS
// =========================================================

// Linker encoder: D3 / D4

void leftEncoderISR() {

  bool a = (PIND & _BV(PD3)) != 0;
  bool b = (PIND & _BV(PD4)) != 0;

  if (a == b) {
    leftEncoderRaw++;
  } else {
    leftEncoderRaw--;
  }
}


// Rechter encoder: D9 / D7

ISR(PCINT0_vect) {

  bool a = (PINB & _BV(PB1)) != 0;
  bool b = (PIND & _BV(PD7)) != 0;

  if (a == b) {
    rightEncoderRaw++;
  } else {
    rightEncoderRaw--;
  }
}


// =========================================================
// 10. ENCODERWAARDEN
// =========================================================

long getLeftEncoderCount() {

  noInterrupts();
  long value = leftEncoderRaw;
  interrupts();

  return value * LEFT_ENCODER_SIGN;
}


long getRightEncoderCount() {

  noInterrupts();
  long value = rightEncoderRaw;
  interrupts();

  return value * RIGHT_ENCODER_SIGN;
}


// =========================================================
// 11. ENCODERSNELHEID
// =========================================================

void updateEncoderSpeed() {

  unsigned long now = millis();
  unsigned long elapsed = now - lastEncoderUpdate;

  if (elapsed < 50) {
    return;
  }

  long leftCount = getLeftEncoderCount();
  long rightCount = getRightEncoderCount();

  long deltaLeft = leftCount - previousLeftCount;
  long deltaRight = rightCount - previousRightCount;

  leftPulsesPerSecond =
    deltaLeft * 1000.0 / elapsed;

  rightPulsesPerSecond =
    deltaRight * 1000.0 / elapsed;

  previousLeftCount = leftCount;
  previousRightCount = rightCount;

  lastEncoderUpdate = now;
}


// =========================================================
// 12. MOTORFUNCTIES
// =========================================================

void setMotor(
  int in1,
  int in2,
  int speedValue,
  bool inverted
) {

  speedValue = constrain(speedValue, -255, 255);

  if (inverted) {
    speedValue = -speedValue;
  }

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


int applyMinimumPWM(int value) {

  value = constrain(value, -maxPWM, maxPWM);

  if (value > 0 && value < minMotorPWM) {
    value = minMotorPWM;
  }

  if (value < 0 && value > -minMotorPWM) {
    value = -minMotorPWM;
  }

  return value;
}


void setMotors(int leftSpeed, int rightSpeed) {

  leftSpeed = applyMinimumPWM(leftSpeed);
  rightSpeed = applyMinimumPWM(rightSpeed);

  currentLeftSpeed = leftSpeed;
  currentRightSpeed = rightSpeed;

  setMotor(
    LEFT_IN1, LEFT_IN2,
    leftSpeed, LEFT_INVERTED
  );

  setMotor(
    RIGHT_IN1, RIGHT_IN2,
    rightSpeed, RIGHT_INVERTED
  );
}


void stopMotors() {

  currentLeftSpeed = 0;
  currentRightSpeed = 0;

  leftTargetPPS = 0;
  rightTargetPPS = 0;

  leftSpeedIntegral = 0;
  rightSpeedIntegral = 0;

  setMotors(0, 0);
}


// =========================================================
// 13. SENSORFUNCTIES
// =========================================================

void readSensors() {

  for (byte i = 0; i < 8; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
  }
}


void normalizeSensors() {

  for (byte i = 0; i < 8; i++) {

    int value = map(
      sensorValues[i],
      whiteValues[i],
      blackValues[i],
      0,
      1000
    );

    value = constrain(value, 0, 1000);

    if (value < SENSOR_NOISE_LIMIT) {
      value = 0;
    }

    normalizedValues[i] = value;
  }
}


// =========================================================
// 14. LIJNPOSITIE
// =========================================================

bool readLine(int &position) {

  readSensors();
  normalizeSensors();

  long weightedSum = 0;
  long totalStrength = 0;

  for (byte i = 0; i < 8; i++) {

    int value = normalizedValues[i];

    weightedSum +=
      (long)value * sensorPositions[i];

    totalStrength += value;
  }

  if (totalStrength < MIN_LINE_STRENGTH) {
    return false;
  }

  position = weightedSum / totalStrength;

  return true;
}


// =========================================================
// 15. PID-REGELAAR
// =========================================================

int calculateCorrection(int error) {

  unsigned long now = micros();

  float dt = (now - lastPidMicros) / 1000000.0;

  if (dt <= 0.0 || dt > 0.1) {
    dt = 0.01;
  }

  lastPidMicros = now;

  pidIntegral += error * dt;

  pidIntegral = constrain(
    pidIntegral, -10000.0, 10000.0
  );

  float derivative =
    (error - previousPidError) / dt;

  previousPidError = error;

  float correction =
    (Kp * error) / 1000.0
    + (Ki * pidIntegral) / 1000.0
    + (Kd * derivative) / 1000.0;

  return (int)correction;
}


// =========================================================
// 16. PI-SNELHEIDSREGELING
// =========================================================

void updateSpeedPI() {

  if (!speedPIEnabled || !robotRunning) {
    return;
  }

  unsigned long now = millis();
  unsigned long elapsed = now - lastSpeedControl;

  if (elapsed < 20) {
    return;
  }

  float dt = elapsed / 1000.0;
  lastSpeedControl = now;

  float leftError =
    leftTargetPPS - leftPulsesPerSecond;

  float rightError =
    rightTargetPPS - rightPulsesPerSecond;

  leftSpeedIntegral += leftError * dt;
  rightSpeedIntegral += rightError * dt;

  leftSpeedIntegral = constrain(
    leftSpeedIntegral, -5000.0, 5000.0
  );

  rightSpeedIntegral = constrain(
    rightSpeedIntegral, -5000.0, 5000.0
  );

  // Feed-forward volgt de gewenste snelheid. Daardoor blijft ook
  // de ingestelde bochtvertraging actief wanneer speed-PI aan staat.
  float leftFeedForward =
    baseSpeed * (leftTargetPPS / targetPPS);

  float rightFeedForward =
    baseSpeed * (rightTargetPPS / targetPPS);

  float leftOutput =
    leftFeedForward
    + speedKp * leftError
    + speedKi * leftSpeedIntegral;

  float rightOutput =
    rightFeedForward
    + speedKp * rightError
    + speedKi * rightSpeedIntegral;

  int leftPWM = constrain(
    (int)leftOutput, -maxPWM, maxPWM
  );

  int rightPWM = constrain(
    (int)rightOutput, -maxPWM, maxPWM
  );

  setMotors(leftPWM, rightPWM);
}


// =========================================================
// 17. MOTORCOMMANDO'S
// =========================================================

void commandMotors(
  int correction,
  float effectiveBaseSpeed
) {

  if (!speedPIEnabled) {

    int leftSpeed =
      (int)effectiveBaseSpeed - correction;

    int rightSpeed =
      (int)effectiveBaseSpeed + correction;

    leftSpeed = constrain(
      leftSpeed, -maxPWM, maxPWM
    );

    rightSpeed = constrain(
      rightSpeed, -maxPWM, maxPWM
    );

    setMotors(leftSpeed, rightSpeed);

    return;
  }

  // Omzetting van de oorspronkelijke PWM-correctie
  // naar een verschil in gewenste pulssnelheid.

  float deltaPPS =
    correction * targetPPS /
    (baseSpeed > 1.0 ? baseSpeed : 1.0);

  float speedScale =
    effectiveBaseSpeed /
    (baseSpeed > 1.0 ? baseSpeed : 1.0);

  float target = targetPPS * speedScale;

  leftTargetPPS = constrain(
    target - deltaPPS,
    -targetPPS,
    targetPPS
  );

  rightTargetPPS = constrain(
    target + deltaPPS,
    -targetPPS,
    targetPPS
  );

  updateSpeedPI();
}


// =========================================================
// 18. LIJNVOLGEN
// =========================================================

void followLine() {

  int position = currentError;

  bool detected = readLine(position);

  lineDetectedNow = detected;

  if (detected) {

    lastLineSeen = millis();

    currentError = position;
    lastError = currentError;

    int correction =
      calculateCorrection(currentError);

    float curveAmount =
      constrain(
        abs(currentError) / 3500.0,
        0.0,
        1.0
      );

    float effectiveBaseSpeed =
      baseSpeed *
      (1.0 - (turnSlowdown / 100.0) * curveAmount);

    commandMotors(correction, effectiveBaseSpeed);

  } else {

    if (millis() - lastLineSeen < lineLostTimeout) {

      int correction =
        calculateCorrection(lastError);

      commandMotors(correction, baseSpeed);

    } else {

      stopMotors();
    }
  }
}


// =========================================================
// 19. START / STOP
// =========================================================

void startRobot() {

  robotRunning = true;

  lastLineSeen = millis();

  pidIntegral = 0;
  previousPidError = 0;
  lastPidMicros = micros();

  leftSpeedIntegral = 0;
  rightSpeedIntegral = 0;

  lastSpeedControl = millis();

  digitalWrite(LED_PIN, HIGH);
}


void stopRobot() {

  robotRunning = false;

  stopMotors();

  pidIntegral = 0;
  previousPidError = 0;

  digitalWrite(LED_PIN, LOW);
}


// =========================================================
// 20. FYSIEKE STARTKNOP
// =========================================================

void checkStartButton() {

  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastButtonTime = millis();
  }

  if (millis() - lastButtonTime > BUTTON_DEBOUNCE) {

    if (reading != stableButtonState) {

      stableButtonState = reading;

      if (stableButtonState == LOW) {

        if (robotRunning) {
          stopRobot();
        } else {
          startRobot();
        }
      }
    }
  }

  lastButtonReading = reading;
}


// =========================================================
// 21. CONFIGURATIE ONTVANGEN
//
// CFG,base,max,kp,ki,kd,min,turn,timeout,
// speedPI,targetPPS,speedKp,speedKi
// =========================================================

char serialBuffer[160];
byte serialIndex = 0;


void processConfiguration(char *line) {

  char *token = strtok(line, ",");

  if (token == NULL || strcmp(token, "CFG") != 0) {
    return;
  }

  float values[12];

  for (byte i = 0; i < 12; i++) {

    token = strtok(NULL, ",");

    if (token == NULL) {
      return;
    }

    values[i] = atof(token);
  }

  baseSpeed = constrain(values[0], 0.0, 200.0);
  maxPWM = constrain((int)values[1], 50, 255);

  Kp = constrain(values[2], 0.0, 100.0);
  Ki = constrain(values[3], 0.0, 5.0);
  Kd = constrain(values[4], 0.0, 100.0);

  minMotorPWM = constrain((int)values[5], 0, 150);

  turnSlowdown = constrain(values[6], 0.0, 80.0);

  lineLostTimeout = constrain(
    (unsigned long)values[7], 20UL, 1000UL
  );

  speedPIEnabled = values[8] >= 0.5;

  targetPPS = constrain(values[9], 50.0, 3000.0);

  speedKp = constrain(values[10], 0.0, 1.0);
  speedKi = constrain(values[11], 0.0, 0.5);

  Serial.println("ACK,CFG");
}


// =========================================================
// 22. SERIËLE COMMANDO'S
// =========================================================

void processSerialLine(char *line) {

  if (strcmp(line, "START") == 0) {
    startRobot();
    return;
  }

  if (strcmp(line, "STOP") == 0) {
    stopRobot();
    return;
  }

  if (strncmp(line, "CFG,", 4) == 0) {
    processConfiguration(line);
  }
}


void handleSerial() {

  while (Serial.available()) {

    char c = Serial.read();

    if (c == '\n') {

      serialBuffer[serialIndex] = '\0';

      if (serialIndex > 0) {
        processSerialLine(serialBuffer);
      }

      serialIndex = 0;

    } else if (c != '\r') {

      if (serialIndex < sizeof(serialBuffer) - 1) {
        serialBuffer[serialIndex++] = c;
      } else {
        serialIndex = 0;
      }
    }
  }
}


// =========================================================
// 23. TELEMETRIE
// T,run,line,pos,raw0..7,norm0..7,
// leftCount,rightCount,leftPPS,rightPPS,leftPWM,rightPWM
// =========================================================

void sendTelemetry() {

  if (millis() - lastTelemetry < TELEMETRY_INTERVAL) {
    return;
  }

  lastTelemetry = millis();

  Serial.print("T,");

  Serial.print(robotRunning ? 1 : 0);
  Serial.print(",");

  Serial.print(lineDetectedNow ? 1 : 0);
  Serial.print(",");

  Serial.print(currentError);

  for (byte i = 0; i < 8; i++) {
    Serial.print(",");
    Serial.print(sensorValues[i]);
  }

  for (byte i = 0; i < 8; i++) {
    Serial.print(",");
    Serial.print(normalizedValues[i]);
  }

  Serial.print(",");
  Serial.print(getLeftEncoderCount());

  Serial.print(",");
  Serial.print(getRightEncoderCount());

  Serial.print(",");
  Serial.print(leftPulsesPerSecond, 1);

  Serial.print(",");
  Serial.print(rightPulsesPerSecond, 1);

  Serial.print(",");
  Serial.print(currentLeftSpeed);

  Serial.print(",");
  Serial.println(currentRightSpeed);
}


// =========================================================
// 24. SETUP
// =========================================================

void setup() {

  Serial.begin(115200);

  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);

  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  pinMode(LEFT_ENCODER_A, INPUT_PULLUP);
  pinMode(LEFT_ENCODER_B, INPUT_PULLUP);

  pinMode(RIGHT_ENCODER_A, INPUT_PULLUP);
  pinMode(RIGHT_ENCODER_B, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(LEFT_ENCODER_A),
    leftEncoderISR,
    CHANGE
  );

  PCICR |= _BV(PCIE0);
  PCMSK0 |= _BV(PCINT1);

  stopMotors();

  previousLeftCount = getLeftEncoderCount();
  previousRightCount = getRightEncoderCount();

  lastEncoderUpdate = millis();
  lastSpeedControl = millis();
  lastTelemetry = millis();

  lastLineSeen = millis();

  digitalWrite(LED_PIN, LOW);
}


// =========================================================
// 25. LOOP
// =========================================================

void loop() {

  handleSerial();

  checkStartButton();

  updateEncoderSpeed();

  if (robotRunning) {

    digitalWrite(LED_PIN, HIGH);

    followLine();

  } else {

    digitalWrite(LED_PIN, LOW);

    stopMotors();

    int position = currentError;

    lineDetectedNow = readLine(position);

    if (lineDetectedNow) {
      currentError = position;
    }
  }

  sendTelemetry();
}
