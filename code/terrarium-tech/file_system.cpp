#include "file_system.h"
#include "include_files.h"
#include <SD.h>
File myFile;
LOGGER fLogHelper;
int RTCDIGITPIN = 2;

bool FILESYSTEMSETUPCOMPLETE;


FILESYSTEM::FILESYSTEM(uint8_t csPin) : _csPin(csPin), _initialized(false) {}


bool FILESYSTEM::begin() {
  Serial.print("Initializing SD on CS pin ");
  Serial.println(_csPin);

  
  pinMode(_csPin, OUTPUT);
  digitalWrite(_csPin, HIGH); // Deselect SD to avoid SPI conflict

  _initialized = SD.begin(_csPin);

  Serial.println(_initialized ? "SD.begin() succeeded." : "SD.begin() failed.");
  return _initialized;
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


String FILESYSTEM::readFileToString(String filename) {

  if(!FILESYSTEMSETUPCOMPLETE){
  begin();
  FILESYSTEMSETUPCOMPLETE = true;
}
Serial.println("readFileToString - PRE" + filename);

    File file = SD.open(filename, FILE_READ);
    if (!file) {
        Serial.println("Failed to open file.");
        return "";
    }

    file.seek(0);

    Serial.println("file found - PRE " + filename);

    String content = "";
   
          //Serial.println("Non ENV file.");
          Serial.println(file.available());
          Serial.println(file.size());
          Serial.println("last }: " + content.lastIndexOf('}'));
            while (file.available()) {
              
                content += (char)file.read(); 
              
Serial.println("last }: " + content.lastIndexOf('}'));
    
    Serial.println("file closing -  " + filename);
    file.close();

    int braceIndex = content.lastIndexOf('}');
  if (braceIndex > 0) {
    content = content.substring(0, braceIndex + 1);
  } else {
    Serial.println("No valid closing brace found.");
    return "";
  }
   
    return content;
  }
}

void FILESYSTEM::writeLogData(String type,String logFile, String dataItem) {

  if(!FILESYSTEMSETUPCOMPLETE){
  begin();
  FILESYSTEMSETUPCOMPLETE = true;
}

String f = "/" + type + "/" + logFile;

File myFile = SD.open(f, O_RDWR);

  if (myFile) {

char lstChar = 0;

int pos = myFile.position();

int sIndex = myFile.size() -1;

int charVal = 0;

myFile.seek(sIndex);

        String data = dataItem;
        myFile.print('\n' + data);
        myFile.seek(0);
        myFile.close();
  } else {

    Serial.println("error opening " + f);
  }
}

void FILESYSTEM::enumerateLines(File file, int pos){ }


String FILESYSTEM::getWebPage(){
if(!FILESYSTEMSETUPCOMPLETE){
  begin();
  FILESYSTEMSETUPCOMPLETE = true;
}

 return readFileToString("INDX.HTM");
}

File FILESYSTEM::getHomePageFile(){
if(!FILESYSTEMSETUPCOMPLETE){
  begin();
  FILESYSTEMSETUPCOMPLETE = true;
}

File homePage = open("INDX.HTM", FILE_READ);
if(!homePage){
  Serial.println("Error returning home page");
}
Serial.println("returning home page");
 return homePage;
}


String FILESYSTEM::getLogFile(String fileName){
if(!FILESYSTEMSETUPCOMPLETE){
  begin();
  FILESYSTEMSETUPCOMPLETE = true;
}
  
  Serial.print("getLogFile" + fileName);
  return readFileToString(fileName);


}

File FILESYSTEM::getImageFileToSaveTo(String fileName){

  if(!SD.exists("/Photos/" + fileName)){
    return SD.open("/Photos/" + fileName, FILE_WRITE);
  }

} 

void FILESYSTEM::listSdFiles(File dir, int numTabs = 0) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // No more files
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }

    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/ (dir)");
      listSdFiles(entry, numTabs + 1);
    } else {
      Serial.print("\tSize: ");
      Serial.println(entry.size());
    }
    entry.close();
  }
}

void FILESYSTEM::writeJsonLogData(float temp, float humidity, float uvIndex){//, String timeS) {
  Serial.println("writeJsonLogData");

if(!FILESYSTEMSETUPCOMPLETE){
  begin();
  FILESYSTEMSETUPCOMPLETE = true;
}
  const char* filename = "LOG.JS";
  //Open in append mode
  File file = open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(filename);
    Serial.println("Failed to open log.js for appending");
    return;
  }

  StaticJsonDocument<256> doc;
  // doc["timestamp"] = timeS;
  doc["temp"] = temp;
  doc["humidity"] = humidity;
  doc["uvIndex"] = uvIndex;


  serializeJson(doc, file);
  file.println();

  file.close();
  Serial.println("Logged JSON line to log.js");
}


void FILESYSTEM::writeError(String error) {
if(!FILESYSTEMSETUPCOMPLETE){
  begin();
  FILESYSTEMSETUPCOMPLETE = true;
}

  String filename = "Err.TXT";


  File file = SD.open(filename, FILE_WRITE);
  if (!file) {
    return;
  }

  file.println(error);

  file.close();
}

String FILESYSTEM::readAndCleanJsonFile() {
    String filename = "/ENV/LOG.JS";
  String content = "";

  File file = SD.open(filename, FILE_READ);
  if (!file) {
    Serial.println("Failed to open file");
    return "";
  }

  while (file.available()) {
    content += (char)file.read();
  }
  file.close();

  int braceIndex = content.lastIndexOf('}');
  if (braceIndex > 0) {
    content = content.substring(0, braceIndex + 1);
  } else {
    Serial.println("No valid closing brace found.");
    return "";
  }

  return content;
}

void FILESYSTEM::fDateTime(uint16_t* date, uint16_t* time) {

 HELPERS::tcaselect(RTCDIGITPIN);
  DateTime now = fLogHelper.getFileDateTime();
  *date = FAT_DATE(now.year(), now.month(), now.day());
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

File FILESYSTEM::open(const char* path, uint8_t mode) {
  Serial.println(_initialized);
  if (!_initialized) return File();
  return SD.open(path, mode);
}

 bool FILESYSTEM::isInitialized(){
  return _initialized;
 }
