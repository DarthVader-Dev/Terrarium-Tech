#include "thsensor.h"


bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_SHT31 sht31 = Adafruit_SHT31();
bool THSENSORSETUPCOMPLETE = false;


THSensor::THSensor(){ //(byte pin) {
  //this->pin = pin;
  
  
  init();
}
void THSensor::init() {

   
}

void THSensor::beginSetup(){
   Serial.begin(9600);

  // while (!Serial)
  //   delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  Serial.print("Heater Enabled State: ");
  if (sht31.isHeaterEnabled())
    Serial.println("ENABLED");
  else
    Serial.println("DISABLED");
  //pinMode(pin, INPUT);
  //update();
}

void THSensor::readData(){

if(!THSENSORSETUPCOMPLETE){
beginSetup();
THSENSORSETUPCOMPLETE = true;
}



    float t = sht31.readTemperature();
  float h = sht31.readHumidity();

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

  // Toggle heater enabled state every 30 seconds
  // An ~3.0 degC temperature increase can be noted when heater is enabled
  if (loopCnt >= 30) {
    enableHeater = !enableHeater;
    sht31.heater(enableHeater);
    Serial.print("Heater Enabled State: ");
    if (sht31.isHeaterEnabled())
      Serial.println("ENABLED");
    else
      Serial.println("DISABLED");

    loopCnt = 0;
  }
  loopCnt++;
}

void THSensor::update() {
   
} 
byte THSensor::getState() {
  update();
  return state;
}
