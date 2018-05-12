#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "Sensor.h"
#include "Servomotor.h"

#define PHOTOBUFFER_SIZE 6
#define HALLBUFFER_SIZE 2
#define DELAY 200

/*
 * the job of controller is:
 * 1. to compute the time for releasing a ball
 * 2. to decide if the rotation is stable
 * 3. to release a ball
 */
class Controller
{
  public:
    // constructor of controller
    Controller(Servomotor *servo);

    // count of the times that trigger is pulled
    int triggerCount;

    // start of the time interval for releasing a ball
    unsigned long releaseTimeStart;

    // end of the time interval for releaseing a ball
    unsigned long releaseTimeEnd;

    // store new data in hall sensor buffer
    void updateHallBuffer(unsigned long timePoint);

    // store new data in photo sensor buffer
    void updatePhotoBuffer(unsigned long timePoint);

    void printPhotoBuffer();

    // if trigger is pulled, increase the count for one
    void increaseTriggerCount();

    // if ball is released, decrese the count for one. And return if the count == 0
    boolean decreaseTriggerCount();

    // to calculate if the rotation is stable
    boolean isStable();

    // compute the next time interval for releasing a ball
    void updateReleaseTime();

    // control servo to rotate, to release a ball
    void releaseBall();

    // in every round the buffer flag will be reset for once
    void resetBufferFlag();

  private:
    // hall sensor buffer flag
     int hallFlag;

    // photo sensor buffer flag
    int photoFlag;
    
    // store the last time point of hall sensor buffer being updated
//    unsigned long lastHallPoint;

    // store the lastest time point of falling flank of photo sensor
    // also as the start point for computing the releasing time
    unsigned long lastPhotoPoint;

    // 
    unsigned long predictedPhotoPoint;

    // pointer of servo
    Servomotor *_servo;

    // buffer for the time interval between two photo sensor value changes
    unsigned long photoBuffer[PHOTOBUFFER_SIZE];

    // buffer for the time interval between two hall sensor value changes
    unsigned long hallBuffer[HALLBUFFER_SIZE];

    unsigned long computeBias();
};

#endif
