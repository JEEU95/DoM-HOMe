/*
  Proyecto final de probabilidad y estadística
  Autor: Jorge Encalada
  Tema: Casa domótica
*/

#include <Servo.h>
//inclusión de servo motores
Servo servoV1;
Servo servoV2;
Servo servoV3;
Servo servoP;

char terminal; //variable para las lecturas bluetooth

int alarma=12;
int ledA=13;
int led1=7;
int led2=8;
int led3=9;
int puerta=3;
int ventana1=2;
int ventana2=5;
int ventana3=4;


int lucesLDR= A0;
int alarmaLDR= A1;


int valAlarmaLDR=0;
int valLucesLDR=0;


bool activarA=false;
bool ctrlA=false;

bool activarL=false;
bool ctrlL=false;
void setup() {
  Serial.begin(9600);
  pinMode(alarma,OUTPUT);
  pinMode(ledA, OUTPUT);
  pinMode(ventana1,OUTPUT);
  pinMode(ventana2,OUTPUT);
  pinMode(ventana3,OUTPUT);
  pinMode(puerta,OUTPUT);

  pinMode(alarmaLDR, INPUT);
  pinMode(lucesLDR, INPUT);

  servoV1.attach(ventana1, 640, 2450);
  servoV2.attach(ventana2, 640, 2450);
  servoV3.attach(ventana3, 640, 2450);
  servoP.attach(puerta, 640, 2450);
}

void loop() {
  if(Serial.available()>0){ //si existe alguna señal

    terminal=Serial.read(); //Leer señal recibida
    delay(2);
   Serial.println(terminal);


   if (terminal=='1'){
      //abrir
      servoV1.write(65);
      Serial.println("Abrir Ventana 1");
      delay(5);
    }
    if(terminal=='2'){
      //cerrar
      servoV1.write(3);
      Serial.println("Cerrar Ventana 1");
      delay(5);
    }
    if (terminal=='3'){
      digitalWrite(led1, HIGH);
      Serial.println("Foco 1 Prendido");      
      delay(5);
    }if (terminal=='4'){
      digitalWrite(led1, LOW);
      Serial.println("Foco 1 Apagado");      
      delay(5);
    }if (terminal=='5'){
      //abrir
      servoV3.write(65);
      Serial.println("Abrir Ventana 3");
      delay(5);
    }
    if(terminal=='6'){
      //cerrar
      servoV3.write(3);
      Serial.println("Cerrar Ventana 3");
      delay(5);
    }if (terminal=='7'){
      digitalWrite(led2, HIGH);
      Serial.println("Foco 2 Prendido");            
      delay(5);
    }if (terminal=='8'){
      digitalWrite(led2, LOW);
      Serial.println("Foco 2 Apagado");      
      delay(5);
    }if (terminal=='9'){
      //abrir
      servoP.write(65);
      Serial.println("Abrir Puerta");
      delay(5);
    }
    if(terminal=='a'){
      //cerrar
      servoP.write(3);
      Serial.println("Cerrar Puerta");
      delay(5);
    }
    if (terminal=='b'){
      activarA=true;
      
      Serial.println("Alarma Activada");      
      delay(5);
    }if (terminal=='c'){
      activarA=false;
      
      Serial.println("Alarma Desactivada");      
      delay(5);
    }
    if (terminal=='d'){
      //abrir
      servoV2.write(65);
      Serial.println("Abrir Ventana 2");
      delay(5);
    }
    if(terminal=='e'){
      //cerrar
      servoV2.write(3);
      Serial.println("Cerrar Ventana 2");
      delay(5);
    }
    if (terminal=='f'){
      digitalWrite(led3, HIGH);
      Serial.println("Foco 3 Prendido");      
      delay(5);
    }if (terminal=='g'){
      digitalWrite(led3, LOW);
      Serial.println("Foco 3 Apagado");      
      delay(5);
    }if (terminal=='h'){
      activarL=true;
      Serial.println("Sensor de Luces Activada");            
      delay(5);
    }if (terminal=='i'){
      activarL=false;
      Serial.println("Sensor de Luces Desactivada");            
      delay(5);
    }
  }

  if(activarA==true){
    ctrlA=true;
    valAlarmaLDR= analogRead(alarmaLDR);  //leer el valor de la fotoresistencia de la alarma
    Serial.println(valAlarmaLDR);
    
    if (valAlarmaLDR >= 300) {
      //activar alarma
      Serial.println("----------- ALARMA ACTIVADA-----------"); 
      tone(alarma, 100);
      digitalWrite(ledA, HIGH);
      delay(100);
      
      noTone(alarma);
      digitalWrite(ledA, LOW);
      delay(100);
    }
    else {
      //desactivar alarma
      noTone(alarma);
      digitalWrite(ledA, LOW);
      Serial.println("----------ALARMA NO ACTIVADA-----------");
      delay(5000);
    }
    
  }
  if (activarA==false && ctrlA==true){
    //desactivar alarma
    ctrlA=false;
    noTone(alarma);
    digitalWrite(ledA, LOW);
    Serial.println("----------ALARMA DESACTIVADA!!!-----------");
    delay(5000);
  }

  if(activarL==true){
    ctrlL=true;
    valLucesLDR= analogRead(lucesLDR);  //leer el valor de la fotoresistencia de la alarma
    Serial.println(valLucesLDR);
    
    if (valLucesLDR >= 140) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      Serial.println("----------LUCES ENCENDIDAS-----------");
      delay(5);
    }else{
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      Serial.println("----------LUCES APAGADAS-----------");  
      delay(5);
    }
    
  }
  if (activarL==false && ctrlL==true){
    //desactivar luces
    ctrlL=false;
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW); 
    Serial.println("----------SENSOR DE LUCES DESACTIVADO!!!-----------"); 
    delay(5);
  }
}
