#include "include_files.h"
#include <Wire.h>

NETWORK wifiServer;
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


int LOGINTERVAL = 0;
int CAMERAINTERNVAL = 0;
bool SHOWWEBPAGE = true;
bool LogComplete = false;
bool showFiles = true;

void setup(){
delay(1000);  // Give power time to stabilize
Serial.begin(9600);
delay(200);   // Allow Serial and power to settle

if (!SD.begin(chipSelect)) {
  Serial.println("❌ SD failed to initialize in setup");
  while (true);
}

if (!SD.exists("/PHOTOS")) {
  SD.mkdir("/PHOTOS");
  Serial.println("✅ /PHOTOS folder created");
}

if (!SD.exists("/ENV")) {
  SD.mkdir("/ENV");
  Serial.println("✅ /PHOTOS folder created");

SdFile::dateTimeCallback(fSystem.fDateTime);
}

if(!CAMSETUP){
   setupCam();
   CAMSETUP = true;
}
}

void setupCam(){
   
  Serial.println("VC0706 Camera test");
  
  // see if the card is present and can be initialized:
  // if (!SD.begin(chipSelect)) {
  //   Serial.println("Card failed, or not present");
  //   // don't do anything more:
  //   return;
  // }  
 //   File root = SD.open("/");
  //fSystem.listSdFiles(root,0);
  //root.close();

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
  // Remember that bigger pictures take longer to transmit!
  
  cam.setImageSize(VC0706_640x480);        // biggest
  //cam.setImageSize(VC0706_320x240);        // medium
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
}

void loop(){
//Serial.println("loop");
//wifiServer.showWebPage();
  // if(showFiles){
  //   fSystem.printAllFiles();
  // }
  // showFiles = false;
  // Serial.println(showFiles);
    //if(SHOWWEBPAGE){
        

  //}
// if(!CAMSETUP){
//    setupCam();
//    CAMSETUP = true;
// }
// // ******** BEGIN CAMERA ******** //
if(CAMERAINTERNVAL == 0){
  cam.setMotionDetect(true);
  if (cam.motionDetected()) {
   Serial.println("Motion!");   
   cam.setMotionDetect(false);
   Serial.println("Cam IF");
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
    if (! SD.exists("/PHOTOS/" + String(filename))) {
      break;
    }
  }

File imgFile = SD.open("/PHOTOS/" + String(filename), FILE_WRITE);
//File imgFile = fSystem.getImageFileToSaveTo(String(filename));
Serial.println(imgFile.name());
  if (!imgFile) {
    Serial.println("SD open failed");
    return;
  }
          
  Serial.println(imgFile.available());
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

    //Serial.print("Read ");  Serial.print(bytesToRead, DEC); Serial.println(" bytes");

    jpglen -= bytesToRead;
  }
  imgFile.close();
  Serial.println("...Done!");
  cam.setMotionDetect(false);
  CAMERAINTERNVAL+= 1;
  CAMACTIVE = false;

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
    //Serial.println("logging");
    logger.logJsonData();
    //Serial.println("logged");

  }

  // if(!CAMACTIVE && CAMERAINTERNVAL != 0){
  //         CAMERAINTERNVAL+= 1;
  // }

    if(CAMERAINTERNVAL != 0){
          CAMERAINTERNVAL+= 1;
  }
  
LOGINTERVAL++;
LogComplete = true;

//CAMERAINTERNVAL +=1;
digitalWrite(LED_BUILTIN, HIGH);
delay(1000);
//wifiServer.showWebPage();
//Serial.print("CAMACTIVE -"); Serial.println(CAMACTIVE);
// Serial.print("CAMERAINTERNVAL -"); Serial.println(CAMERAINTERNVAL);
digitalWrite(LED_BUILTIN, LOW);
}



