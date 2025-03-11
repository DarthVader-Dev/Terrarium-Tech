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
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    LOGGERSETUPCOMPLETE = true;
  }
  
  //if(!TIMESHOWN){
  DateTime time = rtc.now();
   //Serial.println(time.timestamp());
  Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));
  //}
  
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
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //DateTime now = rtc.now() + TimeSpan(0,-12,0,0);
  //Serial.println(Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+now.timestamp(DateTime::TIMESTAMP_FULL)));
  //rtc.adjust(now);
  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

// void LOGGER::update() {
// }
// byte LOGGER::getState() {
//   update();
//   return state;
// }