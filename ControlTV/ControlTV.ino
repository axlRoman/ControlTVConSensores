#include <IRremote.h>

#define IR_LED_PIN 3
const int pinIRSensor = 2;
const int ledPin = 13; // Define el pin al que está conectado el LED IR
const int trigPin = 9; // Pin del trig para el sensor ultrasónico
const int echoPin = 10; // Pin del echo para el sensor ultrasónico

IRsend irsend(IR_LED_PIN);

unsigned long powerCode = 0x2FD48B7; // Código IR para encender/apagar
unsigned long volumeUpCode = 0x2FD58A7; // Código IR para subir volumen
unsigned long volumeDownCode = 0x2FD7887; // Código IR para bajar volumen
unsigned long channelUpCode = 0x2FDD827; // Código IR para subir canal
unsigned long channelDownCode = 0x2FDF807; // Código IR para bajar canal
unsigned long muteCode = 0x2FD08F7; // Código IR para silenciar

void setup() {
  Serial.begin(115200); // Inicializar el puerto serie
  pinMode(ledPin, OUTPUT); // Configura el pin como salida
  pinMode(trigPin, OUTPUT); // Configura el pin del trig como salida
  pinMode(echoPin, INPUT); // Configura el pin del echo como entrada
}

bool encendido = false;
void loop() {
  
  int sensorValue = digitalRead(pinIRSensor);
  if(sensorValue == HIGH && !encendido){
    irsend.sendNEC(channelUpCode, 32);

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
    delay(50);
  }
  // Si la distancia es mayor a 15 pero menor a 20 cm, sube el volumen
  else if (distance > 15 && distance < 20) {
    irsend.sendNEC(volumeUpCode, 32);
    delay(50);
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
