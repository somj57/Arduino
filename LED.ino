//For this to work you need to have node mcu 
//For Arduino you need to change pin number to respective pin number |
void setup() {  //                                                   |
 pinMode(D0, 1);//<--------------------------------------------------                                                     
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
