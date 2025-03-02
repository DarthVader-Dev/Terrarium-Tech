#ifndef camera_h
#define camera_h

#include <Arduino.h>


class Camera {
  private: byte pin;
  public: 
    camera(byte pin);
    void init();
    


};

#endif