#include "Android.h"
  
typedef struct{
  String moves[16] = {};
}Array;

int ficha1 = 32;
int ficha50 = 33;
int ficha25 = 34;

/*Cantidad de fichas*/
int ficha1C = 0;
int ficha50C = 0;
int ficha25C = 0;
double restante = 0;
double total = 0;

byte state = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(38400);
  pinMode(ficha1, INPUT);
  pinMode(ficha50, INPUT);
  pinMode(ficha25, INPUT);
}

void loop() {
  switch(state){
    case 0:
    countCoins();
    break;
    case 1:
    movesAndroid();
    break;
  }
}

void movesAndroid(){
  
  if(Serial2.available() > 0){
    String input = Serial2.readString();
    if(input.length() == 2){
      updateAndroid(input);
    }else{
      Array a = getMoves(input);
      for(int i = 0; i < 50; i++){
        if(!a.moves[i].equals("")){
          updateAndroid(a.moves[i]);
        }
      }
    }
  }
  
}

void updateAndroid(String input){
  if(input.equals("a1")){//Left move
    Android::velocityX = -1;
    Serial.println("Moving to the left");
  }else if(input.equals("a0")){//Left stop
    Android::velocityX = 0;
  }else if(input.equals("s1")){//Backward move
    Android::velocityY = -1;
    Serial.println("Moving backward");
  }else if(input.equals("s0")){//Backward stop
    Android::velocityY = 0;
  }else if(input.equals("d1")){//Right move   
    Android::velocityX = 1;
    Serial.println("Moving to the rigth");
  }else if(input.equals("d0")){//Rigth stop
    Android::velocityX = 0;
  }else if(input.equals("w1")){//Forward move
    Android::velocityY = 1;
    Serial.println("Moving forward");
  }else if(input.equals("w0")){//Forward stop
    Android::velocityY = 0;
  }else if(input.equals("ca")){//Catch
    Android::flagCatch = true;
    Serial.println("Catching");
  }else if(input.equals("dr")){//Drop
    Android::flagDrop = true;
    Serial.println("Droping");
  }
  //Javi function
  /*
  int javi = 2;
  switch(javi){
    case 0: //non
    break;
    case 1: //playing
    break;
    case 2: //won
    state = 0;
    Serial2.write("000#");
    break;
    case 3: //lost
    Serial2.write("111#");
    state = 0;
    break;
  }*/
  
}

Array getMoves(String input){
  Array a;
  int cont = 0;
  char contArray = 0;
  String aux = "";
  
  for(int i = 0; i < input.length(); i++){
    aux += input.charAt(i);
    cont++;
    if(cont == 2){
      a.moves[contArray] = aux;
      cont = 0;
      aux = "";
      contArray++;
    }
  }
  
  return a;
}

/* ---------------- COINS ---------------- */
void countCoins(){
  if(total < 1.00){
      if(digitalRead(ficha1)==0){ 
        total = total + 1.00;
        ficha1C++;
        Serial2.write(cadenaFichas(1).c_str());
        Serial.println(cadenaFichas(1).c_str());
        Serial.println("Q.1.00");
        delay(200);
      }else if(digitalRead(ficha25)==0){
        total = total+ 0.25;
        ficha25C++;
        Serial2.write(cadenaFichas(3).c_str());
        Serial.println(cadenaFichas(3).c_str());
        Serial.println("Q.0.25");
        delay(200);
      }else if(digitalRead(ficha50)==0){
        total = total+ 0.50;
        ficha50C++;
        Serial2.write(cadenaFichas(2).c_str());
        Serial.println(cadenaFichas(2).c_str());
        Serial.println("Q.0.50");
        delay(200);
      }
  }else{
    state = 1;
    total = 0;
    ficha1C = 0;
    ficha50C = 0;
    ficha25C = 0;
    Serial.println("Start game");
    Serial2.write("77777777#");
    delay(100);
  }
}

String cadenaFichas(int ingresada){
  String c = "";
  c+= " ";
  c+= ingresada;
  c+= ",1";
  c+= ficha1C;
  c+= ",2";
  c+= ficha50C;
  c+= ",3";
  c+= ficha25C;
  c+= ",#"; 
  return c;
}
