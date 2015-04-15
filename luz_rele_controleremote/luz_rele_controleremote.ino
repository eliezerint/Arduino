#include <IRremote.h>




int RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();

}

void loop() {
  
   if (irrecv.decode(&results)){
    Serial.println(results.value);
    irrecv.resume();
    
   }
    
    if(results.value == 5316027){
      ligar();
     
    }
  else desligar();
  delay(1000);
    
}

void desligar(){
  digitalWrite(7,LOW);
  
}

void ligar(){
  digitalWrite(7,HIGH);
  
}
  
