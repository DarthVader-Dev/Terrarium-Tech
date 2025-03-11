#include "wifi.h"
#include "WiFiS3.h"
#include "file_system.h"
#include "arduino_secrets.h" 

char ssid[] = SECRET_SSID;

char pass[] = SECRET_PASS;

int keyIndex = 0; 

int led =  LED_BUILTIN;

int status = WL_IDLE_STATUS;

FILESYSTEM fileSystem;

bool WIFISETUPCOMPLETE;
bool fileWrittenTo;

WiFiServer server(80);

  WIFI::WIFI() {
  
  init();
}
void WIFI::init() {

}

void WIFI::update() {
    
}
byte WIFI::getState() {
  update();
  return state;
}

void WIFI::printWifiStatus() {


  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);

}

void WIFI::beginSetup(){
  Serial.begin(9600); 

  pinMode(led, OUTPUT); 

  if (WiFi.status() == WL_NO_MODULE) {

    Serial.println("Communication with WiFi module failed!");

    while (true);

  }


  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {

    Serial.println("Please upgrade the firmware");

  }

  while (status != WL_CONNECTED) {

    Serial.print("Attempting to connect to Network named: ");

    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);

    delay(10000);

  }

  server.begin();

  printWifiStatus();   
}



void WIFI::showWebPage(){

if(!WIFISETUPCOMPLETE){
  beginSetup();
  WIFISETUPCOMPLETE = true;
}

WiFiClient client = server.available();


  if (client) { 

    Serial.println("new client");

    String currentLine = "";

    while (client.connected()) {

      if (client.available()) {

        char c = client.read();

        Serial.write(c);

        if (c == '\n') { 

          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");

            client.println("Content-type:text/html");

            client.println();

            client.print(fileSystem.getWebPage());

            client.println();

            break;

          } else { 

            currentLine = "";

          }

        } else if (c != '\r') { 

          currentLine += c; 

        }

        if (currentLine.endsWith("GET /H")) {

          digitalWrite(LED_BUILTIN, HIGH);

        }

        if (currentLine.endsWith("GET /L")) {

          digitalWrite(LED_BUILTIN, LOW);

        }

      }

    }

    client.stop();

    Serial.println("client disconnected");

  }
}

void WIFI::writeData(char d[]){
  WiFiClient client = server.available(); 
  client.println(d);
}
