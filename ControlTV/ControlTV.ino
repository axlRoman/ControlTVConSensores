#include <IRremote.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

// Constants

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

#define IR_LED_PIN 3
#define LED_PIN 2
const int power = 4;

const int menu = 22;

const int channelUp = 5;
const int channelDown = 6;

const int up = 8;
const int down = 7;

const int source = 26;
const int ok = 11;

const int rigth = 15;
const int left = 0;

const int play = 17;

//const int ret = 19;

const int exitPort = 19;

const int mute = 13; // Define el pin al que está conectado el LED IR
const int trigPin = 9; // Pin del trig para el sensor ultrasónico
const int echoPin = 10; // Pin del echo para el sensor ultrasónico

IRsend irsend(IR_LED_PIN);

//Spectra
unsigned long powerCode = 0x2FD48B7; // Código IR para encender/apagar
unsigned long volumeUpCode = 0x2FD58A7; // Código IR para subir volumen
unsigned long volumeDownCode = 0x2FD7887; // Código IR para bajar volumen
unsigned long channelUpCode = 0x2FDD827; // Código IR para subir canal
unsigned long channelDownCode = 0x2FDF807; // Código IR para bajar canal
unsigned long muteCode = 0x2FD08F7; // Código IR para silenciar

unsigned long sourceCode = 0x2FD28D7; // Código IR para home
unsigned long upCode =0x2FD9867 ; // Código IR para arriba
unsigned long downCode = 0x2FDB847  ; // Código IR para abajo
unsigned long leftCode = 0x2FD629D  ; // Código IR para izquierda
unsigned long rightCode = 0x2FDE21D  ; // Código IR para derecha
unsigned long okCode = 0x2FD50AF  ; // Código IR para ok
unsigned long backCode = 0x2FDFF00 ; // Código IR para regresar

unsigned long playPauseCode = 0x2FDEA15 ; // Código IR para play/pause

unsigned long exitCode = 0x2FD22DD  ;


unsigned long menuCode = 0x2FDDA25    ;

unsigned long netflixCode = 0xBB44BF40; // Código IR para Netflix
unsigned long disneyCode = 0x3A00 ; // Código IR para Disney+

void interruptRoutine() {
  isr_flag = 1;
}

void setup() {
  Serial.begin(115200); // Inicializar el puerto serie
//  pinMode(ledPin, OUTPUT); // Configura el pin como salida
  pinMode(trigPin, OUTPUT); // Configura el pin del trig como salida
  pinMode(echoPin, INPUT); // Configura el pin del echo como entrada
  pinMode(LED_PIN,OUTPUT);
  pinMode(power, INPUT_PULLUP); // Configura el pin power con resistencia pull-up

  pinMode(channelUp, INPUT_PULLUP); // Configura el pin channelUp con resistencia pull-up
  pinMode(channelDown, INPUT_PULLUP); // Configura el pin channelDown con resistencia pull-up

  pinMode(source, INPUT_PULLUP); // Configura el pin source con resistencia pull-up
  pinMode(ok, INPUT_PULLUP); // Configura el pin ok con resistencia pull-up

  pinMode(up, INPUT_PULLUP); // Configura el pin up con resistencia pull-up
  pinMode(down, INPUT_PULLUP); // Configura el pin down con resistencia pull-up

  pinMode(rigth, INPUT_PULLUP); // Configura el pin right con resistencia pull-up
  pinMode(left, INPUT_PULLUP); // Configura el pin left con resistencia pull-up

  pinMode(exit, INPUT_PULLUP); // Configura el pin return con resistencia pull-up
  pinMode(play, INPUT_PULLUP); // Configura el pin play con resistencia pull-up

  pinMode(mute, INPUT_PULLUP); // Configura el pin play con resistencia pull-up

  //pinMode(exit, INPUT_PULLUP); // Configura el pin up con resistencia pull-up
 // pinMode(down, INPUT_PULLUP); // Configura el pin down con resistencia pull-up
}

void encender(){
  digitalWrite(LED_PIN,HIGH);
  delay(500);
  digitalWrite(LED_PIN,LOW);
}

bool encendido = false;
bool channel = false;
void loop() {

  int sensorPower = digitalRead(power);
  if(sensorPower == HIGH && !encendido){
    irsend.sendNEC(powerCode, 32);
    //delay(50);
    encendido = true;
    encender();
  }


  int sensorChannelUp = digitalRead(channelUp);
  if(sensorChannelUp == LOW){
    irsend.sendNEC(channelUpCode, 32);
    delay(50);
    encender();
  }

  int sensorChannelDown = digitalRead(channelDown);
  if(sensorChannelDown == LOW){
    irsend.sendNEC(channelDownCode, 32);
    delay(50);
    encender();
  }

  int sensorSource = digitalRead(source);
  if(sensorSource == LOW){
    irsend.sendNEC(sourceCode, 32);
    delay(50);
    encender();
  }
  
  int sensorOk = digitalRead(ok);
  if(sensorOk == LOW){
    irsend.sendNEC(okCode, 32);
    delay(50);
    encender();
  }


  int sensorUp = digitalRead(up);
  if(sensorUp == LOW){
    irsend.sendNEC(upCode, 32);
    delay(50);
  }

  int sensorDown = digitalRead(down);
  if(sensorDown == LOW){
    irsend.sendNEC(downCode, 32);
    delay(50);
    encender();
  }
  int sensorRigth = digitalRead(rigth);
  if(sensorRigth == LOW){
    irsend.sendNEC(rightCode, 32);
    delay(50);
    encender();
  }

  int sensorleft = digitalRead(left);
  if(sensorleft == LOW){
    irsend.sendNEC(leftCode, 32);
    delay(50);
    encender();
  }

  int sensorPlay = digitalRead(play);
  if(sensorPlay == LOW){
    irsend.sendNEC(playPauseCode, 32);
    delay(50);
    encender();
  }

  int sensorMute = digitalRead(mute);
  if(sensorMute == LOW){
    irsend.sendNEC(muteCode, 32);
    delay(50);
    encender();
  }
/*
  int sensorReturn = digitalRead(ret);
  if(sensorReturn == LOW){
    irsend.sendNEC(backCode, 32);
    delay(50);
    encender();
  }
*/

  int sensorMenu = digitalRead(menu);
  if(sensorMenu == LOW){
    irsend.sendNEC(menuCode, 32);
    delay(50);
    encender();
  }

  int sensorExit = digitalRead(exitPort);
  if(sensorExit == LOW){
    irsend.sendNEC(exitCode, 32);
    delay(50);
    encender();
  }

  // Si el sensor vuelve a LOW, se restablece la variable encendido
  if(sensorPower == LOW){
    encendido = false;
  }
  



  // Lee la distancia del sensor ultrasónico
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Si la distancia es menor o igual a 10 cm, baja el volumen
  if (distance <= 13 && distance >= 2) {
    irsend.sendNEC(volumeDownCode, 32);
    digitalWrite(LED_PIN,HIGH);
    //delay(10);
  }
  // Si la distancia es mayor a 15 pero menor a 20 cm, sube el volumen
  else if (distance > 18 && distance < 35) {
    irsend.sendNEC(volumeUpCode, 32);
    digitalWrite(LED_PIN,HIGH);
    //delay(10);
  }
  else{
  digitalWrite(LED_PIN,LOW);
  }
  delay(50);
} 