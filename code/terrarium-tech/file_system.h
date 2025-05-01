#ifndef file_system_h
#define file_system_h
#include <SD.h>


#include <Arduino.h>

class FILESYSTEM {
    
  public: 
    
    FILESYSTEM(uint8_t csPin); 
    bool begin();
    bool isInitialized();
    void writeLogData(String type,String logFile, String dataItem);
    File getImageFileToSaveTo(String fileName);
    void readData();
    String getWebPage();   
    File getHomePageFile();   
    File open(const char* path, uint8_t mode);        
    String readFileToString(String filename);
    void enumerateLines(File file, int pos);
    String getLogFile(String fileName);
    void printDirectory(File dir, int numTabs);
    void printAllFiles();
    void listSdFiles(File dir, int numTabs);
    void writeJsonLogData(float temp, float humidity, float uvIndex);//, String dte);
    String readAndCleanJsonFile();
    static void fDateTime(uint16_t* date, uint16_t* time);
    void writeError(String error);
    
    private:
      uint8_t _csPin;
      bool _initialized;
    
};

#endif