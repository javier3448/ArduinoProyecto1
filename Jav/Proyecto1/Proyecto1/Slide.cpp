// 
// 
// 

#include "Slide.h"

Slide::Slide(byte hasPrizeEchoPin, byte hasPrizeTriggerPin, byte doorPin)
{
	this->hasPrizePin = hasPrizePin;
	pinMode(hasPrizePin, INPUT);
	servo = Servo();
	servo.attach(doorPin);
	usSensor = UsSensor(hasPrizeTriggerPin, hasPrizeEchoPin);
	pinMode(doorPin, OUTPUT);
	servo.attach(doorPin);
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
	doorOpen = true;
	servo.write(90);
}

void Slide::close()
{
	doorOpen = false;
	servo.write(0);
}

bool Slide::isDoorOpen()
{
	return doorOpen;
}
