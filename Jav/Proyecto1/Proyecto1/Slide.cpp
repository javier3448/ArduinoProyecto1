// 
// 
// 

#include "Slide.h"

Slide::Slide(byte hasPrizeEchoPin, byte hasPrizeTriggerPin, byte doorPin) : usSensor(hasPrizeTriggerPin, hasPrizeEchoPin)
{
	this->servoPin = doorPin;
	doorOpen = false;
}

void Slide::update()
{
	hadPrize = hasPrize;
	
	//hasPrize = digitalRead(hasPrizePin);//DESCONECTAR Y ARMAR SENSOR DE HASPRIZE
	hasPrize = usSensor.getDistance() < HAS_PRIZE_DISTANCE;
}

byte Slide::getHasPrize()
{
	return hasPrize;
}

byte Slide::getHadPrize()
{
	return hadPrize;
}

void Slide::open()
{
	Serial.println("SE ABRIO LA PUERTA");
	doorOpen = true;
	digitalWrite(PIN_DOOR0, HIGH);
	delay(150);
	digitalWrite(PIN_DOOR0, LOW);
}

void Slide::close()
{
	Serial.println("SE CERRO LA PUERTA");
	doorOpen = false;
	digitalWrite(PIN_DOOR1, HIGH);
	delay(150);
	digitalWrite(PIN_DOOR1, LOW);
}

bool Slide::isDoorOpen()
{
	return doorOpen;
}

void Slide::setup()
{
	pinMode(PIN_DOOR0, OUTPUT);
	digitalWrite(PIN_DOOR0, LOW);
	pinMode(PIN_DOOR1, OUTPUT);
	digitalWrite(PIN_DOOR1, LOW);
}
