

#include <ESP8266WiFi.h>

//const char* ssid = "DELL";//type your ssid
//const char* password = "div12345";//type your password

const char* ssid = "DELL";//type your ssid
const char* password = "div12345";//type your password

int ledPin = 2; // GPIO2 of ESP8266
WiFiServer ESPserver(255);//Service Port

void setup() 
{
Serial.begin(115200);
pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, LOW);

Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);
/*
 The following four line of the 
 code will assign a Static IP Address to 
 the ESP Module. If you do not want this, 
 comment out the following four lines.  
 */
//IPAddress ip(192,168,1,254);   
//IPAddress gateway(192,168,1,1);   
//IPAddress subnet(255,255,255,0);   
//WiFi.config(ip, gateway, subnet);

delay(5000);

while (WiFi.status() != WL_CONNECTED) 
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
ESPserver.begin();
Serial.println("Server started");

// Print the IP address
Serial.print("Enter this URL to control ESP8266: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println(":255"); //"/255" is the Server Port. 
}

void loop() 
{
// Check if a client has connected
WiFiClient client = ESPserver.available();
if (!client) 
{
return;
}

// Wait until the client sends some data
Serial.println("new client");
while(!client.available())
{
delay(1);
}

// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

// Match the request

int value = LOW;
if (request.indexOf("/LED=ON") != -1) 
{
Serial.println("LED is ON");
digitalWrite(ledPin, HIGH);
value = HIGH;
} 
if (request.indexOf("/LED=OFF") != -1)
{
Serial.println("LED is OFF");
digitalWrite(ledPin, LOW);
value = LOW;
}

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); //  IMPORTANT
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.print("<center>WELCOME TO YOUR IOT BASED HOME AUTOMATION SYSTEM</center>");
client.print("<center>Status of the LED: </center>");

if(value == HIGH) 
{
client.print("<center>ONs</center>");  
} 
else 
{
client.print("OFF");
}
client.println("<br><br>");
client.println("Click <a href=\"/LED=ON\">here</a> to turn ON the LED<br>");
client.println("Click <a href=\"/LED=OFF\">here</a> to turn OFF the LED<br>");
client.println("</html>");

delay(1);
Serial.println("Client disconnected");
Serial.println("");
}
