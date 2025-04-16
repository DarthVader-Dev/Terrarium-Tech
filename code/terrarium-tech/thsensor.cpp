#include "thsensor.h"
#include "include_files.h"

bool enableHeater = false;
uint8_t loopCnt = 0;
HELPERS tempHelper;
//Adafruit_SHT31 sht31 = Adafruit_SHT31();
bool THSENSORSETUPCOMPLETE = false;
LOGGER templogger = LOGGER();
int TEMPDIGITPIN = 2;
Adafruit_HTU21DF HTU21 = Adafruit_HTU21DF();
THSensor::THSensor(){ //(byte pin) {
  //this->pin = pin;
  
  
  init();
}
void THSensor::init() {

   
}

void THSensor::beginSetup(){
  Serial.begin(9600);
  tempHelper.tcaselect(TEMPDIGITPIN);
  // while (!Serial)
  //   delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("HTU21 test");
  //if (! HTU21.begin(0x44)) {   
    if (! HTU21.begin()) {// Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find HTU21");
    while (1) delay(1);
  }

  // Serial.print("Heater Enabled State: ");
  // if (HTU21.isHeaterEnabled())
  //   Serial.println("ENABLED");
  // else
  //   Serial.println("DISABLED");
  // //pinMode(pin, INPUT);
  // //update();
}

void THSensor::readData(){

if(!THSENSORSETUPCOMPLETE){
beginSetup();
THSENSORSETUPCOMPLETE = true;
}


tempHelper.tcaselect(TEMPDIGITPIN);
    float t = HTU21.readTemperature();
  float h = HTU21.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *F = "); Serial.print((t * 1.8) + 32); Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }

  delay(1000);
}

void THSensor::LogData(){
if(!THSENSORSETUPCOMPLETE){
beginSetup();
  THSENSORSETUPCOMPLETE = true;
}

  tempHelper.tcaselect(TEMPDIGITPIN);
  float t = HTU21.readTemperature();
  float h = HTU21.readHumidity();  

  String d = "\"temp\":" + String(t) + ",\"humidity\":" + String(h);
  // logger.log("Temperature",String(t));
  // logger.log("Humidity", String(h));
  //Serial.println("LogData" + d);
  templogger.log("ENV","THLOG.JS", d);
}

void THSensor::update() {
   
} 
byte THSensor::getState() {
  update();
  return state;
}
