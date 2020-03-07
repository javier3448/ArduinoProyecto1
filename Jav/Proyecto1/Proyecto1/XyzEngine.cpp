// 
// 
// 

#include "XyzEngine.h"

using namespace XyzEngine::Pin;

extern byte XyzEngine::xPower = 0xff;//para debugging vamos a usar menos potencia
extern byte XyzEngine::yPower = 0xff;
extern byte XyzEngine::zPower = 0xff;

extern char XyzEngine::xVelocity = 0;//para debugging vamos a usar menos potencia
extern char XyzEngine::yVelocity = 0;
extern char XyzEngine::zVelocity = 0;

void XyzEngine::init()
{
	pinMode(MOTOR_X1, OUTPUT);
	digitalWrite(MOTOR_X1, LOW);
	pinMode(MOTOR_X2, OUTPUT);
	digitalWrite(MOTOR_X2, LOW);
	pinMode(MOTOR_Y1, OUTPUT);
	digitalWrite(MOTOR_Y1, LOW);
	pinMode(MOTOR_Y2, OUTPUT);
	digitalWrite(MOTOR_Y2, LOW);
	pinMode(MOTOR_Z1, OUTPUT);
	digitalWrite(MOTOR_Z1, LOW);
	pinMode(MOTOR_Z2, OUTPUT);
	digitalWrite(MOTOR_Z2, LOW);
}

void XyzEngine::xStop()
{
	if(xVelocity != 0){
		digitalWrite(MOTOR_X1, LOW);
		digitalWrite(MOTOR_X2, LOW);
		xVelocity = 0;
	}
}

void XyzEngine::xFoward()
{
	if(xVelocity != 1){
		digitalWrite(MOTOR_X1, LOW);
		analogWrite(MOTOR_X2, xPower);
		xVelocity = 1;
	}
}

void XyzEngine::xReverse()
{
	if(xVelocity != -1){
		analogWrite(MOTOR_X1, xPower);
		digitalWrite(MOTOR_X2, LOW);
		xVelocity = -1;
	}
}

void XyzEngine::yStop()
{
	if(yVelocity != 0){
		digitalWrite(MOTOR_Y1, LOW);
		digitalWrite(MOTOR_Y2, LOW);
		yVelocity = 0;
	}
}

void XyzEngine::yFoward()
{
	if(yVelocity != 1){
		digitalWrite(MOTOR_Y1, LOW);
		analogWrite(MOTOR_Y2, yPower);
		yVelocity = 1;
	}
}

void XyzEngine::yReverse()
{
	if(yVelocity != -1){
		analogWrite(MOTOR_Y1, yPower);
		digitalWrite(MOTOR_Y2, LOW);
		yVelocity = -1;
	}
}

void XyzEngine::zStop()
{
	if(zVelocity != 0){
		digitalWrite(MOTOR_Z1, LOW);
		digitalWrite(MOTOR_Z2, LOW);
		zVelocity = 0;
	}
}

void XyzEngine::zFoward()
{
	if(zVelocity != 1){
		digitalWrite(MOTOR_Z1, LOW);
		analogWrite(MOTOR_Z2, zPower);
		zVelocity = 1;
	}
}

void XyzEngine::zReverse()
{
	if(zVelocity != -1){
		analogWrite(MOTOR_Z1, zPower);
		digitalWrite(MOTOR_Z2, LOW);
		zVelocity = -1;
	}
}