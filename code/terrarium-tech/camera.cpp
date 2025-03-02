#include "camera.h"


Camera::Camera(byte pin) {
  this->pin = pin;
  //lastReading = LOW;
  
  init();
}
void Camera::init() {
  pinMode(pin, INPUT);
  update();
}

void Camera::update() {
    
}
byte Camera::getState() {
  update();
  return state;
}
