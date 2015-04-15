int speakerPin = 6;
  //
int tamanho = 15; // numeros de notas
char notes[] = "ccggaagffeeddbcdcecdce ";//espaços pausa
int batida[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

void playTone(int tone, int duration) {
    for (long x = 0; x < duration * 1000L; x += tone * 2) {
      digitalWrite(speakerPin,HIGH);
      delayMicroseconds(tone);
      digitalWrite(speakerPin, LOW);
      delayMicroseconds(tone);
    }
}

void playNote (char note , int duration) {
   char names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
   int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
   
   for (int x = 0; x < 20 ; x++){
    if (names[x] == note) {
        playTone(tones[x],duration);
        
    } 
   
   }
} 

void setup() {
  pinMode(speakerPin,OUTPUT);

}

void loop() {
  
  for (int x = 0; x < tamanho; x++){
    if (notes[x] == ' '){
       delay(batida[x] * tempo);// rest
    } else {
       playNote(notes[x], batida[x] * tempo );
       
    }
     // pausa entre as notas
    delay(tempo /2);
  }
}

