#ifndef camera_h
#define camera_h

#include <Arduino.h>


class Camera {
  private: 
    byte pin;
    byte state;

  public: 
    Camera(byte pin);
    void init();
    void update();
    byte getState();

};

#endif