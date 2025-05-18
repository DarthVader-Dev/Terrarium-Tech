#include "helpers.h"
#include <Wire.h>

#define TCAADDR 0x70

bool HELPERSSETUPCOMPLETE;
//RTC_DS3231 rtcHelp;
//int RTCDIGITPIN = 2;

HELPERS::HELPERS() {
  //init();
  
}
// void HELPERS::init() {
// }

void HELPERS::beginSetup() {
 
    //if(!Serial){
      Wire.begin();
      //Serial.begin(9600);
   // }


    
    //Serial.println("Initializing WIRE...");
}

void HELPERS::tcaselect(uint8_t i) {
 // Serial.println("tcaselect"); Serial.print(i);
  // if(!HELPERSSETUPCOMPLETE){
  //   beginSetup();
  //   HELPERSSETUPCOMPLETE = true;
  // }
if(HELPERSSETUPCOMPLETE){
      Wire.begin();
      HELPERSSETUPCOMPLETE = true;
}
  String message = "Changing Address to: " + String(i);
  Serial.println(message);
  //Serial.println( i);
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
  Serial.println("Wire Transferred");
}

// void HELPERS::fDateTime(uint16_t* date, uint16_t* time) {
//   // Read current date and time from RTC
// logHelper.tcaselect(LOGDIGITPIN);
// if (!rtcHelp.begin()) {
//     Serial.println("Couldn't find RTC");
//     Serial.flush();
//     while (1) delay(10);
//   }

//   if (! rtc.lostPower()) {
//     //Serial.println("RTC is NOT running, let's set the time!");
//     rtcHelp.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   }


//  HELPERS::tcaselect(RTCDIGITPIN);
//   DateTime now = fLogHelper.getFileDateTime();
//   *date = FAT_DATE(now.year(), now.month(), now.day());
//   *time = FAT_TIME(now.hour(), now.minute(), now.second());
// }
