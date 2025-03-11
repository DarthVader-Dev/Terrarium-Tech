// #include "wifi.h"
// #include "file_system.h"
#include "include_files.h"


WIFI wifiServer;
LOGGER logger;
//FILESYSTEM fileSystem;

void setup(){
  wifiServer.beginSetup();
  //fileSystem.beginSetup();
  //logger.beginSetup();
  //logger.log();
  //wifiServer.showWebPage();
}

void loop(){
  //wifiServer.printWifiStatus();
 wifiServer.showWebPage();
 logger.log();
 //fileSystem.readData();
 delay(1000);
}