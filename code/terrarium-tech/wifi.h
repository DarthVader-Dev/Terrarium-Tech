#ifndef wifi_h
#define wifi_h

#include <Arduino.h>

class WIFI {


  private: 
    byte pin;
    byte state;

    
  public: 
    //WIFI(byte pin);
    WIFI();
    void init();
    void update();
    byte getState();
    void printWifiStatus();
    void showWebPage();
    void beginSetup();
    void writeData(char d[]);

};

#endif