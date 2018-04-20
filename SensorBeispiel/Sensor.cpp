#include "Sensor.h"

Sensor::Sensor(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

int Sensor::getValue() {
  return digitalRead(_pin);
}
