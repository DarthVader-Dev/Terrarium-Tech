#include "thsensor.h"
#include "include_files.h"

bool enableHeater = false;
uint8_t loopCnt = 0;
//HELPERS tempHelper;
extern HELPERS helpers;
bool THSENSORSETUPCOMPLETE = false;
LOGGER templogger = LOGGER();
int TEMPDIGITPIN = 5;
Adafruit_HTU21DF HTU21 = Adafruit_HTU21DF();
THSensor::THSensor(){ 

  
  
  init();
}
void THSensor::init() {

   
}

void THSensor::beginSetup(){

  helpers.tcaselect(TEMPDIGITPIN);
 
    if (! HTU21.begin()) {
    Serial.println("Couldn't find HTU21");
    while (1) delay(1);
  }

}

void THSensor::readData(){

if(!THSENSORSETUPCOMPLETE){
beginSetup();
THSENSORSETUPCOMPLETE = true;
}


helpers.tcaselect(TEMPDIGITPIN);
    float t = HTU21.readTemperature();
  float h = HTU21.readHumidity();

  if (! isnan(t)) { 
    Serial.print("Temp *F = "); Serial.print((t * 1.8) + 32); Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {
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

  helpers.tcaselect(TEMPDIGITPIN);
  float t = HTU21.readTemperature();
  float h = HTU21.readHumidity();  

  String d = "\"temp\":" + String(t) + ",\"humidity\":" + String(h);

  templogger.log("ENV","THLOG.JS", d);
}

String THSensor::getJsonValue(){
  if(!THSENSORSETUPCOMPLETE){
beginSetup();
  THSENSORSETUPCOMPLETE = true;
}

  helpers.tcaselect(TEMPDIGITPIN);
  float t = HTU21.readTemperature();
  float h = HTU21.readHumidity();  

  String result = "\"temp\":" + String(t) + ",\"humidity\":" + String(h);
  return result;
}

float THSensor::getHumid(){
if(!THSENSORSETUPCOMPLETE){
  beginSetup();
  THSENSORSETUPCOMPLETE = true;
}
  helpers.tcaselect(TEMPDIGITPIN);

  float results = HTU21.readHumidity();

  return results;
}

float THSensor::getTemp(){
if(!THSENSORSETUPCOMPLETE){
  beginSetup();
  THSENSORSETUPCOMPLETE = true;
}
  helpers.tcaselect(TEMPDIGITPIN);

  float results = HTU21.readTemperature();

  return results;
}

void THSensor::update() {
   
} 
byte THSensor::getState() {
  update();
  return state;
}
