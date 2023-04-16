//#include<WiFi.h>

#include <ESP8266WiFi.h>


void setup() {
  Serial.begin(9600);
  pinMode(D2, INPUT);
  pinMode(D1, INPUT);
  pinMode(16, OUTPUT);
}

void loop() {

  int val = digitalRead(D2);

  if (val == 1) {
    Serial.println("Input1 is ok");
    digitalWrite(16, LOW);
  }
  else {
    Serial.println("continuity of input1 is not found");
    digitalWrite(16, HIGH);
  }

   int val2 = digitalRead(D1);

  if (val2 == 1) {
    Serial.println("Input2 is ok");
    digitalWrite(16, LOW);
  }
  else {
    Serial.println("continuity of input2 is not found");
    digitalWrite(16, HIGH);
  }
}
