#include "logger.h"
//#include "file_system.h"
#include "include_files.h"
#include <RTClib.h>
#include <string>

RTC_DS3231 rtc;
FILESYSTEM fileSystem;

bool LOGGERSETUPCOMPLETE;
HELPERS logHelper;
int LOGDIGITPIN = 5;
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

  
  //fileSystem.writeLogData("testing", "data");
  //Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));
  
}
void LOGGER::log(String type,String logFile , String dataItem) {
//void LOGGER::log(String dataId, String dataItem) {

  if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;
  }

    logHelper.tcaselect(LOGDIGITPIN);
    //Serial.print(dataId + " " + dataItem);

    //Serial.println("Logging Data");
  DateTime time = rtc.now();
  //Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));
    String logItem = "{\"timestamp\":\"" + String(time.timestamp(DateTime::TIMESTAMP_FULL)) + "\"," + dataItem + "},]";
    //Serial.println("Log" + logItem);
    fileSystem.writeLogData(type,logFile, logItem);
}

void LOGGER::init(){
  
}

void LOGGER::beginSetup() {
//Serial.begin(9600);
logHelper.tcaselect(LOGDIGITPIN);
if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.lostPower()) {
    //Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void LOGGER::logSensorData(){
    String data = thSensor.getJsonValue() + "," + uvbSensor.getJsonValue(); 
    //Serial.println(data); 
  log("ENV", "LOG.JS", data);
}

void LOGGER::logJsonData(){
    if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;

   Serial.println("Logging Data");

  }
    //String data = thSensor.getJsonValue() + "," + uvbSensor.getJsonValue(); 
    //Serial.println("logJsonData"); 
    float temp = thSensor.getTemp();
    //Serial.println(temp); 
    float humid = thSensor.getHumid();
    //Serial.println(humid); 
    float uvIndex = uvbSensor.getUvIndex();
   //Serial.println(uvIndex); 
   //DateTime time = getCurrentDateTime();
  //String currentTime = ;
  fileSystem.writeJsonLogData(temp,humid, uvIndex,getCurrentDateTime());
}

String LOGGER::getCurrentDateTime() {

      if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;

   Serial.println("Logging Data");

  }

  logHelper.tcaselect(LOGDIGITPIN);

  DateTime time = rtc.now();

  // Serial.print("DateTime::TIMESTAMP_FULL:\t");
  // Serial.println(time.timestamp(DateTime::TIMESTAMP_FULL));

  // Serial.print("DateTime::TIMESTAMP_DATE:\t");
  // Serial.println(time.timestamp(DateTime::TIMESTAMP_DATE));

  // Serial.print("DateTime::TIMESTAMP_TIME:\t");
  // Serial.println(time.timestamp(DateTime::TIMESTAMP_TIME));

  // Serial.println();

  return time.timestamp(DateTime::TIMESTAMP_FULL);  // Don't call rtc.now() again
}


DateTime LOGGER::getFileDateTime() {

     if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;

   Serial.println("Logging Data");

  }

  logHelper.tcaselect(LOGDIGITPIN);

  DateTime time = rtc.now();

  return time;  // Don't call rtc.now() again
}

