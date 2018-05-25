#ifndef Disk_h
#define Disk_h

#include "Arduino.h"

#define PHOTOBUFFER_SIZE 6
#define HALLBUFFER_SIZE 2

class Disk 
{
  public:
    Disk();

    // store new data in hall sensor buffer
    boolean updateHallBuffer(unsigned long timePoint, int hallValue);

    // store new data in photo sensor buffer
    void updatePhotoBuffer(unsigned long timePoint);

    // in every round the buffer flag will be reset for once
    void resetBufferFlag();

    // to calculate if the rotation is stable
    boolean isStable();

    // buffer for the time interval between two photo sensor value changes
    int photoBuffer[PHOTOBUFFER_SIZE];

    // buffer for the time interval between two hall sensor value changes
    unsigned long hallBuffer[HALLBUFFER_SIZE][HALLBUFFER_SIZE];
    
    // to represent if the disk is stable
    boolean stable;

  private:

    /*
     * hallIndex and photoIndex represent the model state
     */
    int hallIndex;

    int photoIndex;

    // store the last time point of hall sensor buffer being updated
    unsigned long lastHallPoint;

    // store the lastest time point of rising flank of photo sensor
    // also as the start point for computing the releasing time
    unsigned long lastPhotoPoint;
};

#endif
