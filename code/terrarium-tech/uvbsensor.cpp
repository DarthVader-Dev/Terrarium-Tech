#include "uvbsensor.h"
#include "include_files.h"


HELPERS uvbHelper;

bool UVBSENSORSETUPCOMPLETE = false;
LOGGER uvblogger = LOGGER();
int const UV_SENSOR_PIN = A0;

UVBSensor::UVBSensor(){ //(byte pin) {

  
  
  init();
}
void UVBSensor::init() {

   
}

void UVBSensor::beginSetup(){
  delay(10); 
}

String UVBSensor::getJsonValue(){
if(!UVBSENSORSETUPCOMPLETE){
beginSetup();
UVBSENSORSETUPCOMPLETE = true;
}
int sensor_value = analogRead(UV_SENSOR_PIN); // Get raw sensor reading
  float volts = sensor_value * 5.0 / 1024.0;
  String result = "\"uvIndex\":" + String(sensor_value);

  return result;
}

void UVBSensor::readData(){

if(!UVBSENSORSETUPCOMPLETE){
beginSetup();
UVBSENSORSETUPCOMPLETE = true;
}

int sensor_value = analogRead(UV_SENSOR_PIN); // Get raw sensor reading
  float volts = sensor_value * 5.0 / 1024.0;
  Serial.print("Sensor Voltage Output: ");
  Serial.println(sensor_value);

}

void UVBSensor::LogData(){
if(!UVBSENSORSETUPCOMPLETE){
beginSetup();
  UVBSENSORSETUPCOMPLETE = true;
}
 int sensor_value = analogRead(UV_SENSOR_PIN);
  float volts = sensor_value * 5.0 / 1024.0;
  
  String d = "\"uvIndex\":" + String(sensor_value);
  
  uvblogger.log("ENV","UVLOG.JS" ,d);
}

void UVBSensor::update() {
   
} 
byte UVBSensor::getState() {
  update();
  return state;
}

float UVBSensor::getUvIndex(){
  if(!UVBSENSORSETUPCOMPLETE){
beginSetup();
  UVBSENSORSETUPCOMPLETE = true;
}

  int sensor_value = analogRead(UV_SENSOR_PIN); // Get raw sensor reading
  float volts = sensor_value * 5.0 / 1024.0;
  //Serial.println("UV");
  return volts;
  
}
