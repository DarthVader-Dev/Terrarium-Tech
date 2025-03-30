#ifndef helpers_h
#define helpers_h


#include <Arduino.h>

class HELPERS {


  private: 
    byte pin;
    //byte state;

    
  public: 
    
    HELPERS();
    void tcaselect(uint8_t i);
    void beginSetup();    
    //  void log();
    //  void init();

    //  void log(String dataId, String dataItem);
};

#endif