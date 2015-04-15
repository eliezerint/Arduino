#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN A12     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
#define BAUD_RATE 9600
#define TERM_CHAR '\n'
#define BUF_LEN  30


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 1, 177 };         // ip in lan
byte gateway[] = { 192, 168, 1, 254 };         // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                                   //server port
byte sampledata=50;            //some sample data - outputs 2 (ascii = 50 DEC)

float h; //A aquisição dessa informação demora 1 seg , então colocar isto no loop principal afeta o desempenho do programa
float t;
int i;
int count=0;
boolean DispAlarme = false;
boolean FlagAlarme = false;
boolean AIMode = false;
char c;
String readString = String(BUF_LEN); //string for fetching data from address


// O moises é uma bichinha deslumbrada e colocou tudo em inglês

int ContatoSecoState1 = 0;        // variable for reading the status
int ContatoSecoState2 = 0;        // variable for reading the status
int ContatoSecoState3 = 0;        // variable for reading the status
int ContatoSecoState4 = 0;        // variable for reading the status
int ContatoSecoState5 = 0;        // variable for reading the status
int ContatoSecoState6 = 0;        // variable for reading the status
int ContatoSecoState7 = 0;        // variable for reading the status
int ContatoSecoState8 = 0;        // variable for reading the status

int optoacopladorState1 = 0;        // variable for reading the status
int optoacopladorState2 = 0;        // variable for reading the status


const int rele1 =  22;      // Rele 1 PA0 
const int rele2 =  23;      // Rele 2 PA1 
const int rele3 =  24;      // Rele 3 PA2 
const int rele4 =  25;      // Rele 4 PA3 
const int rele5 =  26;      // Rele 5 PA4 
const int rele6 =  27;      // Rele 6 PA5 
const int rele7 =  28;      // Rele 7 PA6 
const int rele8 =  29;      // Rele 8 PA7 
const int rele9 =  42;      // Rele 8 PA7 
const int rele10 =  43;      // Rele 8 PA7 

const int contatoseco8 = 41;    // the number of the pushbutton pin
const int contatoseco7 = 40;    // the number of the pushbutton pin
const int contatoseco6 = 49;    // the number of the drybutton pin
const int contatoseco5 = 48;    // the number of the drybutton pin
const int contatoseco4 = 47;    // the number of the drybutton pin
const int contatoseco3 = 46;    // the number of the drybutton pin
const int contatoseco2 = 45;    // the number of the drybutton pin
const int contatoseco1 = 44;    // the number of the drybutton pin


const int optoacopladorbutton1 = 18;    // optobutton detectar 12v 
const int optoacopladorbutton2 = 19;    // optobutton detectar 12v
const int Sirene = 33;    //Saida de 12 volts Até 1,5A
const int Discadora = 32;  //Saida de 12 volts até 1A  

LiquidCrystal lcd(39, 38, 34, 35, 36, 37);

void setup(){
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print("SIS Versao V4");
  
  pinMode(rele1, OUTPUT); 
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT); 
  pinMode(rele4, OUTPUT);
  pinMode(rele5, OUTPUT); 
  pinMode(rele6, OUTPUT);
  pinMode(rele7, OUTPUT); 
  pinMode(rele8, OUTPUT);
  pinMode(rele9, OUTPUT); 
  pinMode(rele10, OUTPUT);
  pinMode(Discadora, OUTPUT);
  pinMode(Sirene, OUTPUT);

  
  pinMode(contatoseco6, INPUT);  
  pinMode(contatoseco5, INPUT);  
  pinMode(contatoseco4, INPUT);  
  pinMode(contatoseco3, INPUT);
  pinMode(contatoseco2, INPUT);  
  pinMode(contatoseco1, INPUT);
  pinMode(contatoseco2, INPUT);  
  pinMode(contatoseco1, INPUT);

  pinMode(optoacopladorbutton1, INPUT);
  pinMode(optoacopladorbutton2, INPUT);
  
//start Ethernet
  //ip[0] = 192;//EEPROM.read(0);
  //ip[1] = 168;//EEPROM.read(1);
  //ip[2] = 1;///EEPROM.read(2);
  //ip[3] = 177;//EEPROM.read(3);
  Ethernet.begin(mac, ip, gateway, subnet);

//enable serial datada print
  Serial.begin(9600);
  Serial2.begin(9600); //Porta bluetooth
  Serial3.begin(9600); //Porta Xbee
  // Todas as portas declaradas aqui aconseguem acionar reles com o seguinte comando _r1on e _r1off para o rele 2 _r2on e _r2off e assim por diante
}
 
void loop(){
  
  leserial();
  rede();
  count++;
  
  if(count == 1000){
  h = dht.readHumidity(); //A aquisição dessa informação demora 1 seg , então colocar isto no loop principal afeta o desempenho do programa
  t = dht.readTemperature(); // Mesma regra
  lcd.setCursor(0,1);
  lcd.print("RH:     ");
  lcd.setCursor(4,1);
  lcd.print(h);
  
  
  lcd.setCursor(8,1);
  lcd.print("Temp:      ");
  lcd.setCursor(13,1);
  lcd.print(t);
  count=0;
  }
              if(readString.indexOf("r1on") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele1, HIGH);    // set the LED on
            Serial.println("Ligando Rele 1");
            Serial3.println("Ligando Rele 1");
            Serial.println(readString);
          }
              if(readString.indexOf("r1off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele1, LOW);    // set the LED on
            Serial.println("Desligando Rele 1");
            Serial3.println("Desligando Rele 1");
            Serial.println(readString);
          }
              if(readString.indexOf("r2on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele2, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 2");
            Serial3.println("Ligando Rele 2");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r2off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele2, LOW);    // set the LED on
            Serial.println("Desligando Rele 2");
            Serial3.println("Desligando Rele 2");
            Serial.println(readString);
          }
          if(readString.indexOf("r3on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele3, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 3");
            Serial3.println("Ligando Rele 3");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r3off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele3, LOW);    // set the LED on
            Serial.println("Desligando Rele 3");
            Serial3.println("Desligando Rele 3");
            Serial.println(readString);
          }
            if(readString.indexOf("r4on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele4, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 4");
            Serial3.println("Ligando Rele 4");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r4off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele4, LOW);    // set the LED on
            Serial.println("Desligando Rele 4");
            Serial3.println("Desligando Rele 4");
            Serial.println(readString);
          }
          
            if(readString.indexOf("r5on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele5, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 5");
            Serial3.println("Ligando Rele 5");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r5off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele5, LOW);    // set the LED on
            Serial.println("Desligando Rele 5");
            Serial3.println("Desligando Rele 5");
            Serial.println(readString);
          }
          
            if(readString.indexOf("r6on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele6, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 6");
            Serial3.println("Ligando Rele 6");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r6off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele6, LOW);    // set the LED on
            Serial.println("Desligando Rele 6");
            Serial3.println("Desligando Rele 6");
            Serial.println(readString);
          }
            if(readString.indexOf("r7on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele7, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 7");
            Serial3.println("Ligando Rele 7");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r7off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele7, LOW);    // set the LED on
            Serial.println("Desligando Rele 7");
            Serial3.println("Desligando Rele 7");
            Serial.println(readString);
          }
            if(readString.indexOf("r8on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele8, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 8");
            Serial3.println("Ligando Rele 8");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r8off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele8, LOW);    // set the LED on
            Serial.println("Desligando Rele 8");
            Serial3.println("Desligando Rele 8");
            Serial.println(readString);
          }
            if(readString.indexOf("r9on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele9, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 9");
            Serial3.println("Ligando Rele 9");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r9off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele9, LOW);    // set the LED on
            Serial.println("Desligando Rele 9");
            Serial3.println("Desligando Rele 9");
            Serial.println(readString);
          }
            if(readString.indexOf("r10on") >0)//replaces if(readString.contains("L=1"))
          {    
            digitalWrite(rele10, HIGH);    // set the LED OFF        
            Serial.println("Ligando Rele 10");
            Serial3.println("Ligando Rele 10");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r10off") >0)//replaces if(readString.contains("L=1"))
          {
            //led has to be turned ON
            digitalWrite(rele10, LOW);    // set the LED on
            Serial.println("Desligando Rele 10");
            Serial3.println("Desligando Rele 10");
            Serial.println(readString);
          }
////////////////////////////Aciona sirene ou dicadora ////////////////////////////////////////////


          if(readString.indexOf("all=Ativar+Alarme") >0)//replaces if(readString.contains("L=1"))
          {
            FlagAlarme = true;
            lcd.setCursor(0,1);
            lcd.print(" Alarme Ativado ");
            //delay(10000);
          }
          if(readString.indexOf("all=Desativar+Alarme") >0)//replaces if(readString.contains("L=1"))
          {
            FlagAlarme = false;
            DispAlarme = false;
            digitalWrite(Discadora, LOW); 
            digitalWrite(Sirene, LOW);
            lcd.setCursor(0,1);
            lcd.print(" Alarme Desativado ");
            
          }
          if(readString.indexOf("all=DiscadoraON") >0)//replaces if(readString.contains("L=1"))
          {
            digitalWrite(Discadora, HIGH);
          }
          if(readString.indexOf("all=DiscadoraOff") >0)//replaces if(readString.contains("L=1"))
          {
            digitalWrite(Discadora, LOW);
          }
          
          if (FlagAlarme == true){
            le_sensores();          
  
      
            if (DispAlarme == true){ 
            digitalWrite(Sirene, HIGH);    // set the LED on
            digitalWrite(Discadora, HIGH);
            lcd.setCursor(0,1);
            lcd.print("Falha na Seguranca");
            
            }
            }
//Teste de opto acopladores detectam 9~12v podem ser usados tambem como zonas de alarmes principalmente para sensores de portas e janelas
        optoacopladorState1 = digitalRead(optoacopladorbutton1);
        optoacopladorState2 = digitalRead(optoacopladorbutton2);
        
            if(optoacopladorState1 == 0){
              lcd.setCursor(0,1);
            lcd.print("12v entrada 1");              
            }
            if(optoacopladorState2 == 0){
              lcd.setCursor(0,1);
            lcd.print("12v entrada 2");              
            }
            
//////////////////////////////////////////////////////////////////////////////////////////////////////          
          readString=""; //limpa a string depois de testa-la
 } //loop
 
////////////////////////////////////////////////////////////////////////////////////////////////////// 
//Função Alarme UP
void le_sensores(){
  ContatoSecoState1 = digitalRead(contatoseco1);
  ContatoSecoState2 = digitalRead(contatoseco2);
  ContatoSecoState3 = digitalRead(contatoseco3);
  ContatoSecoState4 = digitalRead(contatoseco4);
  ContatoSecoState5 = digitalRead(contatoseco5);
  ContatoSecoState6 = digitalRead(contatoseco6);
  ContatoSecoState7 = digitalRead(contatoseco7);
  ContatoSecoState8 = digitalRead(contatoseco8);
  
  if (ContatoSecoState1 == LOW){
      DispAlarme = true;
  } 
  
  if (ContatoSecoState2 == LOW){
      DispAlarme = true;
  } 
  if (ContatoSecoState3 == LOW){
      DispAlarme = true;
  } 
  
  if (ContatoSecoState4 == LOW){
      DispAlarme = true;
  } 
  if (ContatoSecoState5 == LOW){
      DispAlarme = true;
  } 
  if (ContatoSecoState6 == LOW){
      DispAlarme = true;
  }
  if (ContatoSecoState7 == LOW){
      DispAlarme = true;
  } 
  if (ContatoSecoState8 == LOW){
      DispAlarme = true;
  }  
  
}


//Função lê serial
void leserial(){
  // read incoming message
 while(Serial.available()){
    c = (char) Serial.read();
    if (readString.length() < 100)
      {
        //store characters to string
        readString += c; //replaces readString.append(c);
      }
    delay(1); // wait for another byte  
  }
  while(Serial2.available()){
    c = (char) Serial2.read();
    if (readString.length() < 100)
      {
        //store characters to string
        readString += c; //replaces readString.append(c);
      }
    delay(1); // wait for another byte  
  }
    while(Serial3.available()){
    c = (char) Serial3.read();
    if (readString.length() < 100)
      {
        //store characters to string
        readString += c; //replaces readString.append(c);
      }
    delay(1); // wait for another byte  
  }
  
}  
/////////////////////////////////////////////////////////////////////////////////////////////////////////  
//Função que recebe string do navegador 
 void rede(){
  // Create a client connection
EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
  if (client.available()) {
    c = client.read();
    //read char by char HTTP request
    if (readString.length() < 100)
      {
        //store characters to string
        readString += c; //replaces readString.append(c);
      }
        //output chars to serial port
      
        //if HTTP request has ended
        if (c == '\n') {
          //dirty skip of "GET /favicon.ico HTTP/1.1"
          if (readString.indexOf("?") <0)
          {
            //skip everything
          }
          //else
            //--------------------------HTML------------------------          
client.println("HTTP/1.1 200 OK");

client.println("Content-Type: text/html");

client.println();

client.print("<html><head>");

client.print("<title>Arduino Webserver Poldi</title>");

client.println("</head>");

client.print("<body bgcolor='#444444'>");

//---Überschrift---
client.println("<br><hr />");

client.println("<h1><div align='center'><font color='#2076CD'>Arduino Webserver 1.0 by Mijja</font color></div></h1>");

client.println("<hr /><br>");
//---Überschrift---

//---Ausgänge schalten---
client.println("<div align='left'><font face='Verdana' color='#FFFFFF'>Painel de Controle WEB:</font></div>");

client.println("<br>");

client.println("<div align='left'><font face='Verdana' color='#FFFFFF'>Temperatura:");
client.print(t);
client.println("</font></div>");

client.println("<div align='left'><font face='Verdana' color='#FFFFFF'>Umidade:");
client.print(h);
client.println("</font></div>");

client.println("<br>");

client.println("<table border='1' width='100%' cellpadding='5'>");

client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Sala<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r1on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r1off value='Apagar'></form></td>");


if (digitalRead(rele1)==HIGH)
  client.println("<td align='center'><font color='green' size='5'>LIG");
else
client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");

client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Cozinha<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r2on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r2off value='Apagar'></form></td>");

if (digitalRead(rele2) == HIGH)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Garagem<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r3on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r3off value='Apagar'></form></td>");

if (digitalRead(rele3) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Suite<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r4on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r4off value='Apagar'></form></td>");

if (digitalRead(rele4) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Quarto<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r5on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r5off value='Apagar'></form></td>");

if (digitalRead(rele5) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Banheiro Suite<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r6on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r6off value='Apagar'></form></td>");

if (digitalRead(rele6) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Escritorio<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r7on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r7off value='Apagar'></form></td>");

if (digitalRead(rele7) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Banheiro<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r8on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r8off value='Apagar'></form></td>");

if (digitalRead(rele8) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Portão Social<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r9on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r9off value='Apagar'></form></td>");

if (digitalRead(rele9) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Portão Garagem<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r10on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r10off value='Apagar'></form></td>");

if (digitalRead(rele10) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
client.println("</tr>");

client.println("</table>");


client.println("<br>");

if (FlagAlarme == 0)
client.println("<form method=get><input type=submit name=all value='Ativar Alarme'></form>");
else
client.println("<form method=get><input type=submit name=all value='Desativar Alarme'></form>");

client.println("<br>");
client.println("<form method=get><input type=submit name=all value='DiscadoraON'></form>");
client.println("<form method=get><input type=submit name=all value='DiscadoraOff'></form>");

//client.println("<form style='height: 257px;' method='get' action='?' name='fomlu_id'></form>");
client.println("<form method=get><input name='ip' size='17' maxlength=17>");
client.println("<form method=get><input value='Salvar' type=submit></form>");


client.println("</body></html>");
          
          //stopping client
          client.stop();
            }              
          }        
        } //while              
      } //If client
 } //Void rede
