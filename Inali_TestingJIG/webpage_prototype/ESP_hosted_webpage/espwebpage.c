#include <WiFi.h>

// Replace with your network credentials
const char *ssid = "Inali_Testing_JIG";
const char *password = "123456789";

// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;
void setup()
{
  Serial.begin(115200);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
  Serial.println("Server started");
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            /////////////////////////////////////////////////////////////////
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<title>Google Sheets API Test</title>");
            /////////////////////////////////SCRIPT///////////////////
            //Script

              // CSS
              client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");

          client.println(".button { background-color: #10c0e3; color: white; padding: 10px; border-radius: 20px; cursor: pointer; border: none; color: white; padding: 16px 40px;");

          client.println("text-decoration: none; font-size: 15px; margin: 2px; cursor: pointer;}");

          client.println(".button2 {background-color: #31d618; font-size:15px; border:none; color: white; padding: 10px; flex-direction:column; gap:1rem; border-radius: 20px; cursor:pointer;}");
          client.println(".button3 {background-color: #10c0e3; font-size:15px; border:none; color: white; padding: 10px; flex-direction:column; border-radius: 20px; cursor:pointer;{display:inline-block;}");

          client.println(".card {width: 10rem; height: 13rem; position: absolute; display: flex; flex-direction:column; gap:1rem; align-items: center; width: 10rem; text-align: center; background: rgba(224, 50, 50, 0.26); border: 7px solid red; box-shadow: var(--boxShasow); border-radius: 20px; padding: 0px 26px 3rem 26px;}");

          client.println(".button4 {background-color: #f00534; font-size:15px; border:none; color: white; padding: 10px; border-radius: 20px; cursor:pointer;}</style></head>");

          // HTML
          client.println("<p><img src=https://www.google.com/url?sa=i&url=https%3A%2F%2Finalifoundation.com%2F&psig=AOvVaw061auyqmjdOAsEp1S6s5Bi&ust=1673435216640000&source=images&cd=vfe&ved=0CBAQjRxqFwoTCKi-oI3uvPwCFQAAAAAdAAAAABAJ style=width:100></p>");
          client.println("<body><h1>Testing JIG</h1>");

          // Display current state, and ON/OFF buttons for GPIO 26
          client.println("<label>Name</label>");
          client.println("<p><input type=text class= form-control name=Name placeholder=Your_Name /></p>");

          client.println("<label>Batch_NO. </label>");
          client.println("<p><input type=text class= form-control name=Batch_NO. placeholder=Batch_NO. /></p>");

          client.println("<p><a><button class=\"button button\">Submit</button></a></p>");

          client.println("<p><a><button class=\"button button2\">New_Sheet</button></a></p>");
          client.println("<p><a><button class=\"button button3\">Previous_Sheet</button></a></p>");
          client.println("<p><a><button class=\"button button4\">Delete_Sheet</button></a></p>");

          client.println("</body></html>");

          // The HTTP response ends with another blank line
          client.println();
          // Break out of the while loo
          // Clear the header variable
          header = "";
          // Close the connection
          client.stop();
          Serial.println("Client disconnected.");
          Serial.println("");
          }
        }
      }
    }
  }
}