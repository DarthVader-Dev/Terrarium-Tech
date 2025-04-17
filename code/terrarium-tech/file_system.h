#ifndef file_system_h
#define file_system_h
#include <SD.h>

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
    void writeLogData(String type,String logFile, String dataItem);
    //bool savePhoto(String filename, uint32_t jpglen, uint8_t *buffer, uint8_t bytesToRead,Adafruit_VC0706 cam);
    File getImageFileToSaveTo(String fileName);
    void readData();
    String getWebPage();              
    String readFileToString(String filename);
    void enumerateLines(File file, int pos);
    String getLogFile(String fileName);
    void printDirectory(File dir, int numTabs);
    void printAllFiles();
  
};

#endif