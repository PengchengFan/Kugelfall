#ifndef Servomotor_h
#define Servomotor_h

#include "Arduino.h"
#include "Servo.h"
#include "Actor.h"

#define START_POS 0
#define END_POS 20

class Servomotor: public Servo, public Actor
{
  public:
    Servomotor(int pin);
    
    void rotate();
    
  private:
    int _pin;
};

#endif
