#include <Servo.h>

Servo horizontalServo;
Servo verticalServo;

// LDR pins
const int leftLDR   = A0;
const int rightLDR  = A1;
const int topLDR    = A2;
const int bottomLDR = A3;

// Solar voltage sensor
const int voltagePin = A4;

// Servo pins
const int horizontalPin = 9;
const int verticalPin   = 10;

// Load resistance
const float loadResistance = 82.0;

// Servo positions
int horizontalAngle = 90;
int verticalAngle   = 90;

// Tracking parameters
const int threshold = 50;
const int stepSize = 1;

// Number of samples for voltage averaging
const int voltageSamples = 10;

void setup() {

  horizontalServo.attach(horizontalPin);
  verticalServo.attach(verticalPin);

  horizontalServo.write(horizontalAngle);
  verticalServo.write(verticalAngle);

  Serial.begin(9600);

  delay(500);
}

void loop() {

  // -------- LDR READINGS --------

  int leftValue   = analogRead(leftLDR);
  int rightValue  = analogRead(rightLDR);
  int topValue    = analogRead(topLDR);
  int bottomValue = analogRead(bottomLDR);


  // -------- TRACKING ERROR --------

  int horizontalError = leftValue - rightValue;
  int verticalError   = topValue - bottomValue;


  // -------- HORIZONTAL TRACKING --------

  if (horizontalError > threshold) {
    horizontalAngle += stepSize;
  }
  else if (horizontalError < -threshold) {
    horizontalAngle -= stepSize;
  }


  // -------- VERTICAL TRACKING --------

  if (verticalError > threshold) {
    verticalAngle += stepSize;
  }
  else if (verticalError < -threshold) {
    verticalAngle -= stepSize;
  }


  // -------- SERVO LIMITS --------

  horizontalAngle = constrain(horizontalAngle, 0, 180);
  verticalAngle   = constrain(verticalAngle, 0, 180);


  // -------- SERVO OUTPUT --------

  horizontalServo.write(horizontalAngle);
  verticalServo.write(verticalAngle);


  // -------- AVERAGE SOLAR VOLTAGE --------

  long totalADC = 0;

  for (int i = 0; i < voltageSamples; i++) {
    totalADC += analogRead(voltagePin);
    delay(2);
  }

  float averageADC = totalADC / (float)voltageSamples;

  // Arduino ADC voltage
  float dividerVoltage = averageADC * (5.0 / 1023.0);

  // 10kΩ-10kΩ voltage divider
  float solarVoltage = dividerVoltage * 2.0;


  // -------- CURRENT ESTIMATION --------

  float current = solarVoltage / loadResistance;


  // -------- POWER CALCULATION --------

  float power = solarVoltage * current;


  // -------- SERIAL MONITOR --------

  Serial.print("L=");
  Serial.print(leftValue);

  Serial.print(" R=");
  Serial.print(rightValue);

  Serial.print(" T=");
  Serial.print(topValue);

  Serial.print(" B=");
  Serial.print(bottomValue);

  Serial.print(" | H=");
  Serial.print(horizontalAngle);

  Serial.print(" V=");
  Serial.print(verticalAngle);

  Serial.print(" | Solar Voltage=");
  Serial.print(solarVoltage, 2);

  Serial.print(" V");

  Serial.print(" | Current=");
  Serial.print(current * 1000.0, 2);

  Serial.print(" mA");

  Serial.print(" | Power=");
  Serial.print(power * 1000.0, 2);

  Serial.println(" mW");


  delay(100);
}
