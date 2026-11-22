#include <Arduino.h>
#include <EEPROM.h>
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

int whiteValues[8] = {
  688, 618, 643, 568,
  590, 560, 588, 651
};

int blackValues[8] = {
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
bool debugEnabled = false;

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
unsigned long lastDebugTelemetry = 0;

const uint16_t EEPROM_MAGIC = 0x4C46;
const uint8_t EEPROM_VERSION = 1;
const int EEPROM_ADDRESS = 0;

struct PersistentRobotData {
  uint16_t magic;
  uint8_t version;
  float baseSpeed;
  int16_t maxPWM;
  int16_t minMotorPWM;
  float kp;
  float ki;
  float kd;
  float turnSlowdown;
  uint16_t lineLostTimeout;
  uint8_t speedPIEnabled;
  float targetPPS;
  float speedKp;
  float speedKi;
  uint8_t debugEnabled;
  uint16_t white[8];
  uint16_t black[8];
};

void saveRobotDataToEEPROM() {
  PersistentRobotData data;
  data.magic = EEPROM_MAGIC;
  data.version = EEPROM_VERSION;
  data.baseSpeed = baseSpeed;
  data.maxPWM = maxPWM;
  data.minMotorPWM = minMotorPWM;
  data.kp = Kp;
  data.ki = Ki;
  data.kd = Kd;
  data.turnSlowdown = turnSlowdown;
  data.lineLostTimeout = (uint16_t)lineLostTimeout;
  data.speedPIEnabled = speedPIEnabled ? 1 : 0;
  data.targetPPS = targetPPS;
  data.speedKp = speedKp;
  data.speedKi = speedKi;
  data.debugEnabled = debugEnabled ? 1 : 0;

  for (byte i = 0; i < 8; i++) {
    data.white[i] = (uint16_t)whiteValues[i];
    data.black[i] = (uint16_t)blackValues[i];
  }

  EEPROM.put(EEPROM_ADDRESS, data);
  Serial.println(F("ACK,EEPROM"));
}

bool validPersistentData(const PersistentRobotData &data) {
  if (data.magic != EEPROM_MAGIC || data.version != EEPROM_VERSION) return false;
  if (data.baseSpeed < 0 || data.baseSpeed > 200) return false;
  if (data.maxPWM < 50 || data.maxPWM > 255) return false;
  if (data.minMotorPWM < 0 || data.minMotorPWM > 150) return false;
  if (data.kp < 0 || data.kp > 100 || data.ki < 0 || data.ki > 5 ||
      data.kd < 0 || data.kd > 100) return false;
  if (data.turnSlowdown < 0 || data.turnSlowdown > 80) return false;
  if (data.lineLostTimeout < 20 || data.lineLostTimeout > 1000) return false;
  if (data.speedPIEnabled > 1 || data.debugEnabled > 1) return false;
  if (data.targetPPS < 50 || data.targetPPS > 3000) return false;
  if (data.speedKp < 0 || data.speedKp > 1 ||
      data.speedKi < 0 || data.speedKi > 0.5) return false;

  for (byte i = 0; i < 8; i++) {
    if (data.white[i] > 1023 || data.black[i] > 1023) return false;
    if (data.black[i] <= data.white[i] + 50) return false;
  }
  return true;
}

void loadRobotDataFromEEPROM() {
  PersistentRobotData data;
  EEPROM.get(EEPROM_ADDRESS, data);
  if (!validPersistentData(data)) {
    Serial.println(F("EEPROM,DEFAULTS"));
    return;
  }

  baseSpeed = data.baseSpeed;
  maxPWM = data.maxPWM;
  minMotorPWM = data.minMotorPWM;
  Kp = data.kp;
  Ki = data.ki;
  Kd = data.kd;
  turnSlowdown = data.turnSlowdown;
  lineLostTimeout = data.lineLostTimeout;
  speedPIEnabled = data.speedPIEnabled != 0;
  targetPPS = data.targetPPS;
  speedKp = data.speedKp;
  speedKi = data.speedKi;
  debugEnabled = data.debugEnabled != 0;

  for (byte i = 0; i < 8; i++) {
    whiteValues[i] = data.white[i];
    blackValues[i] = data.black[i];
  }
  Serial.println(F("EEPROM,LOADED"));
}


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


void stopRobot();

void captureSensorCalibration(bool captureBlack) {
  stopRobot();

  unsigned long sums[8] = {0};
  const byte sampleCount = 32;

  for (byte sample = 0; sample < sampleCount; sample++) {
    readSensors();
    for (byte i = 0; i < 8; i++) {
      sums[i] += (unsigned int)sensorValues[i];
    }
    delay(5);
  }

  int captured[8];
  for (byte i = 0; i < 8; i++) {
    captured[i] = (int)(sums[i] / sampleCount);
  }

  for (byte i = 0; i < 8; i++) {
    if (captureBlack) {
      if (captured[i] <= whiteValues[i] + 50) {
        Serial.println(F("ERR,CAL,CONTRAST"));
        return;
      }
    } else {
      if (blackValues[i] <= captured[i] + 50) {
        Serial.println(F("ERR,CAL,CONTRAST"));
        return;
      }
    }
  }

  for (byte i = 0; i < 8; i++) {
    if (captureBlack) blackValues[i] = captured[i];
    else whiteValues[i] = captured[i];
  }

  saveRobotDataToEEPROM();
  Serial.println(captureBlack ? F("ACK,CAL,BLACK") : F("ACK,CAL,WHITE"));
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

}


void stopRobot() {

  robotRunning = false;

  stopMotors();

  pidIntegral = 0;
  previousPidError = 0;

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
// speedPI,targetPPS,speedKp,speedKi,debug
// =========================================================

char serialBuffer[160];
byte serialIndex = 0;


void processConfiguration(char *line) {

  char *token = strtok(line, ",");

  if (token == NULL || strcmp(token, "CFG") != 0) {
    return;
  }

  float values[13];

  for (byte i = 0; i < 13; i++) {

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
  debugEnabled = values[12] >= 0.5;

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
    return;
  }

  if (strcmp(line, "SAVE") == 0) {
    saveRobotDataToEEPROM();
    return;
  }

  if (strcmp(line, "CAL,WHITE") == 0) {
    captureSensorCalibration(false);
    return;
  }

  if (strcmp(line, "CAL,BLACK") == 0) {
    captureSensorCalibration(true);
    return;
  }

  if (strcmp(line, "STATUS") == 0) {
    Serial.print(F("STATUS,"));
    Serial.print(robotRunning ? 1 : 0);
    Serial.print(',');
    Serial.print(debugEnabled ? 1 : 0);
    Serial.print(',');
    Serial.println(EEPROM.length());
    return;
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


void sendDebugTelemetry() {
  if (!debugEnabled || millis() - lastDebugTelemetry < 500) return;
  lastDebugTelemetry = millis();

  Serial.print(F("DBG,"));
  Serial.print(lastError);
  Serial.print(',');
  Serial.print(pidIntegral, 2);
  Serial.print(',');
  Serial.print(previousPidError, 2);
  Serial.print(',');
  Serial.print(leftSpeedIntegral, 2);
  Serial.print(',');
  Serial.println(rightSpeedIntegral, 2);
}


// =========================================================
// 24. SETUP
// =========================================================

void setup() {

  Serial.begin(115200);
  loadRobotDataFromEEPROM();

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

  digitalWrite(LED_PIN, HIGH);  // Power-on-indicator: brandt zolang de robot gevoed is.
}


// =========================================================
// 25. LOOP
// =========================================================

void loop() {

  handleSerial();

  checkStartButton();

  updateEncoderSpeed();

  if (robotRunning) {

    followLine();

  } else {

    stopMotors();

    int position = currentError;

    lineDetectedNow = readLine(position);

    if (lineDetectedNow) {
      currentError = position;
    }
  }

  sendTelemetry();
  sendDebugTelemetry();
}
