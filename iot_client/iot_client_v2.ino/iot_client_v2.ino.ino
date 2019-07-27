#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//---------------Mensagens da aplicação-------------------

const String IAM = "IAM ";
const String SNS = "SNS ";
const String NSNS = "NSNS ";
const String MEAS = "MEAS ";

const String OKK = "+OK";

//--------------------------------------------------------


char* SSID = "house_lacouth";
char* PASS = "TrialByCombat";

char* host = "192.168.15.9"; 
int   port = 8000;

String id = "varanda";

WiFiClient client;

//TYPE type = DEVICE;

void waitForOk(){
    String msg;
    do{
      msg = client.readStringUntil('\n');
      Serial.println(msg);
    }while(msg!=OKK);
  }

void handshake(){
  String msg;
  client.print(IAM + id);
  waitForOk();
  client.print(SNS + "1");
  waitForOk();
  
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

  handshake();
}

void loop() {
  auto valor = String(random(300));
  client.print(MEAS + String(valor));
  Serial.println(MEAS + String(valor));
//  while(client.available()){
//      String line = client.readStringUntil('\n');
//      Serial.print(line);
//    }
    delay(1000);
}
