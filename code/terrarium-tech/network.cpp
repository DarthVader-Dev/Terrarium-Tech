#include "network.h"
#include "file_system.h"
#include "arduino_secrets.h" 
#include <WiFiNINA.h>

char ssid[] = SECRET_SSID;

char pass[] = SECRET_PASS;

int keyIndex = 0; 

int led =  LED_BUILTIN;

int status = WL_IDLE_STATUS;
        //

FILESYSTEM webPageFIle;

bool WIFISETUPCOMPLETE;
bool fileWrittenTo;

WiFiServer server(80);

  NETWORK::NETWORK() {
  
  init();
}
void NETWORK::init() {

}

void NETWORK::update() {
    
}
byte NETWORK::getState() {
  update();
  return state;
}

void NETWORK::printWifiStatus() {

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

void NETWORK::beginSetup(){

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module not found.");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.print("Outdated firmware: ");
    Serial.println(fv);
  }

  int attempts = 0;
  const int maxAttempts = 15;

  while ((status = WiFi.begin(ssid, pass)) != WL_CONNECTED && attempts < maxAttempts) {
    Serial.print("Attempt ");
    Serial.print(attempts + 1);
    Serial.println(": Connecting...");
    delay(1000);
    attempts++;
  }

  if (status == WL_CONNECTED) {
    Serial.println("Connected to WiFi.");
    server.begin();
    printWifiStatus();
    pinMode(LED_BUILTIN, OUTPUT);
  } else {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Failed to connect after max attempts.");
  }
}



void NETWORK::writeData(char d[]){
  WiFiClient client = server.available(); 
  client.println(d);
}

void NETWORK::sendFile(WiFiClient& client, const char* path, const char* contentType) {
  File file = SD.open(path);
  
  if (!file) {
    Serial.print(path);Serial.println("Not Found");
    send404(client);
    return;
  }
  Serial.println("web file found");
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(contentType);
  client.println("Connection: close");

  client.println();

  while (file.available()) {

    client.write(file.read());
  }
  file.close();
  client.stop();
}

void NETWORK::sendFile(WiFiClient& client, String path, const char* contentType) {
  File file = SD.open(path);
  if (!file) {
    send404(client);
    return;
  }
  Serial.println("web file found");
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(contentType);
  client.println("Connection: close");

  client.println();

  while (file.available()) {

    client.write(file.read());
  }
  file.close();
  client.stop();
}

void NETWORK::sendJsonFile(WiFiClient& client, const char* path, const char* contentType) {
  File file = SD.open(path);
  if (!file) {
    Serial.println("File Not Found " + String(path));

    send404(client);
    return;
  }

  Serial.println("File Found " + String(path));

  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(contentType);
  client.println("Connection: close");
  //client.println("Refresh: 30");
  client.println();

  while (file.available()) {
    client.write(file.read());

  }
  
  file.close();
  client.stop();
}

void NETWORK::send404(WiFiClient& client) {
   String req = client.readStringUntil('\r');
  Serial.println(req);
  client.println("HTTP/1.1 404 Not Found");
  client.println("Content-Type: text/plain");
  client.println("Connection: close");
  client.println();
  client.println("404 - Not Found");
  client.stop();
}


void NETWORK::showWebPage(){

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
String NETWORK::getImagePath(String request){
  String results = "";

  int firstSpace = request.indexOf(" ");
  int lastSpace = request.indexOf("JPG ");
  return request.substring(firstSpace + 1, lastSpace + 3);

}


void NETWORK::sendNoFavicon(WiFiClient& client) {
  client.println("HTTP/1.1 204 No Content");
  client.println("Connection: close");
  client.println();
}

