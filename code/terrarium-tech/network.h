#ifndef network_h
#define network_h

#include <Arduino.h>
#include <WiFiNINA.h>

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
    void sendFile(WiFiClient& client, const char* path, const char* contentType);
    void sendFile(WiFiClient& client, String path, const char* contentType);
    void sendJsonFile(WiFiClient& client, const char* path, const char* contentType);
    void send404(WiFiClient& client);
    void sendNoFavicon(WiFiClient& client);
    String getImagePath(String req);
};

#endif