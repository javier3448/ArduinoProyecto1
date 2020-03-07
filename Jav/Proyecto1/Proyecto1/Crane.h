// Crane.h

#ifndef _CRANE_h
#define _CRANE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "XyzEngine.h"

//Asumimos que crane esta en pos (0, 0) en la vida real al inicializar la var
class Crane
{
 private:
	//Agregar el sensor de distancia para ver si sostiene premio
 
	static const unsigned long LOWERING_TIME = 1000;//Tiempo que tarda en bajar la garra, vamos a asumir que es el mismo para subir
	static const unsigned long MAX_X_TIME = 1000;//Tiempo que tarda en llegar de 0 x a el tope en x de la garra
	static const unsigned long MAX_Y_TIME = 1000;//Tiempo que tarda en llegar de 0 x a el tope en x de la garra
 
	byte xPos = 0;
	byte yPos = 0;

	//Tiempo que tendrian que estar el motorX avanzando para llegar a xPos partiendo de posicion (0, ?)
	unsigned long xTime = 0;
	//Tiempo que tendrian que estar el motorY 'avanzando' para llegar a yPos partiendo de posicion (?, 0)
	unsigned long yTime = 0;

	unsigned long currStateStartTime = 0;
	unsigned long lastUpdated = 0;

	char lastXVelocity = 0;
	char lastYVelocity = 0;

	char currXVelocity = 0;
	char currYVelocity = 0;

	byte currState = 0;

 public:
 
	static const byte S_RESTING = 0;
	static const byte S_PLAYING = 1;
	static const byte S_RETRIEVING = 2;
	static const byte S_CATCHING_PRIZE = 3;
 
	Crane();
	
	void update();
	
	void updatePlaying();
	void updateCatchingPrize();
	void updateRetrieving();
	
	//sets y gets de currVelocities son solo para proteger que curr velocities solo puedan tomar 3 valores: -1, 0, 1
	
	void setState(byte state);
	byte getState();
	
	char getXVelocity();
	char getYVelocity();
	void setXVelocity(char xVelocity);
	void setYVelocity(char yVelocity);
	byte getXPos();
	byte getYPos();
	
	bool hasPrize();
};

#endif

