// 
// 
// 

#include "Slide.h"

Slide::Slide(byte hasPrizeEchoPin, byte hasPrizeTriggerPin, byte doorPin) : usSensor(hasPrizeTriggerPin, hasPrizeEchoPin)
{
	this->servoPin = doorPin;
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
	servo.write(135);
}

void Slide::close()
{
	Serial.println("SE CERRO LA PUERTA");
	doorOpen = false;
	servo.write(0);
}

bool Slide::isDoorOpen()
{
	return doorOpen;
}

void Slide::setup()
{
	Serial.print("SERVO PIN: ");
	Serial.println(servoPin);
	servo.attach(servoPin);
	close();
}
