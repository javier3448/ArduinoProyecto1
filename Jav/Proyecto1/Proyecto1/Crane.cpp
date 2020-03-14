// 
// 
// 

#include "Crane.h"
#include "Android.h"

//TODO TESTEAR MUCHISIMO Y LEERLA BIEN BIEN

Crane::Crane(byte yAxisPin, byte xAxisPin, byte hasPrizePin) : PIN_X_AXIS(xAxisPin), PIN_Y_AXIS(yAxisPin) , PIN_HAS_PRIZE(hasPrizePin)
{
	XyzEngine::init();
	currStateStartTime = millis();
	pinMode(PIN_HAS_PRIZE, INPUT);
}

bool Crane::update()
{
	switch(currState){
		case S_RESTING:
			return false;
			break;
		case S_PLAYING:
			updatePlaying();
			return false;
		case S_CATCHING_PRIZE:
			return updateCatchingPrize();
		case S_DROPING_PRIZE:
			return updateDropingPrize();
		case S_RETRIEVING:
			return updateRetrieving();
	}
}

void Crane::updateCurrVelocities()
{
	if(Android::velocityX != 0){
		currXVelocity = Android::velocityX;
	}
	else{
		int xAxis = analogRead(PIN_X_AXIS);
		if(xAxis < 256){
			currXVelocity = -1;
		}
		else if(xAxis > 768){
			currXVelocity = 1;
		}
		else{
			currXVelocity = 0;
		}		
	}
	
	if(Android::velocityY != 0){
		currYVelocity = Android::velocityY;
	}
	else{//Invertimos y por como conectamos el joystick
		int yAxis = analogRead(PIN_Y_AXIS);
		if(yAxis < 256){
			currYVelocity = -1;
		}
		else if(yAxis > 768){
			currYVelocity = 1;
		}
		else{
			currYVelocity = 0;
		}
	}
}

//Asumimos que velocidad solo puede ser -1, 0, 1
void Crane::updatePlaying()
{
	lastXVelocity = currXVelocity;
	lastYVelocity = currYVelocity;
	updateCurrVelocities();
	
	if(currStateStartTime == 0xffffffff){
		currStateStartTime = millis();
	}
	
	if (lastXVelocity > 0){
		xTime += (millis() - lastUpdated);//todo revisar bien que da este resultado el usar unsigned long, char y long talvez da comportamientos extrannos
		if(xTime >= MAX_X_TIME){
			currXVelocity = 0;
			xTime = MAX_X_TIME;
		}
	}
	else if (lastXVelocity < 0){
		unsigned long lastXTime = xTime;
		xTime -= (millis() - lastUpdated);//todo revisar bien que da este resultado el usar unsigned long, char y long talvez da comportamientos extrannos
		if(xTime > lastXTime || xTime == 0){//Chequeamos underflow, algo chapuceado seria mejor . Talvez existan maneras mas idiomaticas de hacerlo pero por ahora sirive
			currXVelocity = 0;
			xTime = 0;
		}
	}
	
	if (lastYVelocity > 0){
		yTime += (millis() - lastUpdated);//todo revisar bien que da este resultado el usar unsigned long, char y long talvez da comportamientos eytrannos
		if(yTime > MAX_Y_TIME){
			currYVelocity = 0;
			yTime = MAX_Y_TIME;
		}
	}
	else if (lastYVelocity < 0){
		unsigned long lastYTime = yTime;
		yTime -= (millis() - lastUpdated);//todo revisar bien que da este resultado el usar unsigned long, char y long talvez da comportamientos eytrannos
		if(yTime > lastYTime){//Chequeamos underflow, algo chapuceado seria mejor . Talvez eyistan maneras mas idiomaticas de hacerlo pero por ahora sirive
			currYVelocity = 0;
			yTime = 0;
		}
	}
	
	if(currXVelocity < 0 && xTime != 0){//va a mover el motor a donde dice currXVel si y solo si y solo si tiene espacio disponible
		XyzEngine::xReverse();
	}
	else if(currXVelocity > 0 && xTime != MAX_X_TIME){//va a mover el motor a donde dice currXVel si y solo si tiene espacio disponible
		XyzEngine::xFoward();
	}
	else{
		XyzEngine::xStop();
	}
	
	if(currYVelocity < 0 && yTime != 0){//va a mover el motor a donde dice currYVel si y solo si y solo si tiene espacio disponible
		XyzEngine::yReverse();
	}
	else if(currYVelocity > 0 && yTime != MAX_Y_TIME){//va a mover el motor a donde dice currYVel si y solo si y solo si tiene espacio disponible
		XyzEngine::yFoward();
	}
	else{
		XyzEngine::yStop();
	}
	
	lastUpdated = millis();
}

bool Crane::updateCatchingPrize()
{
	if(currStateStartTime == 0xffffffff){
		currStateStartTime = millis();
		isDone = false;
	}
	
	if(millis() - currStateStartTime < LOWERING_TIME)
	{
		XyzEngine::zFoward();
	}
	else if (millis() - currStateStartTime < LOWERING_TIME * 2 + RISING_TIME_DIFERENCE)//CONSTANTE QUEMADA
	{
		XyzEngine::zReverse();
	}
	else
	{
		XyzEngine::zStop();
		isDone = true;
	}
	
	return isDone;
}

bool Crane::updateDropingPrize()
{
	if(currStateStartTime == 0xffffffff){
		currStateStartTime = millis();
		isDone = false;
	}
	
	if(millis() - currStateStartTime < DROPING_TIME)
	{
		XyzEngine::zFoward();
	}
	else if (millis() - currStateStartTime < DROPING_TIME * 2)//CONSTANTE QUEMADA
	{
		XyzEngine::zReverse();
	}
	else
	{
		XyzEngine::zStop();
		isDone = true;
	}
	return isDone;
}

bool Crane::updateRetrieving()
{
	if(currStateStartTime == 0xffffffff){//Chapuz?
		currStateStartTime = millis();
		isDone = false;
	}
	
	bool shouldRetrieveX = millis() - currStateStartTime < xTime + 100;//CONSTANTES (100) QUEMADA
	bool shouldRetrieveY = millis() - currStateStartTime < yTime + 100;
	
	Serial.print("            xTime: ");
	Serial.println(xTime);
	Serial.print("            yTime: ");
	Serial.println(yTime);
	
	Serial.print("        shouldRetriveX: ");
	Serial.println(shouldRetrieveX);
	Serial.print("        shouldRetriveY: ");
	Serial.println(shouldRetrieveY);
	
	if(shouldRetrieveX){
		XyzEngine::xReverse();	
	}
	else{
		XyzEngine::xStop();
	}
	if(shouldRetrieveY){
		XyzEngine::yReverse();
	}
	else{
		XyzEngine::yStop();
	}
	
	if(!shouldRetrieveX && !shouldRetrieveY){
		xTime = 0;
		yTime = 0;
		isDone = true;
	}
	
	return isDone;
}

void Crane::setState(byte state)//Esta algo chapuceado, revisar el flujo 
{
	if(state != S_RESTING &&
		state != S_PLAYING &&
		state != S_RETRIEVING &&
		state != S_CATCHING_PRIZE && 
		state != S_DROPING_PRIZE)
	{
		Serial.println("Estado no valido");
		return;
	}
		
	if((currState == S_CATCHING_PRIZE || currState == S_RETRIEVING || currState == S_DROPING_PRIZE) && !isDone)//NO PODEMOS SALIRNOS DE UN ESTADO AUTOMATICO DESDE AFUERA DE LA CLASE
	{
		Serial.println("No se puede de cambiar de estado mientras esta corriendo un estado automatico");//Solo para debugging
		return;
	}
	
	if (currState == state)//Deberiamos de actualizar el estado actual aqui tambien?
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
			isDone = false;
			currStateStartTime = 0xffffffff;
		break;
		case S_RETRIEVING :
			currState = S_RETRIEVING;
			isDone = false;
			currStateStartTime = 0xffffffff;
		break;
		case S_CATCHING_PRIZE:
			currState = S_CATCHING_PRIZE;
			isDone = false;
			currStateStartTime = 0xffffffff;
		break;
		case S_DROPING_PRIZE:
			currState = S_DROPING_PRIZE;
			currStateStartTime = 0xffffffff;
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
	return (byte) map(xTime, 0, MAX_X_TIME, 0, 7);//Constante quemada
}

byte Crane::getYPos()
{
	return (byte) map(yTime, 0, MAX_Y_TIME, 0, 7);//Constante quemada
}

bool Crane::hasPrize()
{	
	return !digitalRead(PIN_HAS_PRIZE);//TODO poner un sensor que determine si tiene o no juguete
}

char Crane::getXVelocity()
{
	return currXVelocity;
}

char Crane::getYVelocity()
{
	return currYVelocity;
}

