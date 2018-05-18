#include "Servomotor.h"

Servomotor::Servomotor(int pin)
: Actor(pin)
{
  _pin = pin;
  write(START_POS);
  attach(pin);
}

void Servomotor::rotate() 
{
//  attach(_pin);
  
  write(END_POS);
  
  delay(100);
  
  write(START_POS);

//  delay(150);
  
//  detach();
}
