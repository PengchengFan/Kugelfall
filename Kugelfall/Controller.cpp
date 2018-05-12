#include "Controller.h"

Controller::Controller(Servomotor *servo)
{
  triggerCount = 0;

  hallFlag = 0;

  photoFlag = 0;

//  lastHallPoint = 0;

  lastPhotoPoint = 0;

  _servo = servo;
}

void Controller::updateHallBuffer(unsigned long timePoint)
{
  hallFlag = (hallFlag + 1) % HALLBUFFER_SIZE;
  
//  unsigned long timeInterval = timePoint - lastHallPoint;
  
//  lastHallPoint = timePoint;
  
  hallBuffer[hallFlag] = timePoint;
}

void Controller::updatePhotoBuffer(unsigned long timePoint)
{
  photoFlag = (photoFlag + 1) % PHOTOBUFFER_SIZE;
  
  unsigned long timeInterval = timePoint - lastPhotoPoint;
  
  lastPhotoPoint = timePoint;
  
  photoBuffer[photoFlag] = timeInterval;
}

void Controller::printPhotoBuffer()
{
  int index = photoFlag;
  
  for (int i = 0; i < 12; i ++) 
  {
    Serial.println(photoBuffer[index]);
    index--;
    if (index < 0) 
      index += 12;
  }
}

void Controller::increaseTriggerCount()
{
  if (triggerCount == 0)
    triggerCount = 1;
  else
    triggerCount = 5;
}

boolean Controller::decreaseTriggerCount()
{
  triggerCount--;
  
  return triggerCount == 0;
}

boolean Controller::isStable()
{
  return false;
}

void Controller::updateReleaseTime()
{
  unsigned long timeInterval = photoBuffer[0];

  unsigned long startPoint = hallBuffer[0];

  unsigned long bias = computeBias();
  
  releaseTimeStart = startPoint + timeInterval * 6 - DELAY + bias;

  releaseTimeEnd = releaseTimeStart + timeInterval / 4;

  predictedPhotoPoint = startPoint + (photoFlag + 1) * timeInterval;
}

void Controller::releaseBall()
{
  _servo->rotate();
}

void Controller::resetBufferFlag()
{
  photoFlag = 0;

  hallFlag = 0;
}

unsigned long computeBias() 
{
  return 0;
}
