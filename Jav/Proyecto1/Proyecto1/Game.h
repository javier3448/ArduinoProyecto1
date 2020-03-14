// Game.h

#ifndef _GAME_h
#define _GAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Crane.h"
#include "LedMatrix.h"
#include "Slide.h"

class Game
{
private:
	static const byte S_GAME_OVER = 0;
	static const byte S_LOSER_RETRIEVING = 1;
	static const byte S_PLAYING = 2;
	static const byte S_PLAYING_W_PRIZE = 3;
	static const byte S_WAIT_FOR_PRIZE = 4;
	static const byte S_WINNER_RETRIEVING = 5;
	static const byte S_DROPPING = 6;
	
	static const unsigned long BLINK_PERIOD = 500;
	static const unsigned long PRIZE_WAIT_PERIOD = 2000;
	
	Crane crane;
	LedMatrix ledMatrix;
	Slide slide;
	
	byte currState = S_GAME_OVER;
	unsigned long stateStartTime = 0;
	byte lastXBeforeCatch = 0;
	byte lastYBeforeCatch = 0;
	byte lastResult = R_NONE;
	bool blinkToggle = false;//Solo para saber si tiene que prender o apagar el led que va a blinkear
	
	unsigned long lastUpdateBlinked = 0;
	
	void playTune();
	void printCraneData();//debug
public:

	static const byte R_NONE = 0;//R significa resilt
	static const byte R_PLAYING = 1;
	static const byte R_WON = 2;
	static const byte R_LOST = 3;

	static const byte PIN_BUZZER = 22;//los pines lo deberiamos de enviar como parametro al construir el objeto, porque esto es una clase y en principio deberian de poder existir varias instancias todas con pines diferentes
	static const byte PIN_DOOR = 8;//Probar porque la vez pasada parecia no funcionar el puente h en este pin
	static const byte PIN_HAS_PRIZE_SLIDE_E = 25;
	static const byte PIN_HAS_PRIZE_SLIDE_T = 26;
	static const byte PIN_HAS_PRIZE_CRANE = 27;

	Game();
	
	setup();
	
	//Retorna falso si no pudo empezar el nuevo juego, solo se puede empezar un nuevo juego si currState es GAME_OVER
	bool tryStart();
	//Retorna si gano, esta jugando, perdio o esta en modo gameover
	//Recive la entradas analogas DE 10 BITS de los ejes x y y del joystick
	byte update(bool _catch, bool drop);
	
	friend void setup();
	friend void loop();
	
};

#endif

