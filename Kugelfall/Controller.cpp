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
  unsigned long timeInterval = _disk->photoBuffer[0];

  unsigned long startPoint = _disk->hallBuffer[1];

  unsigned long bias = computeBias();

  if (timeInterval < SPEEDWALL) 
  {
    // if the release time is already passed or not updated, then compute a new release time
    releaseTimeStart = startPoint + timeInterval * 6 - DELAY + bias;
    
    /*
     *in high speed situation, the release time will be smaller than current time, 
     *so keep adding the estimated time of another turn, until bigger than current
     */
    while (releaseTimeStart < millis())
    {
      releaseTimeStart += timeInterval * 6;
    }
  
  //    releaseTimeEnd = releaseTimeStart + timeInterval / 4;
    releaseTimeEnd = releaseTimeStart + timeInterval;
  }
}

void Controller::releaseBall()
{
  _servo->rotate();
}

unsigned long Controller::computeBias() 
{  
  unsigned long timeInterval = _disk->photoBuffer[0];
  unsigned long bias = 0;
  
  if(timeInterval >= 0 && timeInterval < 50)
    bias = 0;
  else if (timeInterval >= 50 && timeInterval < 100) 
    bias = ((0.2 * timeInterval) - 10); 
  else if (timeInterval >= 100 && timeInterval < 300) 
    bias = ((0.06 * timeInterval) + 10);
  else 
    bias = 30;

  return bias;
}
