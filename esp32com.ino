//usamos hardware serial
// Definimos los pines para Serial2 estos pines son para la comunicación serie
#define RX2_PIN 16
#define TX2_PIN 17

String sentMessage = "";    // Almacena el mensaje enviado
String receivedMessage = ""; // Almacena el mensaje recibido

void setup() {
  // Iniciar la comunicación serie con el monitor serial
  Serial.begin(115200);
  while (!Serial) {
    ;  // Espera a que se abra la conexión
  }

  // Iniciar Serial2 con los pines definidos
  Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
  Serial.println("Comenzando la comunicación...");
}

void loop() {
  // Leer desde Serial (monitor serial) y acumular los caracteres en sentMessage
  if (Serial.available()) {
    char incomingChar = Serial.read();
    sentMessage += incomingChar;  // Agregar el caracter al string

    // Cuando se presiona Enter ('\n'), se considera que el mensaje está completo
    if (incomingChar == '\n') {
      Serial.print("Mensaje completo enviado: ");
      Serial.println(sentMessage);   // Mostrar el mensaje completo en el monitor serial
      Serial2.print(sentMessage);    // Enviar el mensaje completo a Serial2
      sentMessage = "";              // Limpiar el string para el siguiente mensaje
    }
  }

  // Leer desde Serial2 y acumular los caracteres en receivedMessage
  if (Serial2.available()) {
    char incomingChar = Serial2.read();
    receivedMessage += incomingChar;  // Agregar el caracter al string

    // Cuando se recibe un Enter ('\n'), se considera que el mensaje está completo
    if (incomingChar == '\n') {
      Serial.print("Mensaje completo recibido: ");
      Serial.println(receivedMessage);  // Mostrar el mensaje completo en el monitor serial
      receivedMessage = "";             // Limpiar el string para el siguiente mensaje
    }
  }
}
