// Pines para controlar los motores
const int motorIzq2 = 5;  // A-IA
const int motorIzq1 = 6;  // A-IB
const int motorDer1 = 10; // B-IA
const int motorDer2 = 11; // B-IB

void setup() {
  // Configurar pines como salida
  pinMode(motorIzq1, OUTPUT);
  pinMode(motorIzq2, OUTPUT);
  pinMode(motorDer1, OUTPUT);
  pinMode(motorDer2, OUTPUT); 
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH); // Encender el LED
  retroceder();
  delay(5000); 
  stop();           // Esperar 1 segundo
  digitalWrite(13, LOW);  // Apagar el LED
  avanzar();
  delay(5000);
  stop();            // Esperar 1 segundo
}
void avanzar(){
// Inicializar motores para moverse hacia adelante
  digitalWrite(motorIzq1, HIGH);
  digitalWrite(motorIzq2, LOW);
  digitalWrite(motorDer1, HIGH);
  digitalWrite(motorDer2, LOW);
}
void retroceder(){
  digitalWrite(motorIzq1, LOW);
  digitalWrite(motorIzq2, HIGH);
  digitalWrite(motorDer1, LOW);
  digitalWrite(motorDer2, HIGH);
}
void stop(){
    digitalWrite(motorIzq1, LOW);
  digitalWrite(motorIzq2, LOW);
  digitalWrite(motorDer1, LOW);
  digitalWrite(motorDer2, LOW);
}