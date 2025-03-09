// #include "wifi.h"
// #include "file_system.h"
#include "include_files.h"

WIFI wifiServer;
//FILESYSTEM fileSystem;

void setup(){
  wifiServer.beginSetup();
  //fileSystem.beginSetup();

}

void loop(){
  //wifiServer.printWifiStatus();
 wifiServer.showWebPage();
 //fileSystem.readData();
}