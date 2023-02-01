#include <ESP8266WiFi.h>
#include <WebSocketClient.h>


const char* ssid = "Fam. Nic Yah";
const char* password = "b6XvtdSAw5";

char path[] = "/EchoAll";
char host[] = "192.168.1.65:80";

WebSocketClient webSocketClient;
WiFiClient client;

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

  if (client.connect("192.168.1.65",80)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }


  webSocketClient.path = path;
  webSocketClient.host = host;
 
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }
}

void loop() {


  const char* msg = "hola server"; 
  String data;

  if (client.connected()) {
    
    webSocketClient.sendData(msg);
 
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
 
  } else {
    Serial.println("Client disconnected.");
  }
 
  delay(3000);
}
