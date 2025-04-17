#ifndef uvbsensor_h
#define uvbsensor_h

#include <Arduino.h>

class UVBSensor {

  private: 
    byte pin;
    byte state;

  public: 
    //ThSensor(byte pin);
    UVBSensor();
    void init();
    void update();
    byte getState();
    void readData();
    void beginSetup();
    void LogData();
    String getJsonValue();

};

#endif