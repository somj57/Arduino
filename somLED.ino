#include <ESP8266WiFi.h>
//#include <DHT.h>    //dht liberary ha jo ke temperature or humidity ke liye kam aate ha 
//DHT MyDht(D3, DHT11); //Pin which is used to Get data from DHT11 Sensor


const char* ssid = "Som";              //yaha wifi ka name dal dena 
const char* password = "11111111";     //yaha password

int buz = D2; // Buzzer connected to D0  //is pin se input jayaga relay ka
WiFiServer server(80);    //ye wifi me nodemcu ko server banana ke liye ha

void setup()
{
  pinMode(D4, 1); 
  Serial.begin(115200);
  //MyDht.begin();
  pinMode(buz, OUTPUT);
  digitalWrite(buz, HIGH);
  digitalWrite(D4, 1);
  
 
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)      //wl connected batata ha agr nodemcu me koi clint aaya ha ky
  {
   // digitalWrite(D4, 1);
    delay(500);
   // digitalWrite(D4, 0);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  server.begin();  // Starts the Server
  Serial.println("Server started");

  Serial.print("IP Address of network: "); // Prints IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  //Serial.println("/");
/*  digitalWrite(buz, HIGH);
  delay(1000);
  digitalWrite(buz, LOW); */
  digitalWrite(D4,0);    //ye maine isliye use kiya ha taki mirko agr serial monitor na mile to light glow ho jayage ke wifi connected ha 
  
}

void loop()
{
  int t = 0;
  int h = 0;
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

  String request = client.readStringUntil('\r');     //ye button me jo data ha vo read kr leha jo herf tag se aayaga
  Serial.println(request);
  client.flush();

  int value = LOW;
  if(request.indexOf("/buz=ON") != -1)
  {
    digitalWrite(buz, LOW); // Turn ON buz
    value = HIGH;
  }
  if(request.indexOf("/buz=OFF") != -1)
  {
    digitalWrite(buz, HIGH); // Turn OFF buz
    value = LOW;
  }

/*------------------HTML Page Creation---------------------*/

  client.println("HTTP/1.1 200 OK"); // standalone web server with an ESP8266
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<center>SOMYA JAISWAL<\center>");
  client.println("LIGHTS ONLINE");
  client.println("<br>");
  client.println("LIGHTS : ");
 
  if(value == HIGH)
  {
    client.print("ON");
  }
  else
  {
    client.print("OFF");
  }
  client.println("<br><br>");
 
  client.println("<br><br>");
  client.println("<a href=\"/buz=ON\"\"><button>ON</button></a>");
  client.println("<br><br><br>");
  client.println("<a href=\"/buz=OFF\"\"><button>OFF</button></a><br />");
  client.println("</html>");
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
