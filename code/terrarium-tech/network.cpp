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

// void NETWORK::printWifiStatus() {


//   Serial.print("SSID: ");
//   Serial.println(WiFi.SSID());
//   IPAddress ip = WiFi.localIP();
//   Serial.print("IP Address: ");
//   Serial.println(ip);
//   long rssi = WiFi.RSSI();
//   Serial.print("signal strength (RSSI):");
//   Serial.print(rssi);
//   Serial.println(" dBm");
//   Serial.print("To see this page in action, open a browser to http://");
//   Serial.println(ip);

// }

void NETWORK::printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void NETWORK::beginSetup(){
  //Serial.begin(9600);
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
  const int maxAttempts = 20;

  while ((status = WiFi.begin(ssid, pass)) != WL_CONNECTED && attempts < maxAttempts) {
    Serial.print("Attempt ");
    Serial.print(attempts + 1);
    Serial.println(": Connecting...");
    delay(10000);
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



// void NETWORK::showWebPage(){

// if(!WIFISETUPCOMPLETE){
//   beginSetup();
//   WIFISETUPCOMPLETE = true;
// }


// String request = "";
// String requestType = "";
// String fileString = "";

// WiFiClient client = server.available();
//   if (client) {

//     boolean currentLineIsBlank = true;
//     while (client.connected()) {
//       if (client.available()) {
//         char c = client.read();
//         request += c;
//         //Serial.write(c);


//         if (c == '\n' && currentLineIsBlank) {

//         //Serial.println(request);

//         if(request.indexOf("GET /ENV/LOG.JS") >= 0 || request.indexOf("GET /ENV/UVLOG.JS") >= 0 || request.indexOf("GET /ENV/THLOG.JS") >= 0){
//             String filen = "";
//           if(request.indexOf("GET /ENV/UVLOG.JS") >= 0){
//             filen = "ENV/UVLOG.JS";
//           }

//           if(request.indexOf("GET /ENV/LOG.JS") >= 0){
//                 filen = "ENV/LOG.JS";
//           }

//           if(request.indexOf("GET /ENV/THLOG.JS") >= 0){
//                 filen = "ENV/THLOG.JS";
//           }
//             //Serial.println(filen);
//             requestType = "Content-Type: application/javascript";
//             fileString = webPageFIle.getLogFile(filen);

//                 client.sendHeader("Content-Type", "application/json");  // or "application/x-ndjson"
//                 client.streamFile(fileString, "application/json");
//                 //logFile.close()
//         }

//         if(request.indexOf("GET / ") >= 0){
//             //Serial.println("Web File");
//             requestType = "Content-Type: text/html";
//             fileString = webPageFIle.getWebPage();
//         } 
//           // send a standard HTTP response header
//           client.println("HTTP/1.1 200 OK");
//           client.println(requestType);
//           client.println("Connection: close");  // the connection will be closed after completion of the response
//           client.println("Refresh: 30");  // refresh the page automatically every 5 sec
//           client.println();
//           // client.println("<!DOCTYPE HTML>");
//           // client.println("<html>");

//           client.println();
//           client.print(fileString);
//           client.println();
//           // client.println("</html>");
//           break;
//         }
//         if (c == '\n') {
//           // you're starting a new line
//           currentLineIsBlank = true;
//         } else if (c != '\r') {
//           // you've gotten a character on the current line
//           currentLineIsBlank = false;
//         }
//       }
//     }

//     delay(10);
//     client.stop();
//   }
// }

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
  //client.println("Refresh: 30");
  client.println();

  while (file.available()) {
    //Serial.println("reading web file");
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
  //client.println("Refresh: 30");
  client.println();

  while (file.available()) {
    //Serial.println("reading web file");
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

  //Serial.println("log file found");

  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(contentType);
  client.println("Connection: close");
  //client.println("Refresh: 30");
  client.println();
  //String req = client.readStringUntil('\r');
  //Serial.println(req);
  while (file.available()) {
    client.write(file.read());
    //Serial.println("reading json");
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

  // Wait for request
  while (client.connected() && !client.available());

String req = client.readStringUntil('\r');
  client.read(); // flush \n
  //Serial.println("Request: " + req);

if (req.indexOf("GET /ENV/LOG.JS") != -1 || req.indexOf("GET /log.js") != -1) {
  //Serial.println("Env");
  sendJsonFile(client, "/ENV/LOG.JS", "application/json");
} else if (req.indexOf("GET / ") >= 0 || req.indexOf("GET /INDX.HTM") >= 0) {
    Serial.println("INDX");
    sendFile(client, "INDX.HTM", "text/html");
} else if (req.indexOf("GET /PH.HTM ") >= 0) {
    Serial.println("PHOTOS");
    sendFile(client, "PH.HTM", "text/html");
  } else if (req.indexOf("GET /PHT/IMAGE") >= 0) {
    Serial.println("IMAGE");
    //Serial.println(client);
    String imgPath = getImagePath(req);
    Serial.println(imgPath);
    sendFile(client, imgPath, "image/jpeg");
  }else if (req.indexOf("GET /favicon.ico") != -1) {
    Serial.println("FAV");
  sendNoFavicon(client);  // suppress repeated errors
}
else {
  send404(client);
}
  

    //  delay(10);
    //  client.stop();  
}
String NETWORK::getImagePath(String request){
  String results = "";

  int firstSpace = request.indexOf(" ");
  int lastSpace = request.indexOf("JPG ");
  //char result[(lastSpace + 3) - (firstSpace - 1)]
  return request.substring(firstSpace + 1, lastSpace + 3); //String
  //return  //(firstSpace) + String(lastSpace);
  //return request.toCharArray()
}


void NETWORK::sendNoFavicon(WiFiClient& client) {
  // Option 1: respond with empty success
  client.println("HTTP/1.1 204 No Content");
  client.println("Connection: close");
  client.println();
}

