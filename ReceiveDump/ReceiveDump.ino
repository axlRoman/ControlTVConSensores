/*
 * ReceiveDump.cpp
 *
 * Dumps the received signal in different flavors.
 * Since the printing takes so much time (200 ms @115200 for NEC protocol, 70ms for NEC repeat),
 * repeat signals may be skipped or interpreted as UNKNOWN.
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 ************************************************************************************
 * MIT License
 *
 * Copyright (c) 2020-2024 Armin Joachimsmeyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is fur  nished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************************
 */
#include <Arduino.h>
#include <IRremote.h>

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.

#if !defined(RAW_BUFFER_LENGTH)
#  if RAMEND <= 0x4FF || RAMSIZE < 0x4FF
#define RAW_BUFFER_LENGTH  180  // 750 (600 if we have only 2k RAM) is the value for air condition remotes. Default is 112 if DECODE_MAGIQUEST is enabled, otherwise 100.
#  elif RAMEND <= 0x8FF || RAMSIZE < 0x8FF
#define RAW_BUFFER_LENGTH  600  // 750 (600 if we have only 2k RAM) is the value for air condition remotes. Default is 112 if DECODE_MAGIQUEST is enabled, otherwise 100.
#  else
#define RAW_BUFFER_LENGTH  750  // 750 (600 if we have only 2k RAM) is the value for air condition remotes. Default is 112 if DECODE_MAGIQUEST is enabled, otherwise 100.
#  endif
#endif

/*
 * MARK_EXCESS_MICROS is subtracted from all marks and added to all spaces before decoding,
 * to compensate for the signal forming of different IR receiver modules. See also IRremote.hpp line 142.
 *
 * You can change this value accordingly to the receiver module you use.
 * The required value can be derived from the timings printed here.
 * Keep in mind that the timings may change with the distance
 * between sender and receiver as well as with the ambient light intensity.
 */
#define MARK_EXCESS_MICROS    20    // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.

//#define RECORD_GAP_MICROS 12000 // Default is 8000. Activate it for some LG air conditioner protocols
//#define DEBUG // Activate this for lots of lovely debug output from the decoders.

#include <IRremote.hpp>


#define IR_LED_PIN 3
const int ledPin = 13; // Define el pin al que está conectado el LED IR
IRsend irsend(IR_LED_PIN);

// Códigos IR genéricos comunes
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




//+=============================================================================
// Configure the Arduino
//
void setup() {
  // Inicializar el puerto serie
  Serial1.begin(9600);
  pinMode(ledPin, OUTPUT); // Configura el pin como salida
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);   // Status message will be sent to PC at 9600 baud
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
    // Just to know which program is running on my Arduino
    //Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
   // printActiveIRProtocols(&Serial);
   // Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));

    // infos for receive
   // Serial.print(RECORD_GAP_MICROS);
   // Serial.println(F(" us is the (minimum) gap, after which the start of a new IR packet is assumed"));
   // Serial.print(MARK_EXCESS_MICROS);
   // Serial.println();
   // Serial.println(F("Because of the verbose output (>200 ms at 115200 baud), repeats are not dumped correctly!"));
   // Serial.println();
   // Serial.println(F("If you receive protocol NEC, Samsung or LG, run also ReceiveDemo to check if your actual protocol is eventually NEC2 or SamsungLG, which is determined by the repeats"));
   // Serial.println();

}

//+=============================================================================
// The repeating section of the code
void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'p':
        irsend.sendNEC(powerCode, 32);
        break;
      case 'u':
        irsend.sendNEC(volumeUpCode, 32);
        break;
      case 'd':
        irsend.sendNEC(volumeDownCode, 32);
        break;
      case 'm':
        irsend.sendNEC(muteCode, 32);
        break;
      case 'h':
        irsend.sendNEC(sourceCode, 32);
        break;
      case 'U':
        irsend.sendNEC(upCode, 32);
        break;
      case 'D':
        irsend.sendNEC(downCode, 32);
        break;
      case 'L':
        irsend.sendNEC(leftCode, 32);
        break;
      case 'R':
        irsend.sendNEC(rightCode, 32);
        break;
      case 'O':
        irsend.sendNEC(okCode, 32);
        break;
      case 'b':
        irsend.sendNEC(backCode, 32);
        break;
      case 'P':
        irsend.sendNEC(playPauseCode, 32);
        break;
      case 'n':
        irsend.sendNEC(netflixCode, 32);
        break;
      case 'i':
        irsend.sendNEC(disneyCode, 32);
        break;
      case 'e':
        irsend.sendNEC(exitCode, 32);
        break;
      default:
        break;
    }
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }

  if (IrReceiver.decode()) {
    Serial.println();
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
    IrReceiver.resume();
  }

}
