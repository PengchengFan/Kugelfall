#include "Sensor.h"
#include "Actor.h"
#include "Servomotor.h"
#include "Controller.h"

// initialize pins and components
// set pins of sensors
const byte hallSensorPin = 2;
const byte photoSensorPin = 3;
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
Sensor *hallSensor, *photoSensor, *trigger, *Switch, *button1, *button2;

// initialize pointers to the actors
Actor *blackled, *led1, *led2;
Servomotor *servo;

// initialize pointer to the main controller
Controller *controller;

void setup() 
{
  // initialize objects of components
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
  controller = new Controller(servo);
  
  // setup interrupt services
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), hallSensorISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(photoSensorPin), photoSensorISR, FALLING);
  
  Serial.begin(9600);
}

void loop() {
    /*
     * this part is to decide if to release a ball, to release a ball the following conditions must be met:
     * 1. at least one ball waiting for being released (trigger count > 0)
     * 2. current time is between the legal time interval 
     * 3. the rotation is stable
     */
//  if (controller->triggerCount > 0) 
//  {
//    if (controller->isStable() && millis() >= controller->releaseTimeStart && millis() <= controller->releaseTimeEnd)
//    {
//      controller->releaseBall();
//      controller->decreaseTriggerCount();
//    }
//    else if (controller->isStable()) 
//      controller->updateReleaseTime();
      /*
       * if the rotation is nor stable, then:
       * 1. wait until enough data needed for computing releaseing time interval are colledted
       * 2. condition 1 is also the definition of stability
       * 
       */
//  }

    /*
     * trigger logic
     */
//  if (trigger->isChanging()) 
//  {
//    controller->increaseTriggerCount();
//    
//    Serial.println(controller->triggerCount);
//    while (trigger->getValue() == 1) 
//    {
//      
//    }
//  }
}

void hallSensorISR() 
{
  Serial.print("Time: ");
  Serial.print(millis());
  Serial.print(" hallsensor: ");
  Serial.println(hallSensor->getValue());
  
  controller->updateHallBuffer(millis());
}

void photoSensorISR() 
{
  Serial.print("Time: ");
  Serial.print(millis());
  Serial.print(" photoSensor: ");
  Serial.println(photoSensor->getValue());
  
  controller->resetBufferFlag();
  
  controller->lastPhotoPoint = millis();
}
