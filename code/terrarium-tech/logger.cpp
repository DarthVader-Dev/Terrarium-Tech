#include "logger.h"
//#include "file_system.h"
#include "include_files.h"
#include "RTClib.h"
#include <string>

FILESYSTEM fileSystem;

bool LOGGERSETUPCOMPLETE;
HELPERS logHelper;
int LOGDIGITPIN = 5;
RTC_DS3231 rtc;

LOGGER::LOGGER() {

          init();
}

void LOGGER::log() {

  if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;

   Serial.println("Logging Data");

  }
  
  //DateTime time = rtc.now();

  
  fileSystem.writeLogData("testing", "data");
  //Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));
  
}

void LOGGER::log(String dataId, String dataItem) {

  if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;
  }

    logHelper.tcaselect(LOGDIGITPIN);
    //Serial.print(dataId + " " + dataItem);
    fileSystem.writeLogData(dataId, dataItem);
    //Serial.println("Logging Data");
  //DateTime time = rtc.now();
  //Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));
  
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
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
