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
  
   Serial.begin(9600);


  // check for the WiFi module:
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

    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
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
  if (client) {

    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        //Serial.write(c);


        if (c == '\n' && currentLineIsBlank) {

        //Serial.println(request);

        if(request.indexOf("GET /ENV/UVLOG.JS") >= 0 || request.indexOf("GET /ENV/THLOG.JS") >= 0){
            String filen = "";
          if(request.indexOf("GET /ENV/UVLOG.JS") >= 0){
            filen = "ENV/UVLOG.JS";
          }

          if(request.indexOf("GET /ENV/THLOG.JS") >= 0){
                filen = "ENV/THLOG.JS";
          }
            //Serial.println(filen);
            requestType = "Content-Type: application/javascript";
            fileString = webPageFIle.getLogFile(filen);
        }

        if(request.indexOf("GET / ") >= 0){
            //Serial.println("Web File");
            requestType = "Content-Type: text/html";
            fileString = webPageFIle.getWebPage();
        } 
          // send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println(requestType);
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 15");  // refresh the page automatically every 5 sec
          client.println();
          // client.println("<!DOCTYPE HTML>");
          // client.println("<html>");

          client.println();
          client.print(fileString);
          client.println();
          // client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    delay(10);
    client.stop();
  }
}

void NETWORK::writeData(char d[]){
  WiFiClient client = server.available(); 
  client.println(d);
}

