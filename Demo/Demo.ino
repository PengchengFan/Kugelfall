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
  attachInterrupt(digitalPinToInterrupt(triggerPin), triggerISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(button1Pin), button1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2Pin), button2ISR, FALLING);

  Serial.begin(9600);
}

void loop() {

}

void hallSensorISR() {
  Serial.println("Time:" + millis());
  Serial.println("; Hall value:" + hallSensor->getValue());
  Serial.println("; Photo value: " + photoSensor->getValue());
  led1->setValue(HIGH);
}

void photoSensorISR() {
  Serial.println("Time:" + millis());
  Serial.println("; Hall value:" + hallSensor->getValue());
  Serial.println("; Photo value: " + photoSensor->getValue());
  led2->setValue(HIGH);
}

void triggerISR() {
  Serial.println("Trigger activated");
  led1->setValue(HIGH);
}

void switchISR() {
  Serial.println("Swtich status: " + Switch->getValue());
  led1->setValue(HIGH);
}

void button1ISR() {
  Serial.println("button1 pressed");
  led1->setValue(HIGH);
}

void button2ISR() {
  Serial.println("button2 pressed");
  led1->setValue(HIGH);
}

