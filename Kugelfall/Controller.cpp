#include "Controller.h"

Controller::Controller(Servomotor *servo, Disk *disk)
{
  triggerCount = 0;

  biasCount = 0;

  bias = 0;

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
  unsigned long timeInterval = _disk->photoBuffer[1];

  unsigned long startPoint = _disk->hallBuffer[1];

//  unsigned long timeInterval = _disk->photoBuffer[0];
//
//  unsigned long startPoint = _disk->hallBuffer[2];
//  
//  releaseTimeStart = startPoint + timeInterval * 3 - DELAY;

  // if the release time is already passed or not updated, then compute a new release time
  releaseTimeStart = startPoint + timeInterval * 6 + 2 - DELAY + bias;
  
  /*
   *in high speed situation, the release time will be smaller than current time, 
   *so keep adding the estimated time of another turn, until bigger than current
   */
  while (releaseTimeStart < millis())
  {
    releaseTimeStart += timeInterval * 6 + bias;
  }

  releaseTimeEnd = releaseTimeStart + timeInterval / 2;
}

void Controller::releaseBall()
{
  _servo->rotate();
}

unsigned long Controller::updateBias() 
{
  unsigned long timeInterval = _disk->photoBuffer[1];
  
  // incrementally computing average bias
  biasCount += 1;

  if (SPEEDWALL < 373)
  {
    bias = (1 - 1 / biasCount) * bias + 1 / biasCount * (_disk->hallBuffer[1] - (releaseTimeStart + DELAY));
  }
  else
  {
    bias += _disk->hallBuffer[1] - (releaseTimeStart + DELAY);
  }
  
  #ifdef DEBUG
  Serial.print("bias: ");
  Serial.println(bias);
  #endif

  
  // original bias computation
//  unsigned long timeInterval = _disk->photoBuffer[0];
//  unsigned long timeInterval2 = _disk->photoBuffer[6];
//  bias = timeInterval - timeInterval2;

//  if (timeInterval >= 50 && timeInterval < 140)
//  {
//    Serial.println(1);
////    bias = ((0.2 * timeInterval) - 5);
//  }
//  else if (timeInterval >= 140 && timeInterval < 500) 
//  {
//    Serial.println(2);
////    bias = ((0.06 * timeInterval) + 5);
//    
//  }
//  else
//  {
//    Serial.println(3);
////    bias = 15;
//  }
}
