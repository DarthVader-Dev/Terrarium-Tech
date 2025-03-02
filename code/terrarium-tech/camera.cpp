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
    // You can handle the debounce of the button directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    // byte newReading = digitalRead(pin);
    
    // if (newReading != lastReading) {
    //   lastDebounceTime = millis();
    // }
    // if (millis() - lastDebounceTime > debounceDelay) {
    //   // Update the 'state' attribute only if debounce is checked
    //   state = newReading;
    // }
    // lastReading = newReading;
}
byte Camera::getState() {
  update();
  return state;
}
// bool Camera::isPressed() {
//   return (getState() == HIGH);
// }