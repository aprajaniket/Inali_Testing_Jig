#include <Arduino.h>
#include <ESP8266WiFi.h>
//#include <WiFi.h>
#include "HTTPSRedirect.h"

// Enter network credentials:
const char* ssid     = "IF Foundation";
const char* password = "inalihelloxyz@123";

//https://script.google.com/macros/s/AKfycbzumFMWYLT1R3Zfg2qFbqxqXaKATp24mESh92LsbCq3yq1HCeSDb0ZMz4fRXdKfn0De8g/exec
//https://script.google.com/macros/s/AKfycbyRlDfWcq5DDvf6LtZXxeTjQT-wNqPfSljbZINthhcCT1P9tXLg9Enck_Oleu4P-xR_6g/exec
//https://script.google.com/macros/s/AKfycbw2FanmgT-9a-qht2yrrt8TN80gT-Oo9sMxFXwUO_kNs0OCd1SlGg5yhF53Vc3NBKhMaw/exec
//https://script.google.com/macros/s/AKfycbxFp3JzVHzolxrUQcx4JoHcS0k96Z4xeb3GID13IP_dZeCQbvSjH1nusQcbpUzmPxcDng/exec
//https://script.google.com/macros/s/AKfycby8B7AA51eVsNt6PqdS1P2NDupxDFC1jNVK1sylLCRKQAwCNhZsFMmfozCrgbZY5KrnmA/exec
//https://script.google.com/macros/s/AKfycbz1bS2awmpxR0MJUzXMCPr8FJIYhA7AAFIMgUlyoFEcCCFeNy-VUOxj8g4p0d4ZXBldsA/exec
// Enter Google Script Deployment ID:
const char *GScriptId = "AKfycbz1bS2awmpxR0MJUzXMCPr8FJIYhA7AAFIMgUlyoFEcCCFeNy-VUOxj8g4p0d4ZXBldsA";

// Enter command (insert_row or append_row) and your Google Sheets sheet name (default is Sheet1):
String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"TestingJIG\", \"values\": ";
String payload = "";

// Google Sheets setup (do not edit)
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

// Declare variables that will be published to Google Sheets
int value0 = 0;
String value1 = "";
String value2 = "";
String value3 = "";

// Declare variables that will keep track of whether or not the data has been published
bool data_published = false;
int error_count = 0;

void setup() {

  Serial.begin(9600);
  delay(10);
  Serial.println('\n');

  // Declare pin D1 as a button input:
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D8, INPUT);
  pinMode(16,OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");

  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i = 0; i < 5; i++) {
    int retval = client->connect(host, httpsPort);
    if (retval == 1) {
      flag = true;
      Serial.println("Connected");
      break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }
  if (!flag) {
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    return;
  }
  delete client;    // delete HTTPSRedirect object
  client = nullptr; // delete HTTPSRedirect object
}


void loop() {

  // attempt to publish to Google Sheets when button is pressed (when pin reads HIGH)
 // if (digitalRead(D1) == HIGH)  {

    // before attempting to publish to Google Sheets, set the data_published variable to false and error_count to 0
    data_published = false;
    error_count = 0;
 int val = digitalRead(D2);

  if (val == 1) {
    Serial.println("Input1 is ok");
    digitalWrite(16, LOW);
       value1 = "input1 is ok";
  }
  else {
    Serial.println("continuity of input1 is not found");
    digitalWrite(16, HIGH);
       value1 = "continuity of input1 is not found..?";
  }

   int val2 = digitalRead(D1);

  if (val2 == 1) {
    Serial.println("Input2 is ok");
    digitalWrite(16, LOW);
       value2 = "Input2 is ok";
  }
  else {
    Serial.println("continuity of input2 is not found");
    digitalWrite(16, HIGH); 
       value2 = "continuity of input2 is not found..?";
  }
 
 //digitalWrite(D4, LOW);
    int val3 = digitalRead(D8);

  if (val3 == HIGH) {
    Serial.println("ON/OFF Switch is ok");
    digitalWrite(16, LOW);
    value3="ON/OFF Switch is ok";
  }
  else {
    Serial.println("continuity of ON/OFF Switch is not found..?");
    digitalWrite(16, HIGH);
     value3 = "continuity of ON/OFF Switch is not found..?";
  }

    // create some fake data to publish
    value0 ++;
  //  value1 = random(0, 1000);
 //   value2 = random(0, 100000);

    // the while loop will attempt to publish data up to 3 times
    while (data_published == false && error_count < 3) {

      static bool flag = false;
      if (!flag) {
        client = new HTTPSRedirect(httpsPort);
        client->setInsecure();
        flag = true;
        client->setPrintResponseBody(true);
        client->setContentTypeHeader("application/json");
      }
      if (client != nullptr) {
        if (!client->connected()) {
          client->connect(host, httpsPort);
        }
      }
      else {
        Serial.println("Error creating client object!");
      }

      // Create json object string to send to Google Sheets
      payload = payload_base + "\"" + value0 + "," + value1 + "," + value2 + "," + value3 + "\"}";

      // Publish data to Google Sheets
      Serial.println("Publishing data...");
      Serial.println(payload);

      if (client->POST(url, host, payload)) {
        // do stuff here if publish was successful
        data_published = true;
      }
      else {
        // do stuff here if publish was not successful
        Serial.println("Error while connecting");
        error_count++;
        delay(2000);
      }
      yield();
    }
 // }
}
