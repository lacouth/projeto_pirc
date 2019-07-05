#include <WiFiServerSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFi.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFiScan.h>
#include <WiFiServer.h>
#include <ESP8266WiFiGeneric.h>
#include <WiFiClientSecure.h>
#include <BearSSLHelpers.h>
#include <ESP8266WiFiType.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiAP.h>


char* SSID = "house_lacouth";
char* PASS = "TrialByCombat";

char* host = "192.168.15.80"; 
int   port = 8000;    

WiFiClient client;

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
