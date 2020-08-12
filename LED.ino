void setup() {
 pinMode(D0, 1);
 pinMode(D4, 1);
 pinMode(D2, 1);

}

void loop() {
  digitalWrite(D0,0);
  digitalWrite(D2,0);
  delay(1000);
  digitalWrite(D0,1);
  digitalWrite(D2,1);
  delay(1000);

}
