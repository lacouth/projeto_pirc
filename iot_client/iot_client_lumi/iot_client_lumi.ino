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

char* host = "192.168.0.153"; 
int   port = 65432;

String id = "LUMI";

WiFiClient client;

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

void protocolo(String cmd){
  if(cmd.indexOf("+LED 1") >= 0){
    Serial.println("ligar");
    digitalWrite(D1,HIGH);
  }else if(cmd.indexOf("+LED 0") >= 0){
    Serial.println("desligar");
    digitalWrite(D1,LOW);
  }
}

void setup() {
  
  Serial.begin(115200);
  WiFi.begin(SSID, PASS); 
  pinMode(D1, OUTPUT);   
  while (WiFi.status() != WL_CONNECTED) {  
    delay(1000);
    Serial.println(WiFi.localIP());
  }
  while(!client.connect(host, port)){
      delay(500);
      Serial.println("Tentando conexão com o servidor...");
    }

  handshake();
}

void loop() {
  int valor = analogRead(A0);
  client.println(MEAS + String(valor));
  Serial.println(MEAS + String(valor));
  while(client.available() > 0){
      String comando = client.readStringUntil('\n');
      protocolo(comando);
      Serial.println(comando);
    }
    //delay(1000);
}
