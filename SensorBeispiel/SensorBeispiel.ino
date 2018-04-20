#include "Sensor.h"

const byte hallSensorPin = 2;
const byte photoSensorPin = 3;

Sensor *hallSensor;
Sensor *photoSensor;

void setup() {
  hallSensor = new Sensor(2);
  photoSensor = new Sensor(3);

  attachInterrupt(digitalPinToInterrupt(hallSensorPin), hallSensorISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(photoSensorPin), photoSensorISR, CHANGE);

  Serial.begin(9600);
}

void loop() {

}

void hallSensorISR() {
  Serial.print("Time:" + millis());
  Serial.print("; Hall value:" + hallSensor->getValue());
  Serial.print("; Photo value: " + photoSensor->getValue());
}

void photoSensorISR() {
  Serial.print("Time:" + millis());
  Serial.print("; Hall value:" + hallSensor->getValue());
  Serial.print("; Photo value: " + photoSensor->getValue());
}

