#include "Servomotor.h"

Servomotor::Servomotor(int pin) 
{
  _pin = pin;
  write(START_POS);
}

void Servomotor::rotate() 
{
  attach(_pin);
  
  write(END_POS);
  
  delay(100);
  
  write(START_POS);
  
  detach();
}
