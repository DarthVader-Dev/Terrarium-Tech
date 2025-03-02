#ifndef thsensor_h
#define thsensor_h

#include <Arduino.h>

class ThSensor {

  private: 
    byte pin;
    byte state;

  public: 
    ThSensor(byte pin);
    void init();
    void update();
    byte getState();


};

#endif