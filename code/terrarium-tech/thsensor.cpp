#include "thsensor.h"


ThSensor::ThSensor(byte pin) {
  this->pin = pin;
  
  
  init();
}
void ThSensor::init() {
  pinMode(pin, INPUT);
  update();
}

void ThSensor::update() {
   
} 
byte ThSensor::getState() {
  update();
  return state;
}
