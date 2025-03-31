#include "logger.h"
#include "file_system.h"
#include "RTClib.h"

RTC_DS1307 rtc;

bool LOGGERSETUPCOMPLETE;

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
  Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));
  
}

void LOGGER::log(String dataId, String dataItem) {

  if(!LOGGERSETUPCOMPLETE){
    beginSetup();
    LOGGERSETUPCOMPLETE = true;
    Serial.print(dataId + " " + dataItem);
   Serial.println("Logging Data");

  }
  
  DateTime time = rtc.now();
  Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));
  
}

void LOGGER::init(){
  
}

void LOGGER::beginSetup() {
if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
