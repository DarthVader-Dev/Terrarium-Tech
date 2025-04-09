#include "include_files.h"
#include <Wire.h>

NETWORK wifiServer;
HELPERS helpers;
THSensor thSensor;

int LOGINTERVAL = 0;
bool SHOWWEBPAGE = true;

void setup(){
  helpers.beginSetup();
  
}

void loop(){
  wifiServer.showWebPage();
  delay(1000);
  if(LOGINTERVAL == 5){

    thSensor.LogData();
    LOGINTERVAL = 0;
  }
LOGINTERVAL++;

}
