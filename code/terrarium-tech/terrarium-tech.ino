#include "include_files.h"

WIFI wifiServer;
HELPERS helpers;
LOGGER logger;
THSensor thSensor;

int LOGINTERVAL = 0;

#define TCAADDR 0x70

void setup(){
// while (!Serial);
//     delay(1000);

    //Wire.begin();
    
     //Serial.begin(9600);
//     Serial.println("\nTCAScanner ready!");
    
//     for (uint8_t t=0; t<8; t++) {
//       tcaselect(t);
//       Serial.print("TCA Port #"); Serial.println(t);

//       for (uint8_t addr = 0; addr<=127; addr++) {
//         if (addr == TCAADDR) continue;

//         Wire.beginTransmission(addr);
//         if (!Wire.endTransmission()) {
//           Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
//         }
//       }
//     }
//     Serial.println("\ndone");
}

void loop(){

  wifiServer.showWebPage();
  helpers.tcaselect(2);
  thSensor.readData();

 delay(1000);

// if(LOGINTERVAL <= 10){
//   LOGINTERVAL++;
  
// }else{
  helpers.tcaselect(5);
  logger.log();
//   LOGINTERVAL = 0;
// }


}


// void tcaselect(uint8_t i) {
//   if (i > 7) return;
 
//   Wire.beginTransmission(TCAADDR);
//   Wire.write(1 << i);
//   Wire.endTransmission();  
// }
