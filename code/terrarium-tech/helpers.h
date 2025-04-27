#ifndef helpers_h
#define helpers_h


#include <Arduino.h>

class HELPERS {


  private: 
    byte pin;
    //byte state;

    
  public: 
    
    HELPERS();
    static void tcaselect(uint8_t i);
    void beginSetup();    
    //static void fDateTime(uint16_t* date, uint16_t* time);
    //  void log();
    //  void init();

    //  void log(String dataId, String dataItem);
};

#endif