

#include <Arduino.h>
#define gas 9
int valor;
int limite;
#define excelente 2
#define bueno 3
#define regular 4
#define malo 5


long tiempoTx;
void setup() {

  Serial.begin(9600);
  pinMode(gas,INPUT);

  pinMode(excelente, OUTPUT);
  pinMode(bueno, OUTPUT);
  pinMode(regular, OUTPUT);
  pinMode(malo, OUTPUT);

  tiempoTx=millis();
  
}

void loop() {

  valor=digitalRead(gas);
  limite=analogRead(0);

  if((millis()-tiempoTx) >500){  //transmision cada 500ms
    Serial.print("valor analogico: "); //datos captados
    Serial.println(limite);
    tiempoTx=millis();
  }

  if (Serial.available()>0)
  {
    int calidad = Serial.read();

    if (calidad == 'e')
    {
      digitalWrite(excelente,HIGH);
      digitalWrite(bueno,LOW);
      digitalWrite(regular,LOW);
      digitalWrite(malo,LOW);
    }
    if (calidad == 'b')
    {
      digitalWrite(bueno,LOW);
      digitalWrite(bueno,HIGH);
      digitalWrite(regular,LOW);
      digitalWrite(malo,LOW);
    }
    if (calidad == 'r')
    {
      digitalWrite(regular,LOW);
      digitalWrite(bueno,LOW);
      digitalWrite(regular,HIGH);
      digitalWrite(malo,LOW);
    }
    if (calidad == 'm')
    {
      digitalWrite(malo,LOW);
      digitalWrite(bueno,LOW);
      digitalWrite(regular,LOW);
      digitalWrite(malo,HIGH);
    }
    
  }
  

  delay(500);
  
}