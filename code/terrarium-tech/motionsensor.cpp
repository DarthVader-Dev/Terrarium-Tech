#include "motionsensor.h"


MotionSensor::MotionSensor(byte pin) {
  this->pin = pin;
  
  
  init();
}
void MotionSensor::init() {
  pinMode(pin, INPUT);
  update();
}

void MotionSensor::update() {
   
}
byte MotionSensor::getState() {
  update();
  return state;
}
