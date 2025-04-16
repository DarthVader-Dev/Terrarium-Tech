#include "file_system.h"
#include "include_files.h"
File myFile;
//LOGGER logHelper;

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

  //SdFile::dateTimeCallback(logHelper.dateTime);

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
//Serial.println("readFileToString - PRE" + filename);

    File file = SD.open(filename);
    if (!file) {
        //Serial.println("Failed to open file.");
        return "";
    }

    //Serial.println("file found - PRE " + filename);

    String content = "";
    //Serial.println("index of " + String(filename.indexOf("ENV")));

        if(filename.indexOf("ENV") == -1){
          //Serial.println("Non ENV file.");
            while (file.available()) {
                content += (char)file.read(); 
                //Serial.println(content);
                    }
        }

      if(filename.indexOf("ENV") >= 0){        
        //Serial.println("ENV file.");
            while (file.available()) {
              content += (char)file.read(); 
              //Serial.println(content);
            }
        
      }

    //Serial.println("file closing -  " + filename);
    file.close();
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

char lstChar = myFile.read();
//Serial.println("Line 85 - LastChar - " + String(lstChar) + " - LastChar");

int pos = myFile.position();
//Serial.println("Line 88 - Position - " + String(pos) + " - Position");

int sIndex = myFile.size() -1;
//Serial.println("Line 91 - sIndex - " + String(sIndex) + " - sIndex");

int charVal = 0;

  if(myFile.read() != char(93)){
    while(myFile.read() != char(93)){
      sIndex -= 1;
      myFile.seek(sIndex);
      pos = myFile.position();
      // Serial.println("Line 96 - sIndex - " + String(sIndex) + " - sIndex");
      // Serial.println("Line 97 - Position - " + String(pos) + " - Position");
      lstChar = myFile.read();
      charVal = (int)(char(lstChar));
      // Serial.println("Line 100 - LastCharCode " + String(charVal));
      }
}

myFile.seek(sIndex);
pos = myFile.position();
// Serial.println("Line 118 - sIndex - " + String(sIndex) + " - sIndex");
// Serial.println("Line 119 - Position - " + String(pos) + " - Position");
lstChar = myFile.read();
charVal = (int)(char(lstChar));
//Serial.println("Line 122 - LastCharCode " + String(charVal));


        String data = dataItem;
        myFile.print('\n' + data);
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

void FILESYSTEM::printDirectory(File dir, int numTabs) {


  while (true) {


    File entry =  dir.openNextFile();


    if (! entry) {


      // no more files


      break;


    }


    for (uint8_t i = 0; i < numTabs; i++) {


      Serial.print('\t');


    }


    Serial.print(entry.name());


    if (entry.isDirectory()) {


      Serial.println("/");


      printDirectory(entry, numTabs + 1);


    } else {


      // files have sizes, directories do not


      Serial.print("\t\t");


      Serial.println(entry.size(), DEC);


    }


    entry.close();


  }
}
