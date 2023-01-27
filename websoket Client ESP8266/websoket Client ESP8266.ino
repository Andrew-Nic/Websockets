#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>


const char* ssid = "Fam. Nic Yah";
const char* password = "b6XvtdSAw5";

WebSocketsClient webSocketClient;


void onWebSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("Desconectado del servidor");
      break;
    case WStype_CONNECTED:
      Serial.println("Conectado al servidor");
      break;
    case WStype_TEXT:
      Serial.print("Mensaje recibido: ");
      Serial.println((char *)payload);
      break;
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);

  webSocketClient.begin("192.168.1.67",80,"/EchoAll");
  webSocketClient.onEvent(onWebSocketEvent);

}

void loop() {

  webSocketClient.loop();
  webSocketClient.sendTXT("Hola server");
  delay(3000);
}
