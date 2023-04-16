#include <ESP8266WiFi.h>
// Set WiFi credentials
#define WIFI_SSID "IF Foundation"
#define WIFI_PASS "inalihelloxyz@123"

// Set AP credentials
#define AP_SSID "ESP8266"
#define AP_PASS "123"

WiFiServer server(80);

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
String html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='LED ON' ></form><br>";
String html_3 = "<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>";
String html_4 = "</div></body></html>";

String request = "";
int LED_Pin = D0;

void setup()
{
  pinMode(LED_Pin, OUTPUT);
  Serial.begin(115200);
  Serial.println();

  // Begin Access Point
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(AP_SSID, AP_PASS);

  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println();
  Serial.println("Connected!");
  Serial.print("IP address for network ");
  Serial.print(WIFI_SSID);
  Serial.print(" : ");
  Serial.println(WiFi.localIP());
  Serial.print("IP address for network ");
  Serial.print(AP_SSID);
  Serial.print(" : ");
  Serial.print(WiFi.softAPIP());

  // boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();

} // void setup()

void loop()
{

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Read the first line of the request
  request = client.readStringUntil('\r');

  if (request.indexOf("LEDON") > 0)
  {
    digitalWrite(LED_Pin, LOW);
  }
  else if (request.indexOf("LEDOFF") > 0)
  {
    digitalWrite(LED_Pin, HIGH);
  }

  client.flush();

  client.print(header);
  client.print(html_1);
  client.print(html_2);
  client.print(html_3);
  client.print(html_4);

  delay(5);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
}