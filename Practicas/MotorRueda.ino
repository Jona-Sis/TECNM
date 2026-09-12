// Definición de pines para el Canal B del L293D
const int ENB = 3; // Activar 3/4 (PWM para velocidad)
const int IN3 = 4; // Entrada 3 (Dirección)
const int IN4 = 5; // Entrada 4 (Dirección)

// Variables de estado
int velocidad = 255;              // Velocidad inicial (Máxima 0-255)
String estadoDireccion = "PARA";  // Estado actual

void setup() {
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  
  // Motor apagado al arrancar
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);

  Serial.println("--- Control de Motor Listo ---");
  Serial.println("Comandos: ADELANTE | RETROCEDE | PARA | LENTO | MEDIO | RAPIDO");
}

void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    comando.toUpperCase();

    if (comando == "ADELANTE") {
      estadoDireccion = "ADELANTE";
      aplicarMovimiento();
      Serial.println("-> Motor: ADELANTE");
    } 
    else if (comando == "RETROCEDE") {
      estadoDireccion = "RETROCEDE";
      aplicarMovimiento();
      Serial.println("-> Motor: RETROCEDIENDO");
    } 
    else if (comando == "PARA") {
      estadoDireccion = "PARA";
      aplicarMovimiento();
      Serial.println("-> Motor: DETENIDO");
    } 
    else if (comando == "LENTO") {
      velocidad = 100; // ~40% de potencia
      aplicarMovimiento();
      Serial.println("-> Velocidad: LENTO (100)");
    } 
    else if (comando == "MEDIO") {
      velocidad = 180; // ~70% de potencia
      aplicarMovimiento();
      Serial.println("-> Velocidad: MEDIO (180)");
    } 
    else if (comando == "RAPIDO") {
      velocidad = 255; // 100% de potencia
      aplicarMovimiento();
      Serial.println("-> Velocidad: RÁPIDO (255)");
    } 
    else {
      Serial.println("<!> Comando invalido. Usa: ADELANTE, RETROCEDE, PARA, LENTO, MEDIO, RAPIDO");
    }
  }
}

void aplicarMovimiento() {
  if (estadoDireccion == "ADELANTE") {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, velocidad);
  } 
  else if (estadoDireccion == "RETROCEDE") {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, velocidad);
  } 
  else if (estadoDireccion == "PARA") {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
  }
}
