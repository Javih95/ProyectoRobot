#include <IRremote.h> // Biblioteca para manejar el receptor infrarrojo

// Configuración del receptor IR
const int receptorIR = 2; // Pin conectado al receptor IR

// Definición de los códigos de los botones del control remoto
const unsigned long botonAvanzar = 0xE718FF00;
const unsigned long botonReversa = 0xAD52FF00;
const unsigned long botonIzquierda = 0xF708FF00;
const unsigned long botonDerecha = 0xA55AFF00;
const unsigned long botonStop = 0xE31CFF00;

// Configuración del receptor IR
IRrecv irrecv(receptorIR);
decode_results resultados;

// Configuración de los pines de los motores
const int motorIzq1 = 6;  // Motor izquierdo, terminal A-IB
const int motorIzq2 = 7;  // Motor izquierdo, terminal A-IA
const int motorDer1 = 10; // Motor derecho, terminal B-IA
const int motorDer2 = 11; // Motor derecho, terminal B-IB

void setup() {
  // Inicializar comunicación serial para depuración
  Serial.begin(9600);

  // Configurar pines de motores como salida
  pinMode(motorIzq1, OUTPUT);
  pinMode(motorIzq2, OUTPUT);
  pinMode(motorDer1, OUTPUT);
  pinMode(motorDer2, OUTPUT);

  // Configurar el pin LED de estado como salida
  pinMode(13, OUTPUT);

  // Iniciar el receptor IR
  IrReceiver.begin(receptorIR, ENABLE_LED_FEEDBACK);
  Serial.println("Esperando señales del control remoto...");
}

void loop() {
  // Verificar si se ha recibido una señal IR
  if (IrReceiver.decode()) {
    unsigned long codigo = IrReceiver.decodedIRData.decodedRawData;

    // Filtrar señales inválidas o repetitivas
    if (codigo != 0x0 && codigo != 0xFFFFFFFF) {
      // Identificar el botón presionado
      if (codigo == botonAvanzar) {
        Serial.println("Avanzar");
        avanzar();
      } else if (codigo == botonReversa) {
        Serial.println("Reversa");
        retroceder();
      } else if (codigo == botonIzquierda) {
        Serial.println("Izquierda");
        girarIzquierda();
      } else if (codigo == botonDerecha) {
        Serial.println("Derecha");
        girarDerecha();
      } else if (codigo == botonStop) {
        Serial.println("Stop");
        stop();
      } else {
        Serial.print("Código no reconocido: ");
        Serial.println(codigo, HEX);
      }
    } else {
      Serial.println("Código repetitivo ignorado");
    }

    // Preparar para recibir la siguiente señal
    IrReceiver.resume();
  }
}

// Funciones de control de los motores
void avanzar() {
  digitalWrite(motorIzq1, HIGH);
  digitalWrite(motorIzq2, LOW);
  digitalWrite(motorDer1, HIGH);
  digitalWrite(motorDer2, LOW);
}

void retroceder() {
  digitalWrite(motorIzq1, LOW);
  digitalWrite(motorIzq2, HIGH);
  digitalWrite(motorDer1, LOW);
  digitalWrite(motorDer2, HIGH);
}

void stop() {
  digitalWrite(motorIzq1, LOW);
  digitalWrite(motorIzq2, LOW);
  digitalWrite(motorDer1, LOW);
  digitalWrite(motorDer2, LOW);
}

void girarDerecha() {
  Serial.println("Girando a la derecha...");
  digitalWrite(motorIzq1, HIGH);
  digitalWrite(motorIzq2, LOW); // Motor izquierdo avanza
  digitalWrite(motorDer1, LOW);
  digitalWrite(motorDer2, LOW); // Motor derecho detenido
}

void girarIzquierda() {
  Serial.println("Girando a la izquierda...");
  digitalWrite(motorIzq1, LOW);
  digitalWrite(motorIzq2, LOW); // Motor izquierdo detenido
  digitalWrite(motorDer1, HIGH);
  digitalWrite(motorDer2, LOW); // Motor derecho avanza
}
