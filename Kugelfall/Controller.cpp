#include "Controller.h"

Controller::Controller(Servomotor *servo, Disk *disk)
{
  triggerCount = 0;

  _servo = servo;

  _disk = disk;
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

void Controller::updateReleaseTime()
{
  unsigned long timeInterval = _disk->photoBuffer[2];

  unsigned long basePoint = _disk->hallBuffer[0][0];

  unsigned long bias = computeBias();

  // if the release time is already passed or not updated, then compute a new release time
  releaseTimeStart = basePoint + timeInterval * 3 - DELAY + bias;
  
  /*
   *in high speed situation, the release time will be smaller than current time, 
   *so keep adding the estimated time of another turn, until bigger than current
   */
  while (releaseTimeStart < millis())
  {
    releaseTimeStart += timeInterval * 6;
  }
  
  releaseTimeEnd = releaseTimeStart + timeInterval / 4;
 
}

void Controller::releaseBall()
{
  _servo->rotate();
}

unsigned long Controller::computeBias() 
{
  return 0;
}
