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
  {
    triggerCount = 1;
  }
  else
  {
    triggerCount = 5;
  }
}

boolean Controller::decreaseTriggerCount()
{
  triggerCount--;
  
  return triggerCount == 0;
}

void Controller::updateReleaseTime()
{
  unsigned long basePoint = _disk->hallBuffer[0][0];
  
  int timeInterval = _disk->photoBuffer[2];

  int sumInterval = 0;
  
  sumInterval += _disk->photoBuffer[3];
  sumInterval += _disk->photoBuffer[4];
  sumInterval += _disk->photoBuffer[5];
    
  /*
   *in high speed situation, the release time will be smaller than current time, 
   *so keep adding the estimated time of another turn, until bigger than current
   */
  if (timeInterval > MAX_INTERVAL)
  {
    Serial.println("Exceeding the minimum speed");

    return;
  }
  else if (timeInterval < MIN_INTERVAL)
  {
    Serial.println("Exceeding the maximum speed");

    return;
  }
  else if (timeInterval < 70)
  { 
    releaseTimeStart = basePoint + sumInterval * 3 - DELAY - 16;
  }
  else if (timeInterval < 160)
  {
    
    for (int i = 0; i < PHOTOBUFFER_SIZE; i++)
    {
      sumInterval += _disk->photoBuffer[i];
    }
    
    releaseTimeStart = basePoint + sumInterval - DELAY - 16;
  }
  else 
  {
    releaseTimeStart = basePoint + sumInterval - timeInterval / 8 - DELAY;
  }

  releaseTimeEnd = releaseTimeStart + timeInterval / 8;
}

void Controller::releaseBall()
{
  _servo->rotate();

  _disk->stable = false;
  
  Serial.println(_disk->photoBuffer[2]);
}

int Controller::computeBias() 
{
  if (_disk->photoBuffer[2] > _disk->photoBuffer[1])
  {
    return -1;
  }
  else if (_disk->photoBuffer[2] < _disk->photoBuffer[1])
  {
    return 1;
  }
  return 0;
}
