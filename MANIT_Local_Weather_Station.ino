#include <ESP8266WiFi.h>
#include <DHT.h>
DHT MyDht(D3, DHT11); //Pin which is used to Get data from DHT11 Sensor


const char* ssid = "Your SSID";
const char* password = "Your Password";

int buz = D0; // Buzzer connected to D0
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  MyDht.begin();
  pinMode(buz, OUTPUT);
  digitalWrite(buz, LOW);

  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  server.begin();  // Starts the Server
  Serial.println("Server started");

  Serial.print("IP Address of network: "); // Prints IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  int t = MyDht.readTemperature();
  int h = MyDht.readHumidity();
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("Waiting for new client");
  while(!client.available())
  {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value = LOW;
  if(request.indexOf("/buz=ON") != -1)
  {
    digitalWrite(buz, HIGH); // Turn ON buz
    value = HIGH;
  }
  if(request.indexOf("/buz=OFF") != -1)
  {
    digitalWrite(buz, LOW); // Turn OFF buz
    value = LOW;
  }

/*------------------HTML Page Creation---------------------*/

  client.println("HTTP/1.1 200 OK"); // standalone web server with an ESP8266
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("buz: ");
 
  if(value == HIGH)
  {
    client.print("ON");
  }
  else
  {
    client.print("OFF");
  }
  client.println("<br><br>");
  client.print("<h3 style = \"color:green\">Temperature:");
  client.print(t);
  client.print("</h3>")
  client.print("<h3 style = \"color:green\">Humidity:");
  client.print(h);
  client.print("</h3>")
  client.println("<br><br>");
  client.println("<a href=\"/buz=ON\"\"><button>ON</button></a>");
  client.println("<a href=\"/buz=OFF\"\"><button>OFF</button></a><br />");
  client.println("</html>");
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
