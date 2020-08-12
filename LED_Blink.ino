#include <DHT.h>
DHT MyDht(D3, DHT11); //pin to connect ,DHT11 or DHT22

void setup() {
  pinMode(D0, 1);
  pinMode(D4 ,1);
  Serial.begin(9600);
  MyDht.begin();
  
}

void loop() {
  int t = MyDht.readTemperature();
  int h = MyDht.readHumidity();
  Serial.println("TEMP = ");
  Serial.print(t);
  Serial.println("HUM = ");
  Serial.print(h);
  Serial.println(" ");
  delay(1000);
}
