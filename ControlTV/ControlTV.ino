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
const int pinIRSensor = 4;
const int ledPin = 13; // Define el pin al que está conectado el LED IR
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

unsigned long netflixCode = 0x6A00; // Código IR para Netflix
unsigned long disneyCode = 0x3A00 ; // Código IR para Disney+


/*
unsigned long powerCode = 0x20DF10EF;

unsigned long volumeUpCode = 0x20DF40BF; // Código IR para subir volumen
unsigned long volumeDownCode = 0x20DFC03F; // Código IR para bajar volumen
unsigned long channelUpCode = 0x20DF00FF; // Código IR para subir canal
unsigned long channelDownCode = 0x20DF807F; // Código IR para bajar canal
unsigned long muteCode = 0x20DF906F; // Código IR para silenciar
*/
void interruptRoutine() {
  isr_flag = 1;
}

void setup() {
  Serial.begin(115200); // Inicializar el puerto serie
  pinMode(ledPin, OUTPUT); // Configura el pin como salida
  pinMode(trigPin, OUTPUT); // Configura el pin del trig como salida
  pinMode(echoPin, INPUT); // Configura el pin del echo como entrada

  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}


void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
      irsend.sendNEC(channelDownCode, 32);
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
      irsend.sendNEC(channelUpCode, 32);
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}

bool encendido = false;
void loop() {
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }

  
  int sensorValue = digitalRead(pinIRSensor);
  if(sensorValue == HIGH && !encendido){
    irsend.sendNEC(powerCode, 32);

    digitalWrite(ledPin, HIGH); // Enciende el LED IR
    delay(1000); // Espera 1 segundo
    digitalWrite(ledPin, LOW); // Apaga el LED IR
    delay(1000); // Espera 1 segundo

    delay(50);
    encendido = true;
  }

  // Si el sensor vuelve a LOW, se restablece la variable encendido
  if(sensorValue == LOW){
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
  if (distance <= 10 && distance >= 5) {
    irsend.sendNEC(volumeDownCode, 32);
    //delay(50);
  }
  // Si la distancia es mayor a 15 pero menor a 20 cm, sube el volumen
  else if (distance > 15 && distance < 20) {
    irsend.sendNEC(volumeUpCode, 32);
    //delay(50);
  }

  // Escuchar el puerto serie para comandos desde la computadora
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'p': // Encender/apagar
        irsend.sendNEC(powerCode, 32);
        delay(50);
        break;
      case 'u': // Subir volumen
        irsend.sendNEC(volumeUpCode, 32);
        delay(50);
        break;
      case 'd': // Bajar volumen
        irsend.sendNEC(volumeDownCode, 32);
        delay(50);
        break;
      case 'c': // Subir canal
        irsend.sendNEC(channelUpCode, 32);
        delay(50);
        break;
      case 'b': // Bajar canal
        irsend.sendNEC(channelDownCode, 32);
        delay(50);
        break;
      case 'm': // Silenciar
        irsend.sendNEC(muteCode, 32);
        delay(50);
        break;
      default:
        break;
    }
  }
}
