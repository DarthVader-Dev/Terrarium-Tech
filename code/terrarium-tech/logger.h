#ifndef logger_h
#define logger_h


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
};

#endif