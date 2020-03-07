// Engine.h

#ifndef _ENGINE_h
#define _ENGINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace XyzEngine 
{
	
	
	//Constantes
	namespace Pin
	{
		const byte MOTOR_X1 = 4;
		const byte MOTOR_X2 = 5;
		const byte MOTOR_Y1 = 2;
		const byte MOTOR_Y2 = 3;
		const byte MOTOR_Z1 = 6;
		const byte MOTOR_Z2 = 7;
	}

	extern byte xPower;
	extern byte yPower;
	extern byte zPower;
	
	//La variables velocity sirven para no mandar analog writes a los motores cuando no sea necesario
	
	extern char xVelocity;
	extern char yVelocity;
	extern char zVelocity;
	
	//TODO: Conseguir mejores nombres para estos metodos:

	void init();
	void xStop();
	void xFoward();
	void xReverse();
	void yStop();
	void yFoward();
	void yReverse();
	void zStop();
	void zFoward();
	void zReverse();
}

#endif

