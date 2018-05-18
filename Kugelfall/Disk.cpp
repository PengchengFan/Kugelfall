#include "Disk.h"

Disk::Disk()
{
  hallIndex = 0;

  photoIndex = 0;

  lastHallPoint = 0;

  lastPhotoPoint = 0;

  stable = false;
}

void Disk::updateHallBuffer(unsigned long timePoint)
{
  hallIndex = (hallIndex + 1) % HALLBUFFER_SIZE;
  
//  unsigned long timeInterval = timePoint - lastHallPoint;
  
//  lastHallPoint = timePoint;
  
  hallBuffer[hallIndex] = timePoint;
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

void Disk::printHallBuffer()
{
  Serial.println("------------Hall Buffer------------");
  for (int i=0; i<2; i++)
  {
    Serial.println(hallBuffer[i]);
  }
}

void Disk::printPhotoBuffer()
{
  Serial.println("------------Photo Buffer------------");
  for (int i=0; i<6; i++)
  {
    Serial.println(photoBuffer[i]);
  }
}

