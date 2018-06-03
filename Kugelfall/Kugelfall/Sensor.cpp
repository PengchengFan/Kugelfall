#include "Sensor.h"

Sensor::Sensor(int pin) 
{
  pinMode(pin, INPUT);//初始化的东西
  
  _pin = pin;
  
  _status = getValue();
}

int Sensor::getValue() //取值
{
  return digitalRead(_pin);
}

boolean Sensor::isFalling() //判断下降沿的，应该只用于按键判断的
{
  if (_status == 1 && getValue() == 0) 
  {
    _status = getValue();
    
    return true;
  }
//  _status = getValue();
  
  return false;
}

boolean Sensor::isRising() //判断上升沿的
{
  if (_status == 0 && getValue() == 1) 
  {
    _status = getValue();
    
    return true;
  }
//  _status = getValue();
  
  return false;
}

boolean Sensor::isChanging() //判断改变值的
{
  if (_status == 1 && getValue() == 0) 
  {
    _status = getValue();
    
    return true;
  }
//  _status = getValue();
  
  return false;
}
