#ifndef Actor_h
#define Actor_h

#include "Arduino.h"

class Actor 
{
  public:
    Actor(int pin);
    
    void setValue(boolean value);

  private:
    int _pin;
};

#endif
