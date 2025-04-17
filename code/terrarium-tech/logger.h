#ifndef logger_h
#define logger_h

#include <RTClib.h>
#include <Arduino.h>

class LOGGER {


  private: 
    byte pin;
    byte state;

    
  public: 
    
    LOGGER();
     void log();
     void init();
     void beginSetup();
     void log(String type,String logFile , String dataItem);
     DateTime getCurrentDateTime();     
     void logSensorData();
};

#endif