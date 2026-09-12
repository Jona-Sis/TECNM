## Reporte de Práctica: Control de Motor CC con L293D y Arduino UNO R4 WiFi

**Objetivo**
Implementar y validar físicamente el control bidireccional y de velocidad de un motor de corriente continua (CC) utilizando la tarjeta Arduino UNO R4 WiFi y el driver L293D (Puente H), interactuando en tiempo real mediante comandos de texto enviados desde el Monitor Serie de la computadora.

**Materiales Utilizados**
* Tarjeta de desarrollo Arduino UNO R4 WiFi
* Circuito integrado L293D (Puente H)
* Motor de corriente continua (CC)
* Fuente de poder de CC regulada (Línea de 12V)
* Protoboard y cables de conexión (Jumpers)

**Justificación de la Fuente de Alimentación**
Para la etapa de potencia del motor (Pin 8 / VCC2 del L293D), se optó por implementar una fuente de poder regulada de 12V (línea amarilla) en lugar de una batería comercial. Esta decisión de diseño responde a la necesidad de suministrar el voltaje nominal óptimo para maximizar el torque y la respuesta dinámica del motor en cambios bruscos de sentido y aceleración (PWM). Asimismo, la fuente garantiza una corriente constante sin caídas de tensión por resistencia interna, aislando la etapa de potencia para evitar fluctuaciones en la línea lógica del Arduino UNO R4 WiFi.

**Esquema de Conexiones Físicas**

| Componente / Origen | Pin de Origen | Pin en L293D | Función |
| :--- | :--- | :--- | :--- |
| **Arduino UNO R4 WiFi** | Pin 3 (PWM) | Pin 9 (EN3/4) | Control de velocidad vía PWM |
| **Arduino UNO R4 WiFi** | Pin 4 | Pin 10 (IN3) | Dirección de giro 1 |
| **Arduino UNO R4 WiFi** | Pin 5 | Pin 15 (IN4) | Dirección de giro 2 |
| **Arduino UNO R4 WiFi** | 5V | Pin 16 (VCC1) | Alimentación lógica del chip |
| **Arduino / Fuente** | GND / Negativo (-) | Pines 4, 5, 12, 13 | Tierra común del circuito |
| **Fuente de Poder (12V)** | Positivo (+) / Cable Amarillo | Pin 8 (VCC2) | Alimentación de potencia para el motor |
| **Motor CC** | Terminales 1 y 2 | Pines 11 y 14 | Salidas de potencia (OUT3 y OUT4) |

**Lógica de Control y Comandos Serie**
El código grabado en el Arduino UNO R4 WiFi establece la comunicación serie a **115200 baudios** para asegurar una transmisión y lectura de datos con latencia mínima. El microcontrolador ejecuta las siguientes acciones al recibir cada comando:

* **`ADELANTE`**: Activa `IN3` en ALTO y `IN4` en BAJO para hacer girar el motor en sentido horario.
* **`RETROCEDE`**: Invierte las señales (`IN3` en BAJO e `IN4` en ALTO) para girar en sentido antihorario.
* **`PARA`**: Coloca ambas salidas en BAJO y apaga el pin de habilitación (`ENB` a 0) para detener el motor.
* **`LENTO`**: Modula la señal PWM del Pin 3 a un valor de **100** (~40% de potencia).
* **`MEDIO`**: Modula la señal PWM del Pin 3 a un valor de **180** (~70% de potencia).
* **`RAPIDO`**: Aplica el ciclo de trabajo máximo en PWM con valor de **255** (100% de potencia).

**Resultados y Conclusiones**
El montaje físico funcionó de manera óptima. La tarjeta Arduino UNO R4 WiFi procesó en tiempo real los comandos enviados desde el Monitor Serie a 115200 baudios. El uso de la fuente regulada a 12V otorgó al motor el torque necesario para realizar transiciones suaves y respuestas inmediatas en las variaciones de PWM. La disposición lógica del circuito sobre el canal central del protoboard y la correcta unificación del plano de tierra (GND) garantizaron la estabilidad general del sistema sin interferencias.
