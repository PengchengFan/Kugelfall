#include "Sensor.h"
#include "Actor.h"
#include "Servomotor.h"
#include "Disk.h"
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
Disk *disk;
Controller *controller;

int diskFlag = 0;

void setup()
{
  // initialize objects of components
  photoSensor = new Sensor(photoSensorPin);
  hallSensor = new Sensor(hallSensorPin);
  trigger = new Sensor(triggerPin);
  Switch = new Sensor(switchPin);
  button1 = new Sensor(button1Pin);
  button2 = new Sensor(button2Pin);
  blackled = new Actor(blackBoxPin);
  led1 = new Actor(led1Pin);
  led2 = new Actor(led2Pin);
  servo = new Servomotor(servoPin);

  disk = new Disk();
  controller = new Controller(servo, disk);

  // setup interrupt services
  attachInterrupt(digitalPinToInterrupt(photoSensorPin), photoSensorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), hallSensorISR, CHANGE);

  Serial.begin(9600);

  Serial.println("initialization finished");
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
      if (millis() >= controller->releaseTimeStart && millis() <= controller->releaseTimeEnd && disk->isStable())
      {
        controller->releaseBall();
        
        if (controller->decreaseTriggerCount())
        {
          break;
        }
      }
      /*
       * if the legal time interval is arrving or has already left
       * calculate a new time interval for releasing ball
       */
      else if (disk->isStable())
      {
        controller->updateReleaseTime();
      }
      /*
       * if the trigger is pressed two times
       */
      if (trigger->isFalling())
      {
        controller->increaseTriggerCount();
      }
    }
  }
  /*
   * for debug
   */
//  if (button1->isFalling())
//  {
//    controller->releaseBall();
//
//    Serial.println("release a ball");
//  }
}

void photoSensorISR()
{
  disk->updatePhotoBuffer(millis());
}

void hallSensorISR()
{ 
  disk->updateHallBuffer(millis(), hallSensor->getValue());

  // for debug
//  Serial.println(hallSensor->getValue());
}
