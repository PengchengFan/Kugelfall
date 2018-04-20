#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor {
  public:
    Sensor(int pin);
    int getValue();

  private:
    int _pin;
};

#endif
