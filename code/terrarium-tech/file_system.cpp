#include "file_system.h"
#include "include_files.h"
File myFile;
LOGGER fLogHelper;

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
  Serial.println("file setup");
  Serial.begin(9600);

  pinMode(10, OUTPUT);

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
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

// String FILESYSTEM::readFileToString(const char *filename) {
//     File file = SD.open(filename);
//     if (!file) {
//         Serial.println("Failed to open file.");
//         return "";
//     }

//     String content = "";
//     while (file.available()) {
//         content += (char)file.read();
//     }

//     file.close();
//     return content;
// }

String FILESYSTEM::readFileToString(String filename) {

  if(!FILESYSTEMSETUPCOMPLETE){
  beginSetup();
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
    //Serial.println("index of " + String(filename.indexOf("ENV")));

        // if(filename.indexOf("ENV") == -1){
          //Serial.println("Non ENV file.");
          Serial.println(file.available());
          Serial.println(file.size());
          Serial.println("last }: " + content.lastIndexOf('}'));
            while (file.available()) {
              
                content += (char)file.read(); 
                //Serial.println(content);
                //Serial.println(file.available());
                    }
                    //Serial.println(file.available());
        // }
Serial.println("last }: " + content.lastIndexOf('}'));
      // if(filename.indexOf("ENV") >= 0){        
      //   Serial.println("ENV file.");
      //   Serial.println(file.size());

            // while (file.available()) {
            //   content += (char)file.read(); 
            //   Serial.print(content);
            // }
        
      // }

    Serial.println("file closing -  " + filename);
    file.close();

    int braceIndex = content.lastIndexOf('}');
  if (braceIndex > 0) {
    content = content.substring(0, braceIndex + 1);
  } else {
    Serial.println("No valid closing brace found.");
    return "";
  }
    //Serial.println("readFileToString" + filename);
    return content;
}

void FILESYSTEM::writeLogData(String type,String logFile, String dataItem) {

  if(!FILESYSTEMSETUPCOMPLETE){
  beginSetup();
  FILESYSTEMSETUPCOMPLETE = true;
}

String f = "/" + type + "/" + logFile;

File myFile = SD.open(f, O_RDWR);

  if (myFile) {

char lstChar = 0;// myFile.read();
//Serial.println("Line 124 - LastChar - " + String(lstChar) + " - LastChar");

int pos = myFile.position();
//Serial.println("Line 127 - Position - " + String(pos) + " - Position");

int sIndex = myFile.size() -1;
//Serial.println("Line 130 - sIndex - " + String(sIndex) + " - sIndex");

int charVal = 0;
// Serial.println(myFile.read());
// myFile.seek(15);
// Serial.println(myFile.read());



  // if(myFile.read() != char(91)){
  //   while(myFile.read() != char(91)){
    //   if(myFile.read() != 91){
    // while(myFile.read() != 91){
    //   sIndex += 1;
    //   myFile.seek(sIndex);
    //   pos = myFile.position();
    //    Serial.println("Line 139 - sIndex - " + String(sIndex) + " - sIndex");
    //    Serial.println("Line 140 - Position - " + String(pos) + " - Position");
    //   lstChar = myFile.read();
    //   charVal = (int)(char(lstChar));
    //    Serial.println("Line 143 - LastCharCode " + String(charVal));
    //   }
//}

myFile.seek(sIndex);
//pos = myFile.position();
// Serial.println("Line 118 - sIndex - " + String(sIndex) + " - sIndex");
// Serial.println("Line 119 - Position - " + String(pos) + " - Position");
//lstChar = myFile.read();
//charVal = (int)(char(lstChar));
//Serial.println("Line 122 - LastCharCode " + String(charVal));


        String data = dataItem;
        myFile.print('\n' + data);
        //Serial.print(data);
        myFile.seek(0);
        myFile.close();
  } else {

  // File root = SD.open("/");
  //   printDirectory(root, 0);
    Serial.println("error opening " + f);
  }
}

void FILESYSTEM::enumerateLines(File file, int pos){
  // for (int i = 0; i < pos; i++){
  //   Serial.println("Position:" + String(i) + ": Character: " + String(file.seek(i)));
  // }
}


String FILESYSTEM::getWebPage(){
if(!FILESYSTEMSETUPCOMPLETE){
  beginSetup();
  FILESYSTEMSETUPCOMPLETE = true;
}

 return readFileToString("INDX.HTM");
}


String FILESYSTEM::getLogFile(String fileName){
if(!FILESYSTEMSETUPCOMPLETE){
  beginSetup();
  FILESYSTEMSETUPCOMPLETE = true;
}
  // File file = SD.open(fileName);

  //   if (!file) {
  //       Serial.println("Failed to open file.");
  //       //return file;
  //   }
  //return readFileToString(fileName);
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

// void FILESYSTEM::savePhoto(String filename, uint32_t jpglen, uint8_t *buffer, uint8_t bytesToRead,Adafruit_VC0706 cam){
// File imgFile = SD.open(filename, FILE_WRITE);

//   while (jpglen > 0) {
//     // read 32 bytes at a time;
//     uint8_t *buffer;
//     uint8_t bytesToRead = min((uint32_t)32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
//     buffer = cam.readPicture(bytesToRead);
//     imgFile.write(buffer, bytesToRead);

//     //Serial.print("Read ");  Serial.print(bytesToRead, DEC); Serial.println(" bytes");

//     jpglen -= bytesToRead;
//   }

// }

void FILESYSTEM::writeJsonLogData(float temp, float humidity, float uvIndex, String timeS) {
  //Serial.println("writeJsonLogData");
  String filename = "/ENV/LOG.JS";

  //Open in append mode
  File file = SD.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open log.js for appending");
    return;
  }

  // Format timestamp (ISO 8601)
  // char isoTime[25];
  // snprintf(isoTime, sizeof(isoTime), "%04d-%02d-%02dT%02d:%02d:%02d",
  //          timestamp.year(), timestamp.month(), timestamp.day(),
  //          timestamp.hour(), timestamp.minute(), timestamp.second());

  // Prepare JSON object
  StaticJsonDocument<256> doc;
  //Serial.print(String(time.timestamp(DateTime::TIMESTAMP_FULL)))
  doc["timestamp"] = timeS;
  doc["temp"] = temp;
  doc["humidity"] = humidity;
  doc["uvIndex"] = uvIndex;

  // Write the object as a single line
  serializeJson(doc, file);
  file.println();  // newline to separate entries

  file.close();
  Serial.println("Logged JSON line to log.js");
}



// --- Step 1: Read file and trim junk after last '}'
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
  // Read current date and time from RTC
  DateTime now = fLogHelper.getFileDateTime();
  *date = FAT_DATE(now.year(), now.month(), now.day());
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

