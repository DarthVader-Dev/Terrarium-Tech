#ifndef file_system_h
#define file_system_h

#include <Arduino.h>

class FILESYSTEM {


  private: 
    byte pin;
    byte state;

    
  public: 
    
    FILESYSTEM();
    void init();
    void update();
    byte getState();    
    void beginSetup();
    void writeLogData(String fileName,String information);
    void readData();
    String getWebPage();
    String readFileToString(const char *filename);

};

#endif