#include <Ultrasonic.h>

#include <LiquidCrystal.h>






LiquidCrystal lcd (11, 10, 5, 4, 3, 2);

Ultrasonic ultrasonic(12,13); // (Trig PIN,Echo PIN)

float distancia = 0;
long microsec = 0;
int luz = 9;

void setup() {
  Serial.begin(9600); 
 
   analogWrite(luz,150);
  lcd.begin( 16, 2);
  
  

   

}
void loop()
{
  /*digitalWrite(trigerPin,LOW);
  
  delayMicroseconds(2);
  
  digitalWrite(trigerPin,HIGH);
  
  delayMicroseconds(10);
  
   digitalWrite(trigerPin,LOW);
*/
   microsec = ultrasonic.timing();
   distancia = ultrasonic.convert(microsec, Ultrasonic::CM);

  
  int distanciacm = int(distancia);
  lcd.print(" Distancia "); // CM or INC
  lcd.setCursor(0,2);
  lcd.print(distanciacm );
  lcd.setCursor(5,2);
  lcd.print("Cm");
 
  
  
   delay(1000);
   lcd.clear();
 
}
