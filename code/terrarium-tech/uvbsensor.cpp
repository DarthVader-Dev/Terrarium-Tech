#include "uvbsensor.h"
#include "include_files.h"


HELPERS uvbHelper;
//Adafruit_SHT31 sht31 = Adafruit_SHT31();
bool UVBSENSORSETUPCOMPLETE = false;
LOGGER uvblogger = LOGGER();
int const UV_SENSOR_PIN = A0;

UVBSensor::UVBSensor(){ //(byte pin) {
  //this->pin = pin;
  
  
  init();
}
void UVBSensor::init() {

   
}

void UVBSensor::beginSetup(){
  Serial.begin(9600);
  // tempHelper.tcaselect(TEMPDIGITPIN);
 while (!Serial)
  delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  // Serial.println("HTU21 test");
  // //if (! HTU21.begin(0x44)) {   
  //   if (! HTU21.begin()) {// Set to 0x45 for alternate i2c addr
  //   Serial.println("Couldn't find HTU21");
  //   while (1) delay(1);
  // }

  // Serial.print("Heater Enabled State: ");
  // if (HTU21.isHeaterEnabled())
  //   Serial.println("ENABLED");
  // else
  //   Serial.println("DISABLED");
  // //pinMode(pin, INPUT);
  // //update();
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
// tempHelper.tcaselect(TEMPDIGITPIN);
//     float t = HTU21.readTemperature();
//   float h = HTU21.readHumidity();

//   if (! isnan(t)) {  // check if 'is not a number'
//     Serial.print("Temp *F = "); Serial.print((t * 1.8) + 32); Serial.print("\t\t");
//   } else { 
//     Serial.println("Failed to read temperature");
//   }
  
//   if (! isnan(h)) {  // check if 'is not a number'
//     Serial.print("Hum. % = "); Serial.println(h);
//   } else { 
//     Serial.println("Failed to read humidity");
//   }

//   delay(1000);
}

void UVBSensor::LogData(){
if(!UVBSENSORSETUPCOMPLETE){
beginSetup();
  UVBSENSORSETUPCOMPLETE = true;
}
 int sensor_value = analogRead(UV_SENSOR_PIN);
  float volts = sensor_value * 5.0 / 1024.0;
  //Serial.print("Sensor Voltage Output: ");
  //Serial.println(sensor_value);

  // tempHelper.tcaselect(TEMPDIGITPIN);
  // float t = HTU21.readTemperature();
  // float h = HTU21.readHumidity();  

  String d = "\"uvIndex\":" + String(sensor_value);
  // // logger.log("Temperature",String(t));
  // // logger.log("Humidity", String(h));
  // Serial.println("LogData" + d);
  uvblogger.log("ENV","UVLOG.JS" ,d);
}

void UVBSensor::update() {
   
} 
byte UVBSensor::getState() {
  update();
  return state;
}
