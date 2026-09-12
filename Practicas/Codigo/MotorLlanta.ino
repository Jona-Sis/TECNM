#include <WiFiS3.h>

// Credenciales Wi-Fi (Sustituir con credenciales propias)
const char ssid[] = "TU_RED_WIFI";
const char pass[] = "TU_CONTRASEÑA_WIFI";

WiFiServer server(80);

// Pines de control para Canal B
const int PIN_ENB = 3;  // PWM Velocidad a ENB
const int PIN_IN3 = 4;  // Dirección 1 a IN3
const int PIN_IN4 = 5;  // Dirección 2 a IN4

// Variables de estado dinámico
int velocidadActual = 200; // Velocidad inicial (MEDIO por defecto)
bool enAvanza = true;       // Sentido de giro (true = Avanza, false = Retrocede)

void setup() {
  Serial.begin(115200);

  pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);

  // Motor apagado al inicio
  analogWrite(PIN_ENB, 0);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);

  Serial.print("Conectando a Wi-Fi");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED || WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    delay(500);
    Serial.print(".");
  }

  server.begin();
  Serial.println("\n¡Servidor Web Activo!");
  Serial.print("IP asignada para la App: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    Serial.print("Comando de voz recibido: ");
    Serial.println(request);

    // --- COMANDOS DE DIRECCIÓN Y FRENO ---
    if (request.indexOf("/PARA") != -1) {
      Serial.println("-> [VOZ] PARAR MOTOR");
      analogWrite(PIN_ENB, 0);
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, LOW);
    } 
    else if (request.indexOf("/AVANZA") != -1) {
      Serial.println("-> [VOZ] AVANZAR (Sentido Horario)");
      enAvanza = true;
      digitalWrite(PIN_IN3, HIGH);
      digitalWrite(PIN_IN4, LOW);
      analogWrite(PIN_ENB, velocidadActual);
    } 
    else if (request.indexOf("/RETROCEDE") != -1) {
      Serial.println("-> [VOZ] RETROCEDER (Sentido Antihorario)");
      enAvanza = false;
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, HIGH);
      analogWrite(PIN_ENB, velocidadActual);
    } 
    
    // --- COMANDOS DE MODULACIÓN DE VELOCIDAD (PWM) ---
    else if (request.indexOf("/LENTO") != -1) {
      Serial.println("-> [VOZ] VELOCIDAD LENTA (PWM 140)");
      velocidadActual = 140;
      aplicarVelocidad();
    } 
    else if (request.indexOf("/MEDIO") != -1) {
      Serial.println("-> [VOZ] VELOCIDAD MEDIA (PWM 200)");
      velocidadActual = 200;
      aplicarVelocidad();
    } 
    else if (request.indexOf("/RAPIDO") != -1) {
      Serial.println("-> [VOZ] VELOCIDAD MAXIMA (PWM 255)");
      velocidadActual = 255;
      aplicarVelocidad();
    }

    // Respuesta HTTP para cerrar el socket rápidamente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}
