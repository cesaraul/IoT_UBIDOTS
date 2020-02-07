
#include "UbidotsESPMQTT.h"


#define TOKEN "BBFF-lDmWE51M3hVYjyx1nqR0vfbskWQJAR" // Your Ubidots TOKEN
#define WIFINAME "iPhone Cesaraul" //Your SSID
#define WIFIPASS "cesar123" // Your Wifi Pass

Ubidots client(TOKEN);


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}



  int L=0;
  int in=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  

  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
       }
  
  // Publish values to 2 different data sources
  
  client.add("temperatura", analogRead(0));
  client.add("luz", analogRead(0)+1);
  client.ubidotsPublish("campus_fia");
  client.loop();
 //delay(1000);
 //  if(L>40)L=0;

  
  }
