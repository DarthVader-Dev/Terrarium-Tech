#include "cam_helper.h"
#include "include_files.h"


bool CAMERASETUPCOMPLETE = false;
bool motionDetectionActive = false;
#define cameraconnection Serial1

Adafruit_VC0706 adaCam = Adafruit_VC0706(&cameraconnection);


#define chipSelect 10
FILESYSTEM camFileSystem;

// Adafruit_VC0706 motionCam Camera::getCamera(){

//     if(!CAMERASETUPCOMPLETE){
//   beginSetup();
//   CAMERASETUPCOMPLETE = true;
//     }



//   return cam;
// }


CAMHELPER::CAMHELPER() {
  this->pin = pin;

  
  init();
}

void CAMHELPER::getStatus(){
  Serial.print("available " + String(adaCam.available()));
  //Serial.print("motion active " + String(cam.getMotionStatus()));
}
void CAMHELPER::init() {
  pinMode(pin, INPUT);
  update();
}

void CAMHELPER::update() {
    
}
byte CAMHELPER::getState() {
  update();
  return state;
}

void CAMHELPER::beginSetup(){

motionDetectionActive = true;

if(chipSelect != 10) pinMode(10, OUTPUT); // SS on Uno, etc.
  //Serial.begin(9600);
  Serial.println("VC0706 Camera test");

  if (adaCam.begin()) {
    Serial.println("Camera Found:");
  } else {
    Serial.println("No camera found?");
    return;
  }

  char *reply = adaCam.getVersion();
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
  adaCam.setImageSize(VC0706_320x240);        // medium
  //cam.setImageSize(VC0706_160x120);          // small

  // You can read the size back from the camera (optional, but maybe useful?)
  uint8_t imgsize = adaCam.getImageSize();
  Serial.print("Image size: ");
  if (imgsize == VC0706_640x480) Serial.println("640x480");
  if (imgsize == VC0706_320x240) Serial.println("320x240");
  if (imgsize == VC0706_160x120) Serial.println("160x120");


}

bool CAMHELPER::motionActive(){
  return motionDetectionActive;
}

bool CAMHELPER::detectsMotion(){
  return adaCam.motionDetected();
}

void CAMHELPER::setActive(bool motionActive){
    if(!CAMERASETUPCOMPLETE){
  beginSetup();
  CAMERASETUPCOMPLETE = true;

  motionDetectionActive = motionActive;

}
}


bool CAMHELPER::takeSnapShot(){



 if (adaCam.motionDetected()) {
    Serial.println("Motion!");   
    adaCam.setMotionDetect(false);
    
    if (! adaCam.takePicture()) 
      Serial.println("Failed to snap!");
    else 
      Serial.println("Picture taken!");
    
    char filename[13];
    strcpy(filename, "IMAGE00.JPG");
    for (int i = 0; i < 100; i++) {
      filename[5] = '0' + i/10;
      filename[6] = '0' + i%10;
      // create if does not exist, do not open existing, write, sync after write
      // if (! SD.exists(filename)) {
      //   break;
      // }
    }

      File newImageFile = camFileSystem.getImageFileToSaveTo(String(filename));
      
      uint32_t jpglen = adaCam.frameLength();
      Serial.print(jpglen, DEC);
      Serial.println(" byte image");
    
      Serial.print("Writing image to "); Serial.print(filename);

      while (jpglen > 0) {
    // read 32 bytes at a time;
      uint8_t *buffer;
      uint8_t bytesToRead = min((uint32_t)32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
      buffer = adaCam.readPicture(bytesToRead);
      newImageFile.write(buffer, bytesToRead);

      //Serial.print("Read ");  Serial.print(bytesToRead, DEC); Serial.println(" bytes");

      jpglen -= bytesToRead;
      }
      newImageFile.close();
      Serial.println("...Done!");
      adaCam.resumeVideo();
      adaCam.setMotionDetect(motionDetectionActive);
      return true;
  }
  return false;
}