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
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(10, OUTPUT);

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file for reading:
  myFile = SD.open("INDX.HTM");
  if (myFile) {
    Serial.println("INDX.HTM:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening INDX.HTM");
  }
}

void FILESYSTEM::readData() {
    pinMode(10, OUTPUT);
    myFile = SD.open("INDX.HTM");
  if (myFile) {
    Serial.println("INDX.HTM:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening INDX.HTM");
  }
}

String FILESYSTEM::readFileToString(const char *filename) {
    File file = SD.open(filename);
    if (!file) {
        Serial.println("Failed to open file.");
        return "";
    }

    String content = "";  // Initialize empty String
    while (file.available()) {
        content += (char)file.read();  // Read each byte and append to String
    }

    file.close();  // Always close the file
    return content;
}

void FILESYSTEM::writeData(char d[]) {
  myFile = SD.open("INDX.HTM", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println(d);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
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

