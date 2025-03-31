#include "include_files.h"
#include <Wire.h>

WIFI wifiServer;
HELPERS helpers;
LOGGER logger;
THSensor thSensor;

int LOGINTERVAL = 0;

void setup(){
  helpers.beginSetup();
}

void loop(){

  wifiServer.showWebPage();
  helpers.tcaselect(2);
  thSensor.readData();

  delay(1000);

  if(LOGINTERVAL <= 10){
  LOGINTERVAL++;

  }else{
  helpers.tcaselect(5);
  logger.log("Temperature","55");
  LOGINTERVAL = 0;
  }


}
