#include "networkr4.h"
#include "file_system.h"
#include "arduino_secrets.h" 
// #include <WiFiNINA.h>

#include "WiFi.h"

char ssid[] = SECRET_SSID;

char pass[] = SECRET_PASS;

int keyIndex = 0; 

int led =  LED_BUILTIN;

int status = WL_IDLE_STATUS;
        //

// FILESYSTEM fSystem;  
extern FILESYSTEM fSystem;

bool WIFISETUPCOMPLETE;
bool fileWrittenTo;

WiFiServer server(80);

  NETWORKR4::NETWORKR4() {
  
  init();
}
void NETWORKR4::init() {

}

void NETWORKR4::update() {
    
}
byte NETWORKR4::getState() {
  update();
  return state;
}

void NETWORKR4::printWifiStatus() {

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());


  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);


  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void NETWORKR4::beginSetup(){
if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 2 seconds for connection:
    delay(1000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}



void NETWORKR4::writeData(char d[]){
  WiFiClient client = server.available(); 
  client.write(d);
}

void NETWORKR4::sendFile(WiFiClient& client, const char* path, const char* contentType) {
  File file = fSystem.getHomePageFile(); // SD.open(path);
  Serial.println(path);
  if (!file) {
    Serial.print(path);Serial.println(" Not Found");
    send404(client);
    return;
  }
  Serial.println("web file found");
  client.write("HTTP/1.1 200 OK\r\n");
  client.write("Content-Type: ");
  client.write(contentType);
  client.write("Connection: close\r\n");

  client.write("\r\n");

  while (file.available()) {

    client.write(file.read());
  }
  file.close();
  client.stop();
}

void NETWORKR4::sendFile(WiFiClient& client, String path, const char* contentType) {
  File file = SD.open(path);
  if (!file) {
    send404(client);
    return;
  }
  Serial.println("web file found");
  client.write("HTTP/1.1 200 OK\r\n");
  client.write("Content-Type: ");
  client.write(contentType);
  client.write("Connection: close\r\n");

  client.write("\r\n");

  while (file.available()) {

    client.write(file.read());
  }
  file.close();
  client.stop();
}

void NETWORKR4::sendJsonFile(WiFiClient& client, const char* path, const char* contentType) {
  File file = SD.open(path);
  if (!file) {
    Serial.println("File Not Found " + String(path));

    send404(client);
    return;
  }

  Serial.println("File Found " + String(path));

  client.write("HTTP/1.1 200 OK\r\n");
  client.write("Content-Type: ");
  client.write(contentType);
  client.write("Connection: close\r\n");
  //client.write("Refresh: 30");
  client.write("\r\n");

  while (file.available()) {
    client.write(file.read());

  }
  
  file.close();
  client.stop();
}

void NETWORKR4::send404(WiFiClient& client) {
   String req = client.readStringUntil('\r');
  Serial.println(req);
  client.write("HTTP/1.1 404 Not Found\r\n");
  client.write("Content-Type: text/plain\r\n");
  client.write("Connection: close\r\n");
  client.write("\r\n");
  client.write("404 - Not Found\r\n");
  client.stop();
}


void NETWORKR4::showWebPage(){

if(!WIFISETUPCOMPLETE){
  beginSetup();
  WIFISETUPCOMPLETE = true;
}


String request = "";
String requestType = "";
String fileString = "";

WiFiClient client = server.available();
  if (!client) return;

  while (client.connected() && !client.available());

String req = client.readStringUntil('\r');
  client.read();




if(req.indexOf("GET / ") >= 0 || req.indexOf("GET /INDX.HTM") >= 0){
    Serial.println("INDX");
    sendFile(client, "INDX.HTM", "text/html");
}
else if (req.indexOf("GET /ENV/LOG.JS") >= 0 || req.indexOf("GET /log.js") >= 0) { 
 sendJsonFile(client, "/ENV/LOG.JS", "application/json");
}else if (req.indexOf("GET /PH.HTM ") >= 0) {
    Serial.println("PHOTOS");
    sendFile(client, "PH.HTM", "text/html");
  } else if (req.indexOf("GET /PHT/IMAGE") >= 0) {
    Serial.println("IMAGE");

    String imgPath = getImagePath(req);
    Serial.println(imgPath);
    sendFile(client, imgPath, "image/jpeg");
  }else if (req.indexOf("GET /favicon.ico") != -1) {
    Serial.println("FAV");
  sendNoFavicon(client); 
}


}
String NETWORKR4::getImagePath(String request){
  String results = "";

  int firstSpace = request.indexOf(" ");
  int lastSpace = request.indexOf("JPG ");
  return request.substring(firstSpace + 1, lastSpace + 3);

}


void NETWORKR4::sendNoFavicon(WiFiClient& client) {
  client.write("HTTP/1.1 204 No Content\r\n");
  client.write("Connection: close\r\n");
  client.write("\r\n");
}


void NETWORKR4::connect() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected. IP: ");
  Serial.println(WiFi.localIP());
}

bool NETWORKR4::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}