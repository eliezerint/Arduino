


void setup() {
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  

}

void loop() {
  
   if (Serial.available() > 0){
    int  valor = Serial.read();
    Serial.println(valor);
    if (valor == 49)
    digitalWrite(7,HIGH);
  else  digitalWrite(7,LOW);
   

  delay(1000);
   }  
}
