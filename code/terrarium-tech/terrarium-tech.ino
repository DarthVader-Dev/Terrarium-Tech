#include "include_files.h"
#include <Wire.h>

NETWORK wifiServer;
HELPERS helpers;
//LOGGER logger;
THSensor thSensor;

int LOGINTERVAL = 0;

void setup(){
  helpers.beginSetup();
}

void loop(){

  wifiServer.showWebPage();
  //helpers.tcaselect(2);
  
  

  delay(1000);



  if(LOGINTERVAL == 5){
    thSensor.readData();  
    thSensor.LogData();
    LOGINTERVAL = 0;
  }
LOGINTERVAL++;

}
