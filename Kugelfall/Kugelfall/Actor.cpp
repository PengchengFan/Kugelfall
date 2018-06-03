#include "Actor.h"

Actor::Actor(int pin) 
{
  pinMode(pin, OUTPUT);
  
  _pin = pin;
}

void Actor::setValue(boolean value) 
{
  digitalWrite(_pin, value);
}

