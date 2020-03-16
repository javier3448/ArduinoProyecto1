#include "MyArray.h"
#include "Slide.h"
#include "Crane.h"
#include "Game.h"

//#include <Servo.h>
//#include "Slide.h"
//#include "Game.h"
//#include "Crane.h"
//#include "LedMatrix.h"
/*
 * Proyecto1.ino
 *
 * Created: 3/3/2020 4:52:55 PM
 * Author: Javier
 */ 


//Game game = Game();
//
//const byte PIN_X_AXIS = A0;
//const byte PIN_Y_AXIS = A1;
//const byte PIN_CATH_BTN = 23;
//const byte PIN_DROP_BTN = 24;
//
//UsSensor us = UsSensor(26, 25);
//
//void setup()
//{
	//Serial.begin(9600);
	//Serial.print("try start ");
	//Serial.println(game.tryStart());
	//
	//pinMode(PIN_CATH_BTN, INPUT_PULLUP);
	//pinMode(PIN_DROP_BTN, INPUT_PULLUP);
//}
//
//bool wasCatchPressed = false;
//bool isCatchPressed = false;
//
//bool wasDropPressed = false;
//bool isDropPressed = false;
//
//void loop()
//{
	//updateCatchAndDrop();
	//bool drop = !wasDropPressed && isDropPressed /*|| android.getInput*/;
	//bool _catch = !wasCatchPressed && isCatchPressed /*|| android.getInput*/;
	//
	//game.update(_catch, drop);
	//Serial.print("catch: " );
	//Serial.println(_catch);
	//
//}
//
//void updateCatchAndDrop(){
	//wasCatchPressed = isCatchPressed;
	//wasDropPressed = isDropPressed;
	//isCatchPressed = !digitalRead(PIN_CATH_BTN);
	//isDropPressed = !digitalRead(PIN_DROP_BTN);
//}

#include "Game.h"
#include "Android.h"

//beg Raul melyza

int ficha1 = 32;
int ficha50 = 33;
int ficha25 = 34;

/*Cantidad de fichas*/
int ficha1C = 0;
int ficha50C = 0;
int ficha25C = 0;
double restante = 0;
double total = 0;//SOLO PARA DEBUGGING. TODO: PONERLO EN 0

byte state = 0;
//end Raul melyza

Game game;
const byte PIN_CATH_BTN = 23;
const byte PIN_DROP_BTN = 24;
bool wasCatchPressed = false;
bool isCatchPressed = false;

bool wasDropPressed = false;
bool isDropPressed = false;

void setup() {
	Serial.begin(9600);
	Serial2.begin(38400);
	pinMode(ficha1, INPUT);
	pinMode(ficha50, INPUT);
	pinMode(ficha25, INPUT);
  
	pinMode(PIN_CATH_BTN, INPUT_PULLUP);//My
	pinMode(PIN_DROP_BTN, INPUT_PULLUP);//My
	
	Serial.println("HOLA");
	game.setup();
}

void loop() {
	switch(state){
		case 0:
			countCoins();
			updateGame();
		break;
		case 1:
			updateCatchAndDrop();
			movesAndroid();
			updateGame();
		break;
	}
}

void updateGame(){
	switch(game.update((!wasCatchPressed && isCatchPressed) || Android::flagCatch, (!wasDropPressed && isDropPressed) || Android::flagCatch)){
		case Game::R_NONE: //non
			Serial.println("none");
		break;
			case Game::R_PLAYING: //playing
			Serial.println("playing");
		break;
		case Game::R_WON: //won
			Serial.println("won");
			state = 0;
			Serial2.write("000#");
		break;
		case Game::R_LOST: //lost
			Serial.println("Lost");
			Serial2.write("111#");
			state = 0;
		break;
	}
}

void updateCatchAndDrop(){
	wasCatchPressed = isCatchPressed;
	wasDropPressed = isDropPressed;
	isCatchPressed = !digitalRead(PIN_CATH_BTN);
	isDropPressed = !digitalRead(PIN_DROP_BTN);
}

//RAUL Y MELYZA beggin
void movesAndroid(){
	if(Serial2.available() > 0){
		String input = Serial2.readString();
		if(input.length() == 2){
			updateAndroid(input);
		}
		else{
			MyArray a = getMoves(input);
			for(int i = 0; i < sizeof(a.moves) / sizeof(*a.moves); i++){//se hicieron cambios
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
}

MyArray getMoves(String input){
  MyArray a;
  int cont = 0;
  char contMyArray = 0;
  String aux = "";
  
  for(int i = 0; i < input.length(); i++){
    aux += input.charAt(i);
    cont++;
    if(cont == 2){
      a.moves[contMyArray] = aux;
      cont = 0;
      aux = "";
      contMyArray++;
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
	game.tryStart();//my
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
//RAUL Y MELYZA end