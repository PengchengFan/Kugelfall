#include "Sensor.h"

Sensor::Sensor(int pin) 
{
  pinMode(pin, INPUT);
  
  _pin = pin;
  
  _status = getValue();
}

int Sensor::getValue() 
{
  return digitalRead(_pin);
}

boolean Sensor::isFalling() 
{
  if (_status == 1 && getValue() == 0) 
  {
    _status = getValue();
    
    return true;
  }
  _status = getValue();
  
  return false;
}

boolean Sensor::isRising() 
{
  if (_status == 0 && getValue() == 1) 
  {
    _status = getValue();
    
    return true;
  }
  _status = getValue();
  
  return false;
}

boolean Sensor::isChanging() 
{
  if (_status == 1 && getValue() == 0) 
  {
    _status = getValue();
    
    return true;
  }
  _status = getValue();
  
  return false;
}
