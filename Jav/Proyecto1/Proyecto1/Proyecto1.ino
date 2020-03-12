#include <Servo.h>
#include "Slide.h"
#include "Game.h"
#include "Crane.h"
#include "LedMatrix.h"
/*
 * Proyecto1.ino
 *
 * Created: 3/3/2020 4:52:55 PM
 * Author: Javier
 */ 

LedMatrix ledMatrix = LedMatrix();

byte x = 0;
byte y = 0;

Game game = Game();

const byte PIN_X_AXIS = A0;
const byte PIN_Y_AXIS = A1;
const byte PIN_CATH_BTN = 23;
const byte PIN_DROP_BTN = 24;

void setup()
{
	Serial.begin(9600);
	Serial.print("try start ");
	Serial.println(game.tryStart());
	
	pinMode(PIN_CATH_BTN, INPUT_PULLUP);
	pinMode(PIN_DROP_BTN, INPUT_PULLUP);
}

bool wasCatchPressed = false;
bool isCatchPressed = false;

bool wasDropPressed = false;
bool isDropPressed = false;

void loop()
{
	updateCatchAndDrop();
	bool drop = !wasDropPressed && isDropPressed /*|| android.getInput*/;
	bool _catch = !wasCatchPressed && isCatchPressed /*|| android.getInput*/;
	
	game.update(_catch, drop);
	Serial.print("catch: " );
	Serial.println(_catch);
}

void updateCatchAndDrop(){
	wasCatchPressed = isCatchPressed;
	wasDropPressed = isDropPressed;
	isCatchPressed = !digitalRead(PIN_CATH_BTN);
	isDropPressed = !digitalRead(PIN_DROP_BTN);
}

