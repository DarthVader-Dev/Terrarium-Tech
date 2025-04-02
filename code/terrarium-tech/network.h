#ifndef network_h
#define network_h

#include <Arduino.h>

class NETWORK {


  private: 
    byte pin;
    byte state;

    
  public: 

    NETWORK();
    void init();
    void update();
    byte getState();
    void printWifiStatus();
    void showWebPage();
    void beginSetup();
    void writeData(char d[]);

};

#endif