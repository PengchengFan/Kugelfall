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

  unsigned long startPoint = _disk->hallBuffer[0];

  unsigned long bias = computeBias();

  // if the release time is already passed or not updated, then compute a new release time
  if (releaseTimeStart > millis())
  {
    releaseTimeStart = startPoint + timeInterval * 6 - DELAY + bias;//starpoint是霍尔传感器的时间点，加上转一圈的时间，然后减去自由落体的时间，加上修正值
    
    /*
     *in high speed situation, the release time will be smaller than current time, 
     *so keep adding the estimated time of another turn, until bigger than current
     */
    while (releaseTimeStart < millis())
    {
      releaseTimeStart += timeInterval * 6;//如果还没有到下落时间，则一直更新释放开始时间，更新到下一圈的释放时间点。
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
  return 0;
}
