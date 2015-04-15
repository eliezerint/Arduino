//Constante que representa o pino onde o positivo do led será ligado.
const int ledVermelho = 10;

//Controladores do efeito de fader
int brilho = 0;
int fader = 1;
boolean acende = true;
boolean apaga = false;


int potenciometro = 2; // define o pino do arduino em qual o pino esta conectado
int tempoDeEspera = 0; //variavel que ira receber o valor do potenciometro
int ledVerde = 12; //define o pino do arduino que o led esta conectado

void setup() {
   Serial.begin(9600);
  pinMode(ledVerde,OUTPUT);
  //Definindo o pino led como de saída.
  pinMode(ledVermelho,OUTPUT);
 
 //DEFIININDO A PORTA
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  
}

void loop() {
  
   analogWrite(ledVermelho,brilho);  
  
  //Processo de acendimento do led usando o efeito fader.
  if (acende == true) {
    if (brilho < 255) {
      brilho = brilho + fader; //aumentando o brilho do led.
    } else {     
      acende = false;
      apaga = true;
    }
  }

  //Processo para apagar o led com efeito fader.  
  if (apaga == true) {
    if (brilho > 0) {
      brilho = brilho - fader; // diminuindo o brilho do led.
    } else {
      acende = true;
      apaga = false;
    }
  }
  
  delay(90);

  
  //PORTA DIGITAL
 
  
   /*digitalWrite(7,HIGH);
  delay(100);
  digitalWrite(7,LOW);
  delay(100);
   digitalWrite(5,HIGH);
  delay(100);
  digitalWrite(5,LOW);
 
  digitalWrite(4,HIGH);
  delay(100);
  digitalWrite(4,LOW);
  delay(100);
  
  digitalWrite(4,LOW);
  digitalWrite(4,LOW);
  digitalWrite(10,LOW);
  
    tempoDeEspera = analogRead(potenciometro); //Recebe o valor do potenciômetro
      digitalWrite(ledVerde, HIGH);
     delay(tempoDeEspera);
    digitalWrite(ledVerde, LOW);
    delay(tempoDeEspera);
    
      if(tempoDeEspera > 0)
    analogWrite(ledVerde, (tempoDeEspera/4)); //Acende o led com intensidade proporcional ao valor obtido
    Serial.println(tempoDeEspera); //Mostra no Serial Monitor o valor obtido do potenciômetro
      
  */
  

}
