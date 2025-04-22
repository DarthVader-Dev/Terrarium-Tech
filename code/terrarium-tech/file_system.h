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
    void listSdFiles(File dir, int numTabs);
    void writeJsonLogData(float temp, float humidity, float uvIndex, String timeS);
    String readAndCleanJsonFile();
    static void fDateTime(uint16_t* date, uint16_t* time);
};

#endif