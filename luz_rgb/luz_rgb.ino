int redpin=8;      
int greenpin=6;    
int bluepin=7;      
int var=0;
int var1=0;

void cores( int cor ){
  if ( cor == 1 ) {
  for(var1=250;var1<255;var1++){
  analogWrite(bluepin,200);   //roxo
  analogWrite(greenpin,0);
  analogWrite(redpin,250); 
  delay(10);
   }
  }
 if ( cor == 2 ){
   for(var1=250;var1<255;var1++){
     analogWrite(redpin,200);  // vermelho
    analogWrite(greenpin,0); 
    delay(1000);
   }
 }
  if ( cor == 3 ){
   for(var1=250;var1<255;var1++){
     analogWrite(redpin,14);    //verde
  analogWrite(greenpin,200); 
  delay(1000);
   }
 }
 if ( cor == 4 ){
   for(var1=250;var1<255;var1++){
   analogWrite(greenpin,0);   //Azul escuro
  analogWrite(bluepin,var);
   analogWrite(bluepin,var1);
  delay(1000);
   }
 }
 if ( cor == 5 ){
   for(var1=250;var1<255;var1++){
  analogWrite(greenpin,60);  //Amarelo
  analogWrite(bluepin,120);
  analogWrite(redpin,150);
  delay(1000);
   }
 }
 if ( cor == 6 ){
   for(var1=250;var1<255;var1++){
  analogWrite(bluepin,150);
  delay(1);  //rosa
  analogWrite(redpin,255);
  analogWrite(bluepin,0);
  delay(1);
  analogWrite(greenpin,200); 
  analogWrite(redpin,0);
  analogWrite(bluepin,150);
  delay(1);
  analogWrite(redpin,100);
  
   }
 }
   
  if ( cor == 6 ){
  
  
  
  analogWrite(greenpin,200);//branca
  
   
 }


}


int op = 0;

void setup()

{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available () > 0 ) {
    op = Serial.read();
  }
  

 cores(1);
 delay(1000);
 Serial.println(op);
 }
 


  
  

