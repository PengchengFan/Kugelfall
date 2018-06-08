#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "Sensor.h"
#include "Disk.h"
#include "Servomotor.h"

#define TRIGGERDELAY 200
#define DELAY 480
#define MIN_INTERVAL 55
#define MAX_INTERVAL 833

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
    Controller(Servomotor *servo, Disk *disk);

    // start of the legal time interval for releasing a ball
    unsigned long releaseTimeStart;

    // end of the legal time interval for releaseing a ball
    unsigned long releaseTimeEnd;

    // count of the times that trigger is pulled
    int triggerCount;

    // if trigger is pulled, increase the count for one
    void increaseTriggerCount();

    // if ball is released, decrese the count for one. And return false if the count == 0
    boolean decreaseTriggerCount();

    // compute the legal time interval for releasing a ball
    void updateReleaseTime();

    // control servo to rotate, to release a ball
    void releaseBall();

  private:
    // disk model, to represent model status
    Disk *_disk;

    // a pointer to servo instance, used for servo control
    Servomotor *_servo;

    // under different speed, different bias will be computed.
    int computeBias();
};

#endif
