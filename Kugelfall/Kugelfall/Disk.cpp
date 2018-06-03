#include "Disk.h"

Disk::Disk()
{
  hallIndex = 0;//初始化

  photoIndex = 0;

  lastHallPoint = 0;

  lastPhotoPoint = 0;

  stable = false;
}

void Disk::updateHallBuffer(unsigned long timePoint)
{
  hallIndex = (hallIndex + 1) % HALLBUFFER_SIZE;//取余，在循环链表和循环队列中，用于判断节点的位置
  
//  unsigned long timeInterval = timePoint - lastHallPoint;
  
//  lastHallPoint = timePoint;
  
  hallBuffer[hallIndex] = timePoint;
}

void Disk::updatePhotoBuffer(unsigned long timePoint)
{
  unsigned long lastInterval = photoBuffer[photoIndex];//更新时间点
  
  photoIndex = (photoIndex + 1) % PHOTOBUFFER_SIZE;//更新完后指针往下移
  
  unsigned long timeInterval = timePoint - lastPhotoPoint;//就算时间间隔
  
  lastPhotoPoint = timePoint;//更新上一点时间，用于下一次循环计算
  
  photoBuffer[photoIndex] = timeInterval;//将时间间隔存入数列中

  if (abs(timeInterval - lastInterval) > lastInterval * 0.03)//如果两次的时间间隔差值超过百分之三，则输出错误
    stable = false;
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
