#include "Sensor.h"
#include "Actor.h"
#include "Servomotor.h"
#include "Disk.h"
#include "Controller.h"
#include "MsTimer2.h"

#define DEBUG 0

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
//  MsTimer::set(30, triggerISR);
//  MsTimer::start();

  Serial.begin(9600);

  Serial.println("Initialization finished");
}
int diskFlag = 0;
void loop() {
  /*
   * trigger logic
   */
  if (trigger->isFalling())
  {
    controller->increaseTriggerCount();

    #ifdef DEBUG
    Serial.print("next h=0 start: ");
    Serial.println(controller->releaseTimeStart + DELAY);
    Serial.print("next h=0 end: ");
    Serial.println(controller->releaseTimeEnd + DELAY);
    #endif
    
    while (true) 
    {
      /*
       * this part is to decide if to release a ball, to release a ball the following conditions must be met:
       * 1. current time is between the legal time interval
       * 2. the rotation is stable
       */
      if (disk->stable && millis() >= controller->releaseTimeStart && millis() <= controller->releaseTimeEnd && diskFlag % 2 == 0)
      {
        controller->releaseBall();
        
        #ifdef DEBUG
        Serial.print("time for release: ");
        Serial.println(millis());
        #endif
        
        disk->stable = 0;
        
        if (controller->decreaseTriggerCount())
          break;
      }
//      else if (millis() >= controller->releaseTimeEnd)
//      {
//        #ifdef DEBUG
//        Serial.print("next h=0 start: ");
//        Serial.println(controller->releaseTimeStart + DELAY);
//        Serial.print("next h=0 end: ");
//        Serial.println(controller->releaseTimeEnd + DELAY);
//        #endif
//
//        controller->updateReleaseTime();
//      }
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
  
}

void photoSensorISR()
{
  disk->updatePhotoBuffer(millis());

  if (disk->photoIndex == 1) 
    controller->updateReleaseTime();
}

void hallSensorISR()
{
  disk->updateHallBuffer(millis());
  
  if (hallSensor->getValue() == 0)
  {
    diskFlag ++;

    disk->stable = 0;
    
    disk->resetBufferFlag();
    
    controller->updateBias();
    
    #ifdef DEBUG
    Serial.print("next h=0 start: ");
    Serial.println(controller->releaseTimeStart + DELAY);
    Serial.print("next h=0 end: ");
    Serial.println(controller->releaseTimeEnd + DELAY);
    Serial.print("base time:");
    Serial.println(millis());
    #endif
  }
}

void triggerISR()
{
  if (trigger->isFalling())
  {
    controller->increaseTriggerCount();
  }
}

