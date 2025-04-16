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
Serial.begin(9600);
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

DateTime LOGGER::getCurrentDateTime(){
  return rtc.now();
}