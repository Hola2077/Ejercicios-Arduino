////Incubadora hecha con arduino y sensor DHT11////
#include "DHT.h"
#include "Servo.h"
#define DHTPIN 3
#define DHTMARCA DHT11
DHT dht(DHTPIN, DHTMARCA);
Servo servo;
unsigned long tienpo = 0;
const int anguloA = 50;
const int anguloB = 110;
bool sel = false;
unsigned long tin = 0;
void setup() {
  dht.begin();
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(5,OUTPUT);
  servo.attach(4);
}

void loop() {
  
    if(dht.readTemperature() < 37.5){
      Serial.println("");
      Serial.print("Calentado ");
      Serial.print(dht.readTemperature()); Serial.print(" ");
      Serial.println(dht.readHumidity());
      digitalWrite(2,HIGH);
    }else{
      Serial.println("");
      Serial.print("Temperatura Correcta ");
      Serial.print(dht.readTemperature()); Serial.print(" ");
      Serial.println(dht.readHumidity());
      digitalWrite(2,LOW);
    }

    if(dht.readHumidity() < 50){
      sonido();
    }

    if(dht.readHumidity() > 65){
      sonidoB();
    }

      if(millis() - tienpo > 3600000){
        tienpo = millis();
        switch(sel){
          case false: servo.write(anguloA); sel = true;
          break;
          case true: servo.write(anguloB); sel = false;
          break;
        }
      }
      
}

void sonido(){
  if(millis() - tin > 2000){
    tin = millis();
    digitalWrite(5,HIGH);
  }else{digitalWrite(5,LOW);}
}

void sonidoB(){
  if(millis() - tin > 200){
    tin = millis();
    digitalWrite(5,HIGH);
  }else{digitalWrite(5,LOW);}
}