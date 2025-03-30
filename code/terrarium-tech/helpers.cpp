#include "helpers.h"
#include <Wire.h>

#define TCAADDR 0x70

bool HELPERSSETUPCOMPLETE;

HELPERS::HELPERS() {
  //init();
  
}
// void HELPERS::init() {
// }

void HELPERS::beginSetup() {
  
    if(!Serial){
      Wire.begin();
      Serial.begin(9600);
    }

    
    Serial.print("Initializing WIRE...");
}

void HELPERS::tcaselect(uint8_t i) {
  if(!HELPERSSETUPCOMPLETE){
    beginSetup();
    HELPERSSETUPCOMPLETE = true;
  }
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}