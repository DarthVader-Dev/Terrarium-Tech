#include "file_system.h"
#include <SD.h>
File myFile;
bool FILESYSTEMSETUPCOMPLETE;


FILESYSTEM::FILESYSTEM() {

  init();
}
void FILESYSTEM::init() {
}

void FILESYSTEM::update() {
}
byte FILESYSTEM::getState() {
  update();
  return state;
}



void FILESYSTEM::beginSetup() {
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
 
  pinMode(10, OUTPUT);

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("INDX.HTM");
  if (myFile) {
    Serial.println("INDX.HTM:");

  
    while (myFile.available()) {
      Serial.write(myFile.read());
    }

    myFile.close();
  } else {

    Serial.println("error opening INDX.HTM");
  }
}

void FILESYSTEM::readData() {
    pinMode(10, OUTPUT);
    myFile = SD.open("INDX.HTM");
  if (myFile) {
    Serial.println("INDX.HTM:");


    while (myFile.available()) {
      Serial.write(myFile.read());
    }

    myFile.close();
  } else {

    Serial.println("error opening INDX.HTM");
  }
}

String FILESYSTEM::readFileToString(const char *filename) {
    File file = SD.open(filename);
    if (!file) {
        Serial.println("Failed to open file.");
        return "";
    }

    String content = "";
    while (file.available()) {
        content += (char)file.read(); 
    }

    file.close();
    return content;
}

void FILESYSTEM::writeData(char d[]) {
  myFile = SD.open("INDX.HTM", FILE_WRITE);

  
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println(d);

    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening test.txt");
  }
}


String FILESYSTEM::getWebPage(){
if(!FILESYSTEMSETUPCOMPLETE){
  beginSetup();
  FILESYSTEMSETUPCOMPLETE = true;
}

 return readFileToString("INDX.HTM");
}

