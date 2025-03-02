#ifndef wifi_h
#define wifi_h

#include <Arduino.h>

class WIFI {


  private: 
    byte pin;
    byte state;

    
  public: 
    WIFI(byte pin);
    void init();
    void update();
    byte getState();


};

#endif