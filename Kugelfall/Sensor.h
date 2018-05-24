#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor 
{
  public:
    Sensor(int pin);
    
    int getValue();
    
    boolean isFalling();
    
    boolean isRising();
    
    boolean isChanging();

  private:  
    int _pin;
    
    boolean _status;
};

#endif
