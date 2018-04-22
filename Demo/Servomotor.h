#ifndef Servomotor_h
#define Servomotor_h

#include "Arduino.h"
#include "Servo.h"

class Servomotor: public Servo {
  public:
    Servomotor(int pin);
    void rotate();
  private:
    int _pin;
};

#endif
