/*

  https://github.com/Isuru2701/esp-http-leds

 A small example showing the use of Node-red as a platform for IoT
 This project will light up two LEDs connected to the ESP8266
 This is done by setting up the ESP8266 as a http server which accepts requests from the node-red dashboard

 Components:
  1. ESP8266
  2. Two LEDs
  3. Two resistors (ohms depend on your LEDs)
  4. Breadboard
  5. Jumper wires
  6. Micro-USB cable for connecting the ESP8266 to your computer

  Instructions:
  1. Connect the ESP8266 to your computer using the micro-USB cable
  2. Connect the LEDs with the pins D2 and D3 (you can change this l8r in the code)
  3. Upload this code
  4. Run node-red on your terminal
  5. Setup the node-red appropriately according to the instructions. Alternatively import the flow from Flow/flows.json in the project structure.

*/


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "SLT_H";
const char* password = "YahampathH8282";

ESP8266WebServer server(80);

const int ledPin1 = D2; 
const int ledPin2 = D3; 

bool led1 = false;
bool led2 = false;

void handleRoot() {
  server.send(200, "text/plain", "Welcome to ESP8266 Web Control");
}


void handleLED1() {
    Serial.println("request on led1");
  if(led1){
    digitalWrite(ledPin1, LOW);
    server.send(200, "text/plain", "LED1 is OFF");
    led1 = false;
    }else{
    digitalWrite(ledPin1, HIGH);
    server.send(200, "text/plain", "LED1 is ON");
    led1=true;
    }
  
}

void handleLED2() {
    Serial.println("request on led2");
  if(led2){
    digitalWrite(ledPin2, LOW);
    server.send(200, "text/plain", "LED2 is OFF");
    led2 = false;
    }else{
    digitalWrite(ledPin2, HIGH);
    server.send(200, "text/plain", "LED2 is ON");
    led2=true;
    }
}

void setup() {
    Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Define HTTP endpoints
  server.on("/", HTTP_GET, handleRoot);
  server.on("/led1", HTTP_GET, handleLED1);
  server.on("/led2", HTTP_GET, handleLED2);


  server.begin();
  Serial.println("HTTP server started");


}

void loop() {
  server.handleClient();
}

