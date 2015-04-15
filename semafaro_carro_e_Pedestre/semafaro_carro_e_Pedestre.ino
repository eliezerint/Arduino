int const vermelhocarro = 1;
'

int bt = 9;

 int pedestre = 0;

void abresinal();
void fechasinal();
void abresinalpedestre();
void setup() {
  
  pinMode(vermelhocarro,OUTPUT);
  pinMode(amarelocarro,OUTPUT);
  pinMode(verdecarro,OUTPUT);
  pinMode(vermelhopedestre,OUTPUT);
  pinMode(verdepedestre,OUTPUT);
  
  
  
  digitalWrite(vermelhopedestre,HIGH);
  abresinal();
 
}

void loop() {
  
  pedestre = digitalRead(bt);
  switch(pedestre){
  case(0):abresinal();
         break;
  case(1):
     fechasinal();
    abresinalpedestre();
    abresinal();
    break;
  }

}


void abresinal(){
  
  pedestre = 0;
 digitalWrite(vermelhocarro,LOW);

    digitalWrite(verdecarro,HIGH);
  pedestre = digitalRead(bt);
   while (pedestre == 0 ) {
     
    pedestre = digitalRead(bt); 

   }
 
 
}



void fechasinal(){
 digitalWrite(verdecarro,LOW);
  digitalWrite(amarelocarro,HIGH);
  delay(4000);
   digitalWrite(amarelocarro,LOW);
    digitalWrite(vermelhocarro,HIGH);
  
}


void abresinalpedestre(){
     digitalWrite(vermelhopedestre,LOW);
     digitalWrite(verdepedestre,HIGH);
     
      delay(7000);
       digitalWrite(verdepedestre,LOW);
       for (int tempo; tempo < 50 ; tempo++){
          digitalWrite(vermelhopedestre,HIGH);
          delay(30);
          digitalWrite(vermelhopedestre,LOW);
       

       }  
         
         digitalWrite(vermelhopedestre,HIGH); 
          
          
          
         
     
  
  

}
