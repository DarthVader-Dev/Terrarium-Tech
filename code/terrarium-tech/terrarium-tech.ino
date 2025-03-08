#include "wifi.h"

WIFI wifiServer;

void setup(){
  wifiServer.beginSetup();
}

void loop(){
  //wifiServer.printWifiStatus();   
 wifiServer.showWebPage();
}