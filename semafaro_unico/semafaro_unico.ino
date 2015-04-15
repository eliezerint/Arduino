int const Vermelho = 2;
int const Vermelho1 =  3;
int const Vermelho2 = 4;
int const Vermelho3 = 5;
int const Verde = 6;


int  tempo = 0;




void setup() {
  pinMode(Vermelho,OUTPUT); 
  pinMode(Vermelho1,OUTPUT);  
  pinMode(Vermelho2,OUTPUT);  
  pinMode(Vermelho3,OUTPUT);
  pinMode(Verde,OUTPUT); 
  

 

}

void loop() {
  
  digitalWrite(Vermelho,HIGH);
  
 delay(1500);
 
 digitalWrite(Vermelho,LOW);
 digitalWrite(Vermelho1,HIGH);
  
 delay(1500);
 
 
 digitalWrite(Vermelho1,LOW);
 digitalWrite(Vermelho2,HIGH);
  
 delay(1500);
 
 
 digitalWrite(Vermelho2,LOW);
 
  
 delay(1500);
 
 tempo = 0;
   while (tempo < 10){
   digitalWrite(Vermelho3,HIGH);
   delay(500);
   digitalWrite(Vermelho3,LOW);
   delay(500);
   tempo++ ;
   }
 
  digitalWrite(Vermelho3,LOW);
  
  
 
   
   tempo = 0; 
    
  while  (tempo < 10) {
   digitalWrite(Verde,HIGH);
   delay(500);
   digitalWrite(Verde,LOW);
   tempo++ ;
   delay(500);
    
  }
  digitalWrite(Verde,LOW);
  
  
   
}





