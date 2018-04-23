#include "Sensor.h"
#include "Actor.h"
#include "Servomotor.h"

const byte hallSensorPin = 2;
const byte photoSensorPin = 3;
const byte triggerPin = 4;
const byte switchPin = 5;
const byte button1Pin = 10;
const byte button2Pin = 11;

const byte blackBoxPin = 7;
const byte servoPin = 9;
const byte led1Pin = 12;
const byte led2Pin = 13;

Sensor *hallSensor, *photoSensor, *trigger, *Switch, *button1, *button2;

Actor *blackled, *led1, *led2;

Servomotor *servo;

void setup() {
  hallSensor = new Sensor(hallSensorPin);
  photoSensor = new Sensor(photoSensorPin);
  trigger = new Sensor(4);
  Switch = new Sensor(5);
  button1 = new Sensor(10);
  button2 = new Sensor(11);

  blackled = new Actor(blackBoxPin);
  led1 = new Actor(led1Pin);
  led2 = new Actor(led2Pin);

  servo = new Servomotor(servoPin);

  attachInterrupt(digitalPinToInterrupt(hallSensorPin), hallSensorISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(photoSensorPin), photoSensorISR, CHANGE);
  Serial.begin(9600);
}
int count = 0;
void loop() {
  if (trigger->getValue()) {
    led1->setValue(HIGH);
    delay(100);
    led1->setValue(LOW);
  }
  if (Switch->getValue()) {
    blackled->setValue(HIGH);
    delay(100);
    blackled->setValue(LOW);
  }
  if (button1->getValue()) {
    led1->setValue(HIGH);
    delay(100);
    led1->setValue(LOW);
  }
  if (button2->getValue()) {
    led2->setValue(HIGH);
    delay(100);
    led2->setValue(LOW);
  }
}

void hallSensorISR() {
  led2->setValue(HIGH);
  delay(100);
  led2->setValue(LOW);
}

void photoSensorISR() {
  led1->setValue(HIGH);
  delay(100);
  led1->setValue(LOW);
}
