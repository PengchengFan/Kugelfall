#include "Disk.h"

Disk::Disk()
{
  hallIndex = 0;

  photoIndex = 0;

  lastHallPoint = 0;

  lastPhotoPoint = 0;

  stable = false;
}

void Disk::updateHallBuffer(unsigned long timePoint, int hallValue)
{

  //  test if the interrupt is valid
  if (hallBuffer[hallIndex][1] == hallValue)
  {
    stable = false;

    return;
  }

  // if the interrupt is valid
  hallIndex = (hallIndex + 1) % HALLBUFFER_SIZE;
  
  hallBuffer[hallIndex][0] = timePoint;
  hallBuffer[hallIndex][1] = hallValue;
  
  if (hallValue == 1)
  {
    resetBufferFlag();
  }
  if (hallValue == 0)
  {
    stable = true;
  }
  
}

void Disk::updatePhotoBuffer(unsigned long timePoint)
{
  int lastInterval = photoBuffer[photoIndex];
  
  photoIndex = (photoIndex + 1) % PHOTOBUFFER_SIZE;
  
  int timeInterval = timePoint - lastPhotoPoint;
  
  lastPhotoPoint = timePoint;
  
  photoBuffer[photoIndex] = timeInterval;

  //  to detect unusual movement
  if (abs(timeInterval - lastInterval) > lastInterval * MOVE_FACTOR)
  {
    stable = false;
    
    Serial.println("unusual Movement");
  }
}

boolean Disk::isStable()
{
  return stable;
}

void Disk::resetBufferFlag()
{
  photoIndex = 0;

  hallIndex = 0;
}


