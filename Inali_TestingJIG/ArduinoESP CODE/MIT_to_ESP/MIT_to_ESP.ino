#include <ESP8266WiFi.h>
// Set WiFi credentials
#define WIFI_SSID "IF Foundation"
#define WIFI_PASS "inalihelloxyz@123"

// Set AP credentials
#define AP_SSID "ESP8266"
#define AP_PASS "123"

WiFiServer ESPserver(80);

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
  Serial.println("");
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
  ESPserver.begin();

} // void setup()

void loop()
{

  // Check if a client has connected
  WiFiClient client = ESPserver.available();
  if (!client)
  {
    return;
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');

  Serial.println(request);
  client.flush();

  if (request.indexOf("LEDON") > 0)
  {
    digitalWrite(LED_Pin, LOW);
  }
  else if (request.indexOf("LEDOFF") > 0)
  {
    digitalWrite(LED_Pin, HIGH);
  }

  delay(5);
}
