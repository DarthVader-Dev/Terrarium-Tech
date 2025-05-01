#include "logger.h"
#include "include_files.h"
#include <RTClib.h>
#include <string>

RTC_DS3231 rtc;
// FILESYSTEM fileSystem;
extern FILESYSTEM fSystem;
//HELPERS logHelper;
extern HELPERS helpers;

bool LOGGERSETUPCOMPLETE;

int LOGDIGITPIN = 2;
int MAX_LOG_ENTRIES = 250;
THSensor thSensor;
UVBSensor uvbSensor;


LOGGER::LOGGER() {

          init();
}

void LOGGER::log() {

  if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;

   Serial.println("Logging Data");

  }
  
  DateTime time = rtc.now();

}
void LOGGER::log(String type,String logFile , String dataItem) {

  if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;
  }

    helpers.tcaselect(LOGDIGITPIN);

  DateTime time = rtc.now();

    String logItem = "{\"timestamp\":\"" + String(time.timestamp(DateTime::TIMESTAMP_FULL)) + "\"," + dataItem + "},]";

    fSystem.writeLogData(type,logFile, logItem);
}

void LOGGER::init(){
  
}

void LOGGER::beginSetup() {

helpers.tcaselect(LOGDIGITPIN);
// if (!rtc.begin()) {
//     Serial.println("Couldn't find RTC");
//     Serial.flush();
//     while (1) delay(10);
//   }

//   if (! rtc.lostPower()) {

//     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   }
}

void LOGGER::logSensorData(){
    String data = thSensor.getJsonValue() + "," + uvbSensor.getJsonValue(); 

  log("ENV", "LOG.JS", data);
}

void LOGGER::logJsonData(){
    if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;

  }
    float temp = thSensor.getTemp();
    // Serial.print(temp); 
    // Serial.print(" - ");
    float humid = thSensor.getHumid();
    // Serial.println(humid); 
    // Serial.print(" - ");
    float uvIndex = uvbSensor.getUvIndex();
  //  Serial.println(uvIndex); 
  //  Serial.print(" - ");

  fSystem.writeJsonLogData(temp,humid, uvIndex);//,getCurrentDateTime());
}

String LOGGER::getCurrentDateTime() {

      if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;

   Serial.println("Logging Data");

  }

  helpers.tcaselect(LOGDIGITPIN);

  DateTime time = rtc.now();
  return time.timestamp(DateTime::TIMESTAMP_FULL);  
}


DateTime LOGGER::getFileDateTime() {

     if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;

   Serial.println("Logging Data");

  }

  helpers.tcaselect(LOGDIGITPIN);

  DateTime time = rtc.now();

  return time;
}

void LOGGER::logErr(String error){
    if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;
  }
  fSystem.writeError(error);
}


