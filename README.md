# [MimoTV](https://github.com/axlRoman/ControlTVConSensores/)
[![MimoTV](https://i.postimg.cc/vmQ5Wp8W/MimoTV.jpg)](https://github.com/axlRoman/ControlTVConSensores/)

## Resumen
[![VideoMimoTV](https://img.youtube.com/vi/ngGnWXy2fA8/0.jpg)](https://youtu.be/ngGnWXy2fA8)

La motivación principal para este proyecto fue que un integrante de nuestro equipo tiene un familiar que tenía dificultades al momento de interactuar con un control remoto. Este familiar encontraba el control remoto impreciso y a menudo presionaba teclas no deseadas, lo cual dificulta su uso. Por lo tanto, este proyecto comenzó principalmente para abordar esa problemática.

Además, se identificó que en el entorno hospitalario, los pacientes a menudo enfrentan desafíos similares al intentar utilizar controles remotos. Muchos pacientes tienen movilidad limitada o falta de destreza en las manos, lo que hace que el uso de un control remoto tradicional sea complicado y frustrante. Este problema puede afectar negativamente su bienestar, ya que no pueden acceder de manera fácil a opciones de entretenimiento o comunicación que les permitan sentirse más cómodos y conectados durante su estancia en el hospital.

Por ello, nuestro proyecto se enfoca en desarrollar una solución de control remoto más intuitiva y accesible, que minimice los errores al presionar teclas y facilite su uso tanto en el hogar como en entornos hospitalarios. Creemos que una herramienta así no solo mejorará la calidad de vida de nuestro compañero de equipo y su familiar, sino también la de muchas otras personas que enfrentan dificultades similares en su vida diaria.

# Control Remoto Universal con Sensores Ultrasónicos e Infrarrojos

Este proyecto utiliza un microcontrolador Arduino para crear un control remoto universal que puede enviar comandos IR (infrarrojos) a varios dispositivos electrónicos. Incorpora sensores ultrasónicos e infrarrojos para ajustar el volumen y activar otras funcionalidades basadas en la proximidad de un objeto.

## Componentes Necesarios

- Arduino (uno o mega)
- Varios sensores infrarrojo detector de obstáculos (13 o mas según las necesidades)
- Sensor ultrasónico HC-SR04
- LED IR y receptor IR
- Resistencias (220Ω) y cables de conexión

## Descripción de Pines
[![CircuitoLogicoMimoTV](https://i.postimg.cc/W4M0rsPp/Circuito-Logico-Mimo-TV.jpg)](https://github.com/axlRoman/ControlTVConSensores/)



- `IR_LED_PIN`: Pin 3 (LED IR)
- `LED_PIN`: Pin 2 (Indicador LED)
- `trigPin`: Pin 9 (Trigger del sensor ultrasónico)
- `echoPin`: Pin 10 (Echo del sensor ultrasónico)

## Asignación de Pines para los sensores infrarrojos detector de obstáculos

- `power`: Pin 4
- `menu`: Pin 22
- `channelUp`: Pin 5
- `channelDown`: Pin 6
- `up`: Pin 8
- `down`: Pin 7
- `source`: Pin 26
- `ok`: Pin 11
- `right`: Pin 15
- `left`: Pin 0
- `play`: Pin 17
- `exitPort`: Pin 19
- `mute`: Pin 13

## Códigos IR

Los códigos IR son específicos para cada comando y se envían utilizando el protocolo NEC. Los códigos utilizados en este proyecto para una televisión LG son:

- `powerCode`: 0x20DF10EF
- `volumeUpCode`: 0x20DF40BF
- `volumeDownCode`: 0x20DFC03F
- `channelUpCode`: 0x20DF00FF
- `channelDownCode`: 0x20DF807F
- `muteCode`: 0x20DF906F
- `sourceCode`: 0x20DF3EC1
- `upCode`: 0x20DF02FD
- `downCode`: 0x20DF827D
- `leftCode`: 0x20DFE01F
- `rightCode`: 0x20DF609F
- `okCode`: 0x20DF22DD
- `backCode`: 0x20DF14EB
- `playPauseCode`: 0x20DF0DF2
- `exitCode`: 0x20DFDA25
- `menuCode`: 0x20DFC23D
- `netflixCode`: 0x20DF6A95
- `disneyCode`: 0x20DF3AC5

### Más Códigos IR

Puedes encontrar más códigos IR en los siguientes archivos dentro del repositorio:
- [Códigos para control LG](https://github.com/axlRoman/ControlTVConSensores/blob/main/CodigoControlLG.txt)
- [Códigos para control Mecagable](https://github.com/axlRoman/ControlTVConSensores/blob/main/CodigosControlMecagable.txt)
- [Códigos para control Spectra](https://github.com/axlRoman/ControlTVConSensores/blob/main/CodigosControlSpectra.txt)
- [Códigos para control Roku](https://github.com/axlRoman/ControlTVConSensores/blob/main/CodigosRoku.txt)


## Instalación

1. Conecta los componentes según la asignación de pines.
2. Instala las librerías necesarias en el IDE de Arduino:
   - `IRremote`
   - `Wire`
3. Sube el código proporcionado al Arduino.

## Funcionamiento

### Configuración Inicial

En la función `setup()`, se inicializan el puerto serie y se configuran los pines de los sensores.

### Bucle Principal

En la función `loop()`, se lee el estado de cada sensor. Según el sensor accionado, se envía el código IR correspondiente. Además, se utiliza el sensor ultrasónico para ajustar el volumen y los otros sensores para activar otras funcionalidades:

- **Sensor Ultrasónico**:
  - Si la distancia es entre 2 cm y 13 cm, se baja el volumen.
  - Si la distancia es entre 18 cm y 35 cm, se sube el volumen.
- **Sensor Infrarrojo Detector de Obstáculos**:
  - Detecta la proximidad y activa otras funcionalidades del control remoto.

### Función `encender()`

Enciende un LED indicador durante 500 ms para proporcionar retroalimentación visual cuando se envía un comando.

### Sensores Infrarrojos

Los sensores infrarrojos detectan la proximidad de objetos y activa funcionalidades adicionales. Como encender o apagar el televisor, cambiar de canales, las flechas de desplazamiento, play y pausa, source, ok, exit y menu

# [Receptor y Emisor de Señales IR con Arduino](https://github.com/axlRoman/ControlTVConSensores/blob/main/ReceiveDump/ReceiveDump.ino)

Este proyecto utiliza un microcontrolador Arduino para recibir señales IR (infrarrojas) y retransmitirlas. Utiliza la librería `IRremote` para gestionar tanto el receptor como el emisor de señales IR.

## Componentes Necesarios

- Arduino (uno compatible)
- Receptor IR (como el TSOP4838)
- Emisor IR (LED IR)
- Resistencias (220Ω) y cables de conexión

## Descripción de Pines
[![CircuitoLogicoReceptorEmisorSeñalIR](https://i.postimg.cc/HLH96rz8/Circuito-Logico-Receptor-YEmisor-De-Se-al.jpg)](https://github.com/axlRoman/ControlTVConSensores/)

- `IR_RECEIVE_PIN`: Pin 2 (Receptor IR)
- `IR_SEND_PIN`: Pin 3 (Emisor IR)
- `LED_BUILTIN`: LED integrado en la placa Arduino

## Instalación

1. Conecta los componentes según la asignación de pines.
2. Instala la librería `IRremote` en el IDE de Arduino. Puedes instalarla desde el Administrador de Librerías buscando "IRremote".
3. Sube el código proporcionado al Arduino.

## Código

```cpp
#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2  // Pin para el receptor IR
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
```
## Funcionamiento
### Configuración Inicial
En la función `setup()`, se inicializa la comunicación serie y se configura el receptor IR en el pin especificado.

### Bucle Principal
En la función `loop()`, se detecta si se ha recibido una señal IR. Si se recibe una señal:

Se imprime la señal recibida en el monitor serie.
Si el protocolo de la señal es conocido, se retransmite la señal utilizando el emisor IR.

Se imprime la señal retransmitida en el monitor serie.
Si el protocolo es desconocido, se notifica que no se retransmitirá.

### Funciones Principales
- `IrReceiver.decode()`: Captura una señal IR recibida.
- `IrReceiver.printIRResultShort(&Serial)`: Imprime los detalles de la señal recibida.
- `IrSender.sendIRResultRaw(&IrReceiver.decodedIRData.rawData)`: Retransmite la señal IR recibida.
- `IrReceiver.resume()`: Prepara el receptor para la próxima señal IR.

## Contribución

Las contribuciones son bienvenidas. Por favor, abre un issue o un pull request para discutir cualquier cambio.

