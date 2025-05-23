#ifndef motionsensor_h
#define motionsensor_h

#include <Arduino.h>

class MotionSensor {
  
  private: 
    byte pin;
    byte state;
  
  public: 
    MotionSensor(byte pin);
    void init();
    void update();
    byte getState();


};

#endif