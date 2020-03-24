
#include "UbidotsESPMQTT.h"
/*
CODIGO para lectura de pulsadores en modo pulldown
envia el valor acumulado mediante protocolo MQTT usando la libreria
MQTT de ubidots
**Autor César Cruz
**Epics-USMP
*/

#define TOKEN "BBFF-lDmWE51M3hVYjyx1nqR0vfbskWQJAR" // Your Ubidots TOKEN
#define WIFINAME "Marriott_Guest" //Your SSID
#define WIFIPASS "kikeGUTY" // Your Wifi Pass

// pines de botones
#define btn_excelente 14
#define btn_bueno     12
#define btn_regular   13
#define btn_malo      2

//pines de luces de alerta
#define led_wifi     4
#define led_power    1


//delay post pulsación
#define delay_btns    5000


//contadores de pulsación
int excelente=0;
int bueno=0;
int regular=0;
int malo=0;
int i=0;
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

void setup() {
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME,NULL);//----!!!! NULL cuando la red no tiene password
  client.begin(callback);

  pinMode(btn_excelente,INPUT);
  pinMode(btn_bueno,INPUT);
  pinMode(btn_regular,INPUT);
  pinMode(btn_malo,INPUT);

  pinMode(led_power,OUTPUT);
  pinMode(led_wifi,OUTPUT);
  //digitalWrite(led_wifi,HIGH);
  //delay(800);
  //digitalWrite(led_wifi,LOW);


  }

void loop() {
  // put your main code here, to run repeatedly:

  if (!client.connected()) {
      digitalWrite(led_wifi, LOW);
      client.reconnect();
      digitalWrite(led_wifi, HIGH);
  } else {
      digitalWrite(led_wifi, HIGH);
  }


if (digitalRead(btn_excelente)==LOW) {

  
  Serial.println("excelente");
  client.add("excelente",excelente); // excelente
  client.ubidotsPublish("hp_tambo");
  excelente=excelente+1;
  delay(delay_btns);

}
if (digitalRead(btn_bueno)==LOW) {
   Serial.println("bueno");
  client.add("bueno",bueno); // excelente
  client.ubidotsPublish("hp_tambo");
  bueno=bueno+1;
  delay(delay_btns);

}
if (digitalRead(btn_regular)==LOW) {
  
    Serial.println("regular");
  client.add("regular",regular); // excelente
  client.ubidotsPublish("hp_tambo");
  regular=regular+1;
  delay(delay_btns);

}
if (digitalRead(btn_malo)==LOW) {

    Serial.println("malo");
  client.add("malo",malo); // excelente
  client.ubidotsPublish("hp_tambo");
  malo=malo+1;
  delay(delay_btns);

}
/*  client.add("excelente",excelente; // excelente
  client.add("bueno", bueno;//bueno
  client.add("regular", regular;//regular
  client.add("malo", malo;//malo
  client.ubidotsPublish("Hp_tambo");
  client.loop();*/

client.loop();

  }
