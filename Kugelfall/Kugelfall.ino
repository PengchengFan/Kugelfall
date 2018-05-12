#include "Sensor.h"
#include "Actor.h"
#include "Servomotor.h"
#include "Controller.h"

// initialize pins and components
// set pins of sensors
const byte photoSensorPin = 2;
const byte hallSensorPin = 3;
const byte triggerPin = 4;
const byte switchPin = 5;
const byte button1Pin = 10;
const byte button2Pin = 11;

// set pins of actors
const byte blackBoxPin = 7;
const byte servoPin = 9;
const byte led1Pin = 12;
const byte led2Pin = 13;

// initialize pointers to the senssors
Sensor *photoSensor, *hallSensor, *trigger, *Switch, *button1, *button2;

// initialize pointers to the actors
Actor *blackled, *led1, *led2;
Servomotor *servo;

// initialize pointer to the main controller
Controller *controller;

void setup()
{
  // initialize objects of components
  photoSensor = new Sensor(photoSensorPin);
  hallSensor = new Sensor(hallSensorPin);
  trigger = new Sensor(4);
  Switch = new Sensor(5);
  button1 = new Sensor(10);
  button2 = new Sensor(11);
  blackled = new Actor(blackBoxPin);
  led1 = new Actor(led1Pin);
  led2 = new Actor(led2Pin);
  servo = new Servomotor(servoPin);
  controller = new Controller(servo);

  // setup interrupt services
  attachInterrupt(digitalPinToInterrupt(photoSensorPin), photoSensorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), hallSensorISR, CHANGE);

  Serial.begin(9600);
}

void loop() {
    /*
     * trigger logic
     */
  if (trigger->isFalling())
  {
    controller->increaseTriggerCount();
    while (true) 
    {
      /*
       * this part is to decide if to release a ball, to release a ball the following conditions must be met:
       * 1. current time is between the legal time interval
       * 2. the rotation is stable
       */
      if (controller->isStable() && millis() >= controller->releaseTimeStart && millis() <= controller->releaseTimeEnd)
      {
        controller->releaseBall();
        if (controller->decreaseTriggerCount())
          break;
      }
      else if (controller->isStable())
        controller->updateReleaseTime();
        /*
         * if the rotation is not stable, then:
         * 1. wait until enough data needed for computing releaseing time interval are colledted
         * 2. condition 1 is also the definition of stability
         */
  
      /*
       * if the trigger is pressed two times
       */
      if (trigger->isFalling())
        controller->increaseTriggerCount();
    }
  }
  
  if (button1->getValue() == 1)
  {
    Serial.println(1);
    controller->releaseBall();
//    controller->printPhotoBuffer();
  }
  
}

void photoSensorISR()
{
  controller->updatePhotoBuffer(millis());
}

void hallSensorISR()
{
  if (hallSensor->getValue() == 0)
    controller->resetBufferFlag();

  controller->updateHallBuffer(millis());
}
