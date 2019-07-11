#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <enums.h> // PRECISA CRIAR LINK SIMBOLICO DA PASTA COMMON PARA A PASTA LIBRARIES DO ARDUINO


char* SSID = "house_lacouth";
char* PASS = "TrialByCombat";

char* host = "192.168.15.80"; 
int   port = 8000;

String key = "varanda";

WiFiClient client;

TYPE type = DEVICE;

void handshake(){
  client.print(type);
  client.print(key);
  int msg;
  do{
    msg = client.readStringUntil('\n').toInt();
  }while(msg!=START);
}

void setup() {
  
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);    
  while (WiFi.status() != WL_CONNECTED) {  
    delay(1000);
    Serial.println(WiFi.status());
  }
  while(!client.connect(host, port)){
      delay(500);
      Serial.println("Tentando conexão com o servidor...");
    }

 client.print(key);

}

void loop() {
  auto valor = String(random(300));
  client.print(valor);
  Serial.println(valor);
//  while(client.available()){
//      String line = client.readStringUntil('\n');
//      Serial.print(line);
//    }
    delay(1000);
}
