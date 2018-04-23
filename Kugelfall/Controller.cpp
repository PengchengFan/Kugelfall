#include "Controller.h"

Controller::Controller(Servomotor *servo) 
{
  triggerCount = 0;
  
  hallFlag = 0;
  
//  photoFlag = 0;

  lastHallPoint = 0;
  
//  lastPhotoPoint = 0;

  _servo = servo;
}

void Controller::updateHallBuffer(unsigned long timePoint) 
{
  unsigned long timeInterval = timePoint - lastHallPoint;
  
  lastHallPoint = timePoint;
  
  hallBuffer[hallFlag] = timeInterval;
  
//  hallFlag = (hallFlag + 1) % HALLBUFFER_SIZE;
}

//void Controller::updatePhotoBuffer(unsigned long timePoint) 
//{
//  photoFlag = (photoFlag + 1) % PHOTOBUFFER_SIZE;
//
//  unsigned long timeInterval = timePoint - lastPhotoPoint;
//
//  lastPhotoPoint = timePoint;
//
//  photoBuffer[photoFlag] = timeInterval;
//}

void Controller::increaseTriggerCount() 
{
  triggerCount++;
}

boolean Controller::isStable() 
{
  
}

void Controller::updateReleaseTime() 
{
//  releaseTimeStart = result;

//  releaseTimeEnd = releaseTimeStart + photoBuffer[photoFlag]
}

void Controller::releaseBall() 
{
  _servo->rotate();
}

void Controller::resetBufferFlag() 
{
  hallFlag = 0;
}

