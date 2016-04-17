/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/green/0 will turn off green LED,
 *    http://server_ip/green/1 will turn on green LED
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "_Repeater";
const char* password = "pw";

const int buttonPin = 4;     // the number of the pushbutton pin on the Witty Cloud board
const int ledPin1 =  12;      // the number of the Green LED pin
const int ledPin2 =  13;      // the number of the Blue LED pin
const int ledPin3 =  15;      // the number of the Red LED pin

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare LED's
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, 0);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, 0);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, 0);
  
  pinMode(buttonPin, INPUT);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  if (digitalRead(buttonPin) == LOW) //If pressed all colors will be turned off
  {
    digitalWrite(ledPin1, 0);
    digitalWrite(ledPin2, 0);
    digitalWrite(ledPin3, 0);
  }
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val, color;
  if (req.indexOf("/green/0") != -1)
  {
    val = 0;
    color = ledPin1;
  }
  else if (req.indexOf("/green/1") != -1)
  {
    val = 1;
    color = ledPin1;
  }
  else if (req.indexOf("/blue/0") != -1)
  {
    val = 0;
    color = ledPin2;
  }
  else if (req.indexOf("/blue/1") != -1)
  {
    val = 1;
    color = ledPin2;
  }
  else if (req.indexOf("/red/0") != -1)
  {
    val = 0;
    color = ledPin3;
  }
  else if (req.indexOf("/red/1") != -1)
  {
    val = 1;
    color = ledPin3;
  }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  digitalWrite(color, val);
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

