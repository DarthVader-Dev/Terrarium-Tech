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
    // void update();
    // byte getState();    
    
    // void writeData(char d[]);
    // void readData();
    // String getWebPage();
    // String readFileToString(const char *filename);

};

#endif