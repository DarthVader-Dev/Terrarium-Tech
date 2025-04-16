#include "include_files.h"
#include <Wire.h>

NETWORK wifiServer;
HELPERS helpers;
THSensor thSensor;
UVBSensor uvbSensor;
//FILESYSTEM fSystem;
//LOGGER loggerHelper;
//Camera camera;
#define cameraconnection Serial1
Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);
#define chipSelect 10
int numMinutesBetweenPics = 1;


int LOGINTERVAL = 0;
int CAMERAINTERNVAL = 0;
bool SHOWWEBPAGE = true;
bool LogComplete = false;

void setup(){

  helpers.beginSetup();  
  //fSystem.beginSetup();
    //Serial.begin(9600);
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
  // Remember that bigger pictures take longer to transmit!
  
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

    //SdFile::dateTimeCallback(dateTime);
}

void loop(){

  
    //if(SHOWWEBPAGE){
        wifiServer.showWebPage();
  
  //}



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

 }
  if(LOGINTERVAL == 10){
    LOGINTERVAL = 0;
  }

  if(CAMERAINTERNVAL == (30 * numMinutesBetweenPics)){
    //camera.setActive(true);
    CAMERAINTERNVAL = 0;
  }

  //if(!LogComplete){
  if(LOGINTERVAL == 0){
    //Serial.println("loop");
    thSensor.LogData();
    uvbSensor.LogData();
    //LogComplete = true;
  }
//Serial.println(camera.motionActive());
  //if(CAMERAINTERNVAL == 0 && camera.motionActive()){
  if(CAMERAINTERNVAL == 0){
  //  Serial.println(CAMERAINTERNVAL);
   // Serial.println(camera.motionActive());    
   // if(came.getCamera().detectsMotion()){
    //  camera.takeSnapShot();
    //      camera.setActive(false);
          CAMERAINTERNVAL+= 1;
   // }
  cam.resumeVideo();
  cam.setMotionDetect(true);
  }

  //}
LOGINTERVAL++;
LogComplete = true;
//SHOWWEBPAGE = false;
CAMERAINTERNVAL +=1;
Serial.println(CAMERAINTERNVAL);
  delay(1000);
}

// void setUpCamera(){

// Serial.println("camera setup");

//   if(chipSelect != 10) pinMode(10, OUTPUT); // SS on Uno, etc.

//   Serial.begin(9600);
//   Serial.println("VC0706 Camera test");
//   if (camera.begin()) {
//     Serial.println("Camera Found:");
//   } else {
//     Serial.println("No camera found?");
//     return;
//   }
//   // Print out the camera version information (optional)
//   char *reply = camera.getVersion();
//   if (reply == 0) {
//     Serial.print("Failed to get version");
//   } else {
//     Serial.println("-----------------");
//     Serial.print(reply);
//     Serial.println("-----------------");
//   }

//   // Set the picture size - you can choose one of 640x480, 320x240 or 160x120 
//   // Remember that bigger pictures take longer to transmit!
  
//   //cam.setImageSize(VC0706_640x480);        // biggest
//   camera.setImageSize(VC0706_320x240);        // medium
//   //cam.setImageSize(VC0706_160x120);          // small

//   // You can read the size back from the camera (optional, but maybe useful?)
//   uint8_t imgsize = camera.getImageSize();
//   Serial.print("Image size: ");
//   if (imgsize == VC0706_640x480) Serial.println("640x480");
//   if (imgsize == VC0706_320x240) Serial.println("320x240");
//   if (imgsize == VC0706_160x120) Serial.println("160x120");


//   //  Motion detection system can alert you when the camera 'sees' motion!
//   camera.setMotionDetect(true);           // turn it on
//   //cam.setMotionDetect(false);        // turn it off   (default)

//   // You can also verify whether motion detection is active!
//   Serial.print("Motion detection is ");
//   if (camera.getMotionDetect()) 
//     Serial.println("ON");
//   else 
//     Serial.println("OFF");

  //  SdFile::dateTimeCallback(dateTime);
// }

// void dateTime(uint16_t* date, uint16_t* time) {
//   DateTime now = loggerHelper.getCurrentDateTime();

//   // Date format: bits 15–9 = year since 1980, bits 8–5 = month, bits 4–0 = day
//   *date = FAT_DATE(now.year(), now.month(), now.day());

//   // Time format: bits 15–11 = hours, bits 10–5 = minutes, bits 4–0 = seconds/2
//   *time = FAT_TIME(now.hour(), now.minute(), now.second());
// }

