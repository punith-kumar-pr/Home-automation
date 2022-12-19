#include <ESP8266WiFi.h>
const char* ssid     = "go";
const char* password = "asdfghjkl";
Wifiserver server(80);
String header;
String output5state = "off";
String output4state = "off";
const int output5 = 5;
const int output4 = 4;

char junk;
String inputstring="";
#define led 5  // d7
#include<SoftwareSerial.h>

SoftwareSerial PS(3, 1);//(rx,tx)

void setup()                    // run once, when the sketch starts
{
Serial.begin(115200);            // set the baud rate to 9600, same should be of your Serial Monitor
 pinMode(led, OUTPUT);
 pinMode(1, FUNCTION_3); 
pinMode(3, FUNCTION_3);
PS.begin(9600);

  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Wifi.begin(ssid, password);
  while (wifi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("wifi connected.");
  Serial.println("IP address: ");
  Serial.println(wifi.localip());
  Server.begin();

}

void loop()
{
  If(PS.available()){
  While(PS.available())
{
      Char inchar = (char)PS.read(); 
      Inputstring += inchar;        
}
    Serial.println(inputstring);
    While (PS.available() > 0)  
    { junk = PS.read() ; }      
    If(inputstring == "A"){      
      Digitalwrite(led, HIGH);
       
    }else if(inputstring == "a"){  
      Digitalwrite(led, LOW);}
      Inputstring = "";
  }
Wificlient client = server.available();   // Listen for incoming clients

  If (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentline = "";                // make a String to hold incoming data from the client
    While (client.connected()) {            // loop while the client's connected
      If (client.available()) {             // if there's bytes to read from the client,
        Char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        Header += c;
        If (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          If (currentline.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            Client.println("HTTP/1.1 200 OK");
            Client.println("Content-type:text/html");
            Client.println("Connection: close");
            Client.println();
            
            // turns the gpios on and off
            If (header.indexof("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              Output5state = "on";
              Digitalwrite(output5, HIGH);
            } else if (header.indexof("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              Output5state = "off";
              Digitalwrite(output5, LOW);
            } else if (header.indexof("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              Output4state = "on";
              Digitalwrite(output4, HIGH);
            } else if (header.indexof("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              Output4state = "off";
              Digitalwrite(output4, LOW);
            }
            
            // Display the HTML web page
            Client.println("<!DOCTYPE html><html>");
            Client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            Client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            Client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            Client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            Client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            Client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            Client.println("<body><h1>Home Automation Control Page</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            Client.println("<p>GPIO 5 - State " + output5state + "</p>");
            // If the output5state is off, it displays the ON button       
            If (output5state=="off") {
              Client.println("<p><ahref=\"/5/on\"><buttonclass=\"button\">ON</button></a></p>");
            } else {
              Client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            Client.println("<p>GPIO 4 - State " + output4state + "</p>");
            // If the output4state is off, it displays the ON button       
            If (output4state=="off") {
              Client.println("<p><ahref=\"/4/on\"><buttonclass=\"button\">ON</button></a></p>");
            } else {
              Client.println("<p><ahref=\"/4/off\"><buttonclass=\"buttonbutton2\">OFF</button></a></p>");
            }
            Client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            Client.println();
            // Break out of the while loop
            Break;
          } else { // if you got a newline, then clear currentline
            Currentline = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          Currentline += c;      // add it to the end of the currentline
        }
      }
    }
    // Clear the header variable
    Header = "";
    // Close the connection
    Client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }  
}
