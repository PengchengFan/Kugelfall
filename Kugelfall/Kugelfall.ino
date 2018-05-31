#include "Sensor.h"
#include "Actor.h"
#include "Servomotor.h"
#include "Disk.h"
#include "Controller.h"

#define TRIGGERDELAY 200

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

int ballFlag = 0;
int diskFlag = 0;

void loop() {
  /*
   * trigger logic
   */
  if (trigger->isFalling())
  {
    controller->increaseTriggerCount();

    delay(TRIGGERDELAY);
    
    controller->updateReleaseTime();

    while (true) 
    {
      /*
       * this part is to decide if to release a ball, to release a ball the following conditions must be met:
       * 1. current time is between the legal time interval
       * 2. the rotation is stable
       */
      if (millis() >= controller->releaseTimeStart && millis() <= controller->releaseTimeEnd && disk->isStable() && diskFlag == 2)
//      if (millis() >= controller->releaseTimeStart && millis() <= controller->releaseTimeEnd && disk->isStable())
      {
        controller->releaseBall();
        
        ballFlag = 1;
        
        disk->stable = false;
        
        if (controller->decreaseTriggerCount())
          break;
      }
      else if (disk->isStable())
      {
//        Serial.println("---------update releasing time--------------");
        controller->updateReleaseTime();
      }
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
  /*
   * for debug
   */
//  if (button1->isFalling())
//  {
//    controller->releaseBall();
//  }
  /*
   * analog read trigger
   */
//  Serial.println(analogRead(triggerPin));
  /*
   * analog read hallsensor
   */
//   Serial.println(analogRead(hallSensorPin));
}

void photoSensorISR()
{
  disk->updatePhotoBuffer(millis());
}

void hallSensorISR()
{
  unsigned long currentTime = millis();
  
  boolean isUpdated = disk->updateHallBuffer(currentTime, hallSensor->getValue());

  // for debug
//  Serial.println(hallSensor->getValue());

  if(!isUpdated)
  {
    disk->stable = false;
  }
  else if (hallSensor->getValue() == 1)
  {
    diskFlag = (diskFlag + 1) % 3;
    
    disk->resetBufferFlag();
  }
  else if (hallSensor->getValue() == 0 && ballFlag == 1)
  {
    diskFlag = 0;
    
    disk->stable = true;
    
    ballFlag = 0;
  }
}
