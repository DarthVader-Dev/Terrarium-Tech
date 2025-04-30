#include "include_files.h"
#include <Wire.h>

// NETWORK wifiServer;
NETWORKR4 wifiServer;
HELPERS helpers;
// THSensor thSensor;
// UVBSensor uvbSensor;
FILESYSTEM fSystem;
LOGGER logger;
bool CAMACTIVE = true;
#define cameraconnection Serial1
Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);
#define chipSelect 10
int numMinutesBetweenPics = 1;
bool CAMSETUP = false;
bool DBG = false;
bool failure;

int LOGINTERVAL = 0;
int CAMERAINTERNVAL = 0;
bool SHOWWEBPAGE = true;
bool LogComplete = false;
bool showFiles = true;
unsigned long start = millis();
#define LED_PIN LED_BUILTIN 

void setup() {

delay(1500);  // Let everything power up
  Serial.begin(9600);

pinMode(10, OUTPUT); 
  pinMode(LED_PIN, OUTPUT);

 setupCam();

//SdFile::dateTimeCallback(fSystem.fDateTime);
helpers.beginSetup();
}
void setupCam(){
  //Delay so all components can power up
delay(2000);
  #if !defined(SOFTWARE_SPI)
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  if(chipSelect != 53) pinMode(53, OUTPUT); // SS on Mega
#else
  if(chipSelect != 10) pinMode(10, OUTPUT); // SS on Uno, etc.
#endif
#endif

  Serial.begin(9600);
  Serial.println("VC0706 Camera test");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }  
  
  // Try to locate the camera
  if (cam.begin()) {
    Serial.println("Camera Found:");
  } else {
    Serial.println("No camera found?");
    return;
  }
  // Print out the camera version information (optional)
  char *reply = cam.getVersion();
  if (reply == 0) {
    Serial.print("Failed to get version");
  } else {
    Serial.println("-----------------");
    Serial.print(reply);
    Serial.println("-----------------");
  }

  // Set the picture size - you can choose one of 640x480, 320x240 or 160x120 
  
  //cam.setImageSize(VC0706_640x480);        // biggest
  cam.setImageSize(VC0706_320x240);        // medium
  //cam.setImageSize(VC0706_160x120);          // small

  // You can read the size back from the camera (optional, but maybe useful?)
  uint8_t imgsize = cam.getImageSize();
  Serial.print("Image size: ");
  if (imgsize == VC0706_640x480) Serial.println("640x480");
  if (imgsize == VC0706_320x240) Serial.println("320x240");
  if (imgsize == VC0706_160x120) Serial.println("160x120");


  //  Motion detection system can alert you when the camera 'sees' motion!
  cam.setMotionDetect(true);           // turn it on
  //cam.setMotionDetect(false);        // turn it off   (default)

  // You can also verify whether motion detection is active!
  Serial.print("Motion detection is ");
  if (cam.getMotionDetect()) 
    Serial.println("ON");
  else 
    Serial.println("OFF");

CAMSETUP = true;
}

void loop(){



// // // ******** BEGIN CAMERA ******** //
if(CAMERAINTERNVAL == 0){
if(!CAMSETUP){
   setupCam();
   CAMSETUP = true;
}
if (cam.motionDetected()) {
   Serial.println("Motion!");   
   cam.setMotionDetect(false);
   
  if (! cam.takePicture()) 
    Serial.println("Failed to snap!");
  else 
    Serial.println("Picture taken!");
  
  char filename[13];
  strcpy(filename, "IMAGE00.JPG");
  for (int i = 0; i < 100; i++) {
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }
  
  File imgFile = SD.open(filename, FILE_WRITE);
  
  uint32_t jpglen = cam.frameLength();
  Serial.print(jpglen, DEC);
  Serial.println(" byte image");
 
  Serial.print("Writing image to "); Serial.print(filename);
  
  while (jpglen > 0) {
    // read 32 bytes at a time;
    uint8_t *buffer;
    uint8_t bytesToRead = min((uint32_t)32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
    buffer = cam.readPicture(bytesToRead);
    imgFile.write(buffer, bytesToRead);


    jpglen -= bytesToRead;
  }
  delay(500);
  imgFile.close();
  Serial.println("...Done!");
  cam.resumeVideo();
  cam.setMotionDetect(true);
  CAMERAINTERNVAL+= 1;
 }
}
// // ******** END CAMERA ******** //
  if(LOGINTERVAL == 5){
    LOGINTERVAL = 0;
  }

  if(CAMERAINTERNVAL == 60){

  cam.resumeVideo();
  cam.setMotionDetect(true);
  Serial.println("Camera Reset");
    CAMERAINTERNVAL = 0;
    CAMACTIVE = true;
  }


  if(LOGINTERVAL == 0){

    logger.logJsonData();
    
    Serial.println("Completed Log");

  } 

    if(CAMERAINTERNVAL != 0){
          CAMERAINTERNVAL+= 1;
  }

LOGINTERVAL++;
LogComplete = true;
wifiServer.showWebPage();
delay(1000);


}


