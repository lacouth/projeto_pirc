#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#define MAX_CHAR 1024
//---------------Mensagens da aplicação-------------------

const String IAM = "IAM ";
const String SNS = "SNS ";
const String NSNS = "NSNS ";
const String MEAS = "MEAS ";

const String OKK = "+OK";

//----------------- Variáveis Globais-------------------

int DELAY = 1000;
char recv_msg[MAX_CHAR];


//------------------------------------------------------


char* SSID = "house_lacouth";
char* PASS = "TrialByCombat";

char* host = "192.168.15.9"; 
int   port = 8888;

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

void protocolo(String mensagem){
  Serial.println(mensagem);
  char *command;
  mensagem.toCharArray(recv_msg,MAX_CHAR);
  command = strtok(recv_msg," ");
  if(!strcmp(command,"FRQ")){
    command = strtok(NULL," ");
    DELAY = atoi(command);
    }
  }

void loop() {
  auto valor = String(random(300));
  client.println(MEAS + String(valor));
  Serial.println(MEAS + String(valor));
  delay(DELAY);
  if(client.available() > 0){
      protocolo(client.readStringUntil('\n'));
    }
    
}
