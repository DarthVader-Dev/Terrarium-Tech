#include "wifi.h"



WIFI::WIFI(byte pin) {
  this->pin = pin;
  
  
  init();
}
void WIFI::init() {
  pinMode(pin, INPUT);
  update();
}

void WIFI::update() {
    
}
byte WIFI::getState() {
  update();
  return state;
}
