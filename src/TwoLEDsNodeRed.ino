#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Nokia";
const char* password = "isuru2701";

ESP8266WebServer server(80);

const int ledPin1 = D4; // GPIO 4
const int ledPin2 = D3; // GPIO 5

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
    Serial.println("request on led1");
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

