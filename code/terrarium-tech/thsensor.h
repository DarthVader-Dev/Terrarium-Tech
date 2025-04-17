#ifndef thsensor_h
#define thsensor_h

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_HTU21DF.h"

class THSensor {

  private: 
    byte pin;
    byte state;

  public: 
    //ThSensor(byte pin);
    THSensor();
    void init();
    void update();
    byte getState();
    void readData();
    void beginSetup();
    void LogData();
    String getJsonValue();


};

#endif