// 
// 
// 

#include "Slide.h"

Slide::Slide(byte hasPrizeEchoPin, byte hasPrizeTriggerPin, byte doorPin) : usSensor(hasPrizeTriggerPin, hasPrizeEchoPin)
{
	servo = Servo();
	this->servoPin = doorPin;
	servo.attach(doorPin);
	doorOpen = false;
	servo.write(100);
}

void Slide::update()
{
	hadPrize = hasPrize;
	
	//hasPrize = digitalRead(hasPrizePin);//DESCONECTAR Y ARMAR SENSOR DE HASPRIZE
	hasPrize = usSensor.getDistance() < HAS_PRIZE_DISTANCE;
}

void Slide::updateServo()
{
	if(doorOpen){
		servo.write(0);
	}
	else{
		servo.write(135);
	}
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
	servo.write(0);
}

void Slide::close()
{
	Serial.println("SE CERRO LA PUERTA");
	doorOpen = false;
	servo.write(100);
	 
}

bool Slide::isDoorOpen()
{
	return doorOpen;
}
