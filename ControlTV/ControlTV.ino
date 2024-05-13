#include <IRremote.h>

#define IR_LED_PIN 3
const int ledPin = 13; // Define el pin al que está conectado el LED IR
IRsend irsend(IR_LED_PIN);

// Códigos IR genéricos comunes
//Spectra
//unsigned long powerCode = 0xE0E040BF; // Código IR para encender/apagar
//unsigned long volumeUpCode = 0xE0E0E01F; // Código IR para subir volumen
//unsigned long volumeDownCode = 0xE0E0D02F; // Código IR para bajar volumen
//unsigned long channelUpCode = 0xE0E048B7; // Código IR para subir canal
//unsigned long channelDownCode = 0xE0E008F7; // Código IR para bajar canal

unsigned long powerCode = 0xB9467D02; // Código IR para encender/apagar
unsigned long volumeUpCode = 0xF30C7D02; // Código IR para subir volumen
unsigned long volumeDownCode = 0xE6197D02; // Código IR para bajar volumen
unsigned long channelUpCode = 0xF00F7D02; // Código IR para subir canal
unsigned long channelDownCode = 0xA55A7D02; // Código IR para bajar canal


void setup() {
  // Inicializar el puerto serie
  Serial1.begin(9600);
  pinMode(ledPin, OUTPUT); // Configura el pin como salida
}

void loop() {
  // Escuchar el puerto serie para comandos desde la computadora
  if (Serial1.available() > 0) {
    char command = Serial1.read();
    switch (command) {
      case 'p': // Encender/apagar
        irsend.sendNEC(powerCode, 32);

        digitalWrite(ledPin, HIGH); // Enciende el LED IR
        delay(1000); // Espera 1 segundo
        digitalWrite(ledPin, LOW); // Apaga el LED IR
        delay(1000); // Espera 1 segundo

        delay(50);
        break;
      case 'u': // Subir volumen
        irsend.sendNEC(volumeUpCode, 32);

        digitalWrite(ledPin, HIGH); // Enciende el LED IR
        delay(1000); // Espera 1 segundo
        digitalWrite(ledPin, LOW); // Apaga el LED IR
        delay(1000); // Espera 1 segundo

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
      default:
        break;
    }
  }
}
