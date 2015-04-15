void setup() {
 
 //DEFIININDO A PORTA
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop() {
  //PORTA DIGITAL
  digitalWrite(5,HIGH);
  delay(1000);
  digitalWrite(5,LOW);
 
  digitalWrite(7,HIGH);
  delay(1000);
  digitalWrite(7,LOW);
  delay(1000);
  
  

}
