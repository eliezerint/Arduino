
#include <Servo.h>

Servo motor ;



int motorpin = 3;

int potenciometropin = 0;


int vlpotenciometro = 0 ;

int buzzer = 6;

void setup() {
  
  Serial.begin (9600);
  
  motor.attach(motorpin);
  

}

void loop(){
  
  vlpotenciometro =analogRead(potenciometropin);
 

 Serial.println(vlpotenciometro);
 
 vlpotenciometro = map(vlpotenciometro,0 ,1023, 0,180);
 
  Serial.println(vlpotenciometro);
  
 
  
  motor.write(vlpotenciometro);
  
  delay(15);
  
   
 
 
  
}
