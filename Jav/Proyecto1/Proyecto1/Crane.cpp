// 
// 
// 

#include "Crane.h"

//TODO TESTEAR MUCHISIMO Y LEERLA BIEN BIEN

Crane::Crane()
{
	XyzEngine::init();
	currStateStartTime = millis();
}

void Crane::update()
{
	switch(currState){
		case S_RESTING:
			//Do nothing
			break;
		case S_PLAYING:
			updatePlaying();
			break;
		case S_CATCHING_PRIZE:
			updateCatchingPrize();
			break;
		case S_RETRIEVING:
			updateRetrieving();
			break;
	}
}

void Crane::updatePlaying()
{
	if (lastXVelocity != 0){
		xTime += lastXVelocity * (millis() - lastUpdated);//todo revisar bien que da este resultado el usar unsigned long, char y long talvez da comportamientos extrannos
	}
	if (lastYVelocity != 0){
		yTime += lastYVelocity * (millis() - lastUpdated);
	}
	
	if(xTime >= MAX_X_TIME || xTime <= 0){
		lastXVelocity = 0;
		currXVelocity = 0;
	}
	if(yTime >= MAX_Y_TIME || yTime <= 0){
		lastXVelocity = 0;
		currXVelocity = 0;
	}
	
	lastXVelocity = currXVelocity;
	lastYVelocity = currYVelocity;
	
	if(lastXVelocity < 0){
		XyzEngine::xReverse();
	}
	else if(lastXVelocity > 0){
		XyzEngine::xFoward();
	}
	else{
		XyzEngine::xStop();
	}
	
	if(lastXVelocity < 0){
		XyzEngine::yReverse();
	}
	else if(lastXVelocity > 0){
		XyzEngine::yFoward();
	}
	else{
		XyzEngine::yStop();
	}
	
	lastUpdated = millis();
}

void Crane::updateCatchingPrize()
{
	if(millis() - currStateStartTime < LOWERING_TIME)
	{
		XyzEngine::zFoward();
	}
	else if (millis() - currStateStartTime < LOWERING_TIME * 2)//CONSTANTE QUEMADA
	{
		XyzEngine::zReverse();
	}
	else
	{
		XyzEngine::zStop();
		currState = S_RESTING;
	}
}

void Crane::updateRetrieving()
{
	bool shouldRetrieveX = millis() - currStateStartTime - 100 < xTime;//CONSTANTES (100) QUEMADA
	bool shouldRetrieveY = millis() - currStateStartTime - 100 < yTime;
	
	if(shouldRetrieveX){
		XyzEngine::xReverse();	
	}
	if(shouldRetrieveY){
		XyzEngine::yReverse();
	}
	if(!shouldRetrieveX && !shouldRetrieveY){
		xTime = 0;
		yTime = 0;
		currState = S_RESTING;
	}
}

void Crane::setState(byte state)//Esta algo chapuceado, revisar el flujo 
{
	if(state != S_RESTING &&
		state != S_PLAYING &&
		state != S_RETRIEVING &&
		state != S_CATCHING_PRIZE)
	if(currState == S_CATCHING_PRIZE || currState == S_RETRIEVING)//NO PODEMOS SALIRNOS DE UN ESTADO AUTOMATICO DESDE AFUERA DE LA CLASE
	{
		Serial.println("No se puede de cambiar de estado mientras esta corriendo un estado automatico");//Solo para debugging
		return;
	}
	
	if (currState == state)
		return;
	
	//Para poder detener la garra en estado playing sin perder info de cuanto tiempo se estubo moviendo en cierta direccion tenemos que:
	//poner los currVelocity en 0 y correr el update al menos dos 
	if(state != S_PLAYING && currState == S_PLAYING){//Si nuestor siguiente estado no es playing y el estaado actual es playing
		currXVelocity = 0;
		currYVelocity = 0;
		if(lastXVelocity != 0 || lastYVelocity != 0){
			updatePlaying();
			updatePlaying();
		}
	}
	
	switch (state)
	{
		case S_RESTING:
			currState = S_RESTING;
		break;
		case S_PLAYING :
			currState = S_PLAYING;
			currStateStartTime = millis();
			lastUpdated = millis();
			updatePlaying();
		break;
		case S_RETRIEVING :
			currState = S_RETRIEVING;
			currStateStartTime = millis();
			updateRetrieving();
		break;
		case S_CATCHING_PRIZE:
			currState = S_CATCHING_PRIZE;
			currStateStartTime = millis();
			updateRetrieving();
		break;
		default:
			Serial.println("!!! state no valido");//Solo para debugging
		break;
	}
}

byte Crane::getState()
{
	return currState;
}

void Crane::setXVelocity(char xVelocity)
{
	if(xVelocity < 0){
		currXVelocity = -1;
	}else if(xVelocity > 0){
		currXVelocity = 1;
	}else{
		currXVelocity = 0;
	}
}

void Crane::setYVelocity(char yVelocity)
{
	if(yVelocity < 0){
		currYVelocity = -1;
	}else if(yVelocity > 0){
		currYVelocity = 1;
	}else{
		currYVelocity = 0;
	}
}

byte Crane::getXPos()
{
	return (byte) map(xTime, 0, MAX_X_TIME, 0, 8);//Constante quemada
}

byte Crane::getYPos()
{
	return (byte) map(yTime, 0, MAX_Y_TIME, 0, 8);//Constante quemada
}

bool Crane::hasPrize()
{	
	return false;//TODO poner un sensor que determine si tiene o no juguete
}

char Crane::getXVelocity()
{
	return currXVelocity;
}

char Crane::getYVelocity()
{
	return currYVelocity;
}

