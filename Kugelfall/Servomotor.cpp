#include "Servomotor.h"

Servomotor::Servomotor(int pin)
: Actor(pin)
{
  _pin = pin;
  
  attach(_pin);
  
  write(START_POS);
  
//  detach();
}

void Servomotor::rotate() 
{ 
//  attach(_pin);
  
  write(END_POS);
  
  delay(150);
  
  write(START_POS);

  delay(150);
  
//  detach();
}
