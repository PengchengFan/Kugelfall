#ifndef Servomotor_h
#define Servomotor_h

#include "Arduino.h"
#include "Servo.h"
#include "Actor.h"

#define START_POS 0
#define END_POS 23
#define SERVO_DELAY 160

class Servomotor: public Servo, public Actor
{
  public:
    Servomotor(int pin);
    
    void rotate();
    
  private:
    int _pin;
};

#endif
