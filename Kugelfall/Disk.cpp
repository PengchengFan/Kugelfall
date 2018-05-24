#include "Disk.h"

Disk::Disk()
{
  hallIndex = 0;

  photoIndex = 0;

  lastHallPoint = 0;

  lastPhotoPoint = 0;

  stable = false;
}

boolean Disk::updateHallBuffer(unsigned long timePoint, int hallValue)
{
  
  if (hallBuffer[hallIndex][1] == hallValue)
  {
    return false;
  }
  
  hallIndex = (hallIndex + 1) % HALLBUFFER_SIZE;
  
  hallBuffer[hallIndex][0] = timePoint;
  hallBuffer[hallIndex][1] = hallValue;
  
  return true;
}

void Disk::updatePhotoBuffer(unsigned long timePoint)
{
  unsigned long lastInterval = photoBuffer[photoIndex];
  
  photoIndex = (photoIndex + 1) % PHOTOBUFFER_SIZE;
  
  unsigned long timeInterval = timePoint - lastPhotoPoint;
  
  lastPhotoPoint = timePoint;
  
  photoBuffer[photoIndex] = timeInterval;

//  if (abs(timeInterval - lastInterval) > lastInterval * 0.03)
//    stable = false;
}

boolean Disk::isStable()
{
  return stable;
}

void Disk::resetBufferFlag()
{
  photoIndex = 0;

  hallIndex = 0;

  stable = true;
}


