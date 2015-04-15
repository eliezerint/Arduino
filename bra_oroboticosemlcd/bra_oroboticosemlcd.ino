#include <Servo.h>

Servo servomotorobj ;
Servo servomotorobj1 ;
Servo servomotorobj2 ;



int const servo = 2;
int const servo1 = 3;
int const servo2 = 4 ;
int servograu = 0 ;
int servograu1 = 0 ;
int servograu2 = 0 ;

int const potenciometro = 0;
int const potenciometro1 = 1;
int const potenciometro2 = 2;

int vlpotenciometro = 0;
int vlpotenciometro1 = 0;
int vlpotenciometro2 = 0;


void setup() {
  Serial.begin(9600);

  


}

void loop() {
 

  vlpotenciometro = analogRead(potenciometro);
  
  vlpotenciometro1 = analogRead(potenciometro1);
  
  vlpotenciometro2 = analogRead(potenciometro2);
 
  
  servograu = map(vlpotenciometro, 0, 1023, 0, 150);
   
   servograu1 = map(vlpotenciometro1, 0, 1023, 5, 175);
   
   servograu2 = map(vlpotenciometro2, 0, 1023, 5, 175);
   
  servomotorobj1.attach(servo1);  
  servomotorobj.write(servograu);  
  
   servomotorobj.attach(servo); 
  servomotorobj1.write(servograu1);  
  
  servomotorobj2.attach(servo2); 
  servomotorobj2.write(servograu2);  
  

  
  delay(15);
  
}
