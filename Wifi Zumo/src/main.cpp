#include <Arduino.h>

// Load Wi-Fi library
#include <WiFi.h>

// Network credentials Here
const char* ssid     = "ESP32-Network";
const char* password = "Esp32-Password";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

//variables to store the current LED states
String statePin0 = "off";
String statePin4 = "off";
String statePinA1 = "off";
String statePinA2 = "off";
String statePinA3 = "off";
//Output variable to GPIO pins
const int ledPin0 = A0;
const int ledPin4 = A4;
const int ledPinA1 = A1;
const int ledPinA2 = A2;
const int ledPinA3 = A3;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin0, OUTPUT);      // Pin A0 to pin D0 on Arduino GREEN
  digitalWrite(ledPin0, 1);      // default pin to HIGH
  pinMode(ledPin4, OUTPUT);      // Pin A4 to pin D4 on Arduino ORANGE
  digitalWrite(ledPin4, 1);      // default pin to HIGH
  pinMode(ledPinA1, OUTPUT);     // Pin A1 to pin D1 on Arduino YELLOW
  digitalWrite(ledPinA1, 1);     // default pin to HIGH
  pinMode(ledPinA2, OUTPUT);     // Pin A2 to pin D2 on Arduino BROWN
  digitalWrite(ledPinA2, 1);     // default pin to HIGH
  pinMode(ledPinA3, OUTPUT);     // Pin A3 to pin D3 on Arduino WHITE
  digitalWrite(ledPinA3, 1);     // default pin to HIGH

  WiFi.softAP(ssid,password);

  // delay(7000);
  
  // Print IP address and start web server
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /0/on") >= 0) {
              statePin0 = "on";
              digitalWrite(ledPin0, LOW);               // turns the LED on
            } else if (header.indexOf("GET /0/off") >= 0) {
              statePin0 = "off";
              digitalWrite(ledPin0, HIGH);                //turns the LED off
            }
            
            if (header.indexOf("GET /4/on") >= 0) {
              statePin4 = "on";
              digitalWrite(ledPin4, LOW);               // turns the LED on
            } else if (header.indexOf("GET /4/off") >= 0) {
              statePin4 = "off";
              digitalWrite(ledPin4, HIGH);                //turns the LED off
            }
            
            if (header.indexOf("GET /1/on") >= 0) {
              statePinA1 = "on";
              digitalWrite(ledPinA1, LOW);               // turns the LED on
            } else if (header.indexOf("GET /1/off") >= 0) {
              statePinA1 = "off";
              digitalWrite(ledPinA1, HIGH);                //turns the LED off
            }
            
            if (header.indexOf("GET /2/on") >= 0) {
              statePinA2 = "on";
              digitalWrite(ledPinA2, LOW);               // turns the LED on
            } else if (header.indexOf("GET /2/off") >= 0) {
              statePinA2 = "off";
              digitalWrite(ledPinA2, HIGH);                //turns the LED off
            }
            
            if (header.indexOf("GET /3/on") >= 0) {
              statePinA3 = "on";
              digitalWrite(ledPinA3, LOW);               // turns the LED on
            } else if (header.indexOf("GET /3/off") >= 0) {
              statePinA3 = "off";
              digitalWrite(ledPinA3, HIGH);                //turns the LED off
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            client.println("<style>html { font-family: monospace; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: yellowgreen; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 32px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: gray;}");
            client.println(".grid-container { display: grid; grid-template-areas: '. a .' 'b center c' '. d .'; justify-content: center; align-items: center; }");
            client.println(".a { grid-area: a; }");
            client.println(".b { grid-area: b; }");
            client.println(".c { grid-area: c; }");
            client.println(".d { grid-area: d; }");
            client.println(".center { grid-area: center; }</style></head>");

            client.println("<body><h1>Zumo Drive Server</h1>");
            client.println("<p>Wifi Control for Zumo Robot</p>");

            client.println("<div class='grid-container'>");
            if (statePinA1 == "off") {
              client.println("<p class='b'><a href=\"/1/on\"><button class=\"button\">TURN LEFT</button></a></p>");
            } else {
              client.println("<p class='b'><a href=\"/1/off\"><button class=\"button button2\">turn left</button></a></p>");
            }
            if (statePinA2 == "off") {
              client.println("<p class='c'><a href=\"/2/on\"><button class=\"button\">TURN RIGHT</button></a></p>");
            } else {
              client.println("<p class='c'><a href=\"/2/off\"><button class=\"button button2\">turn right</button></a></p>");
            }
            if (statePin0 == "off") {
              client.println("<p class='a'><a href=\"/0/on\"><button class=\"button\">FORWARDS</button></a></p>");
            } else {
              client.println("<p class='a'><a href=\"/0/off\"><button class=\"button button2\">forwards</button></a></p>");
            }
            if (statePinA3 == "off") {
              client.println("<p class='center'><a href=\"/3/on\"><button class=\"button\">ARM ZUMO</button></a></p>");
            } else {
              client.println("<p class='center'><a href=\"/3/off\"><button class=\"button button2\">ZUMO ARMED</button></a></p>");
            }
            if (statePin4 == "off") {
              client.println("<p class='d'><a href=\"/4/on\"><button class=\"button\">BACKWARDS</button></a></p>");
            } else {
              client.println("<p class='d'><a href=\"/4/off\"><button class=\"button button2\">backwards</button></a></p>");
            }
            client.println("</div>");

            //////////////////// KEYDOWN EXPERIMENT
            // client.println("<script>");
            // client.println("document.body.addEventListener('keydown', function(event) {");
            // client.println("  var url;");
            // client.println("  switch(event.key) {");
            // client.println("    case 'ArrowLeft':");
            // client.println("      url = '/1/on';");
            // client.println("      break;");
            // client.println("    case 'ArrowRight':");
            // client.println("      url = '/2/on';");
            // client.println("      break;");
            // client.println("    case 'ArrowUp':");
            // client.println("      url = '/0/on';");
            // client.println("      break;");
            // client.println("    case 'ArrowDown':");
            // client.println("      url = '/4/on';");
            // client.println("      break;");
            // client.println("  }");
            // client.println("  if (url) {");
            // client.println("    fetch(url, { method: 'POST' });");
            // client.println("  }");
            // client.println("});");
            // client.println("</script>");
            //////////////////// KEYDOWN EXPERIMENT

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}