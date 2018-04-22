#include "Servomotor.h"

Servomotor::Servomotor(int pin) {
  _pin = pin;
}

void Servomotor::rotate() {
  attach(_pin);
  write(25);
  delay(150);
  write(-3);
  delay(150);
  detach();
}
