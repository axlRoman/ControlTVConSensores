#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 11  // Pin para el receptor IR
#define IR_SEND_PIN 3      // Pin para el emisor IR

void setup() {
    Serial.begin(115200); // Inicializa la comunicación serie
    pinMode(LED_BUILTIN, OUTPUT);
    
    Serial.println(F("Iniciando receptor IR..."));
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Inicializa el receptor IR
    
    Serial.println(F("Listo para recibir señales IR."));
}

void loop() {
    if (IrReceiver.decode()) {  // Captura una señal IR
        // Imprime los resultados de la señal recibida
        Serial.println();
        Serial.println(F("Señal recibida:"));
        IrReceiver.printIRResultShort(&Serial);

        // Retransmite la señal recibida
        if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
            Serial.println(F("Retransmitiendo señal..."));
            IrSender.sendIRResultRaw(&IrReceiver.decodedIRData.rawData); // Enviar la señal IR recibida
            
            // Imprime la señal que se retransmitió
            Serial.println(F("Señal retransmitida:"));
            IrReceiver.printIRResultShort(&Serial);
        } else {
            Serial.println(F("Protocolo desconocido, no se retransmitirá."));
        }

        IrReceiver.resume(); // Prepara para la siguiente señal IR
    }
}
