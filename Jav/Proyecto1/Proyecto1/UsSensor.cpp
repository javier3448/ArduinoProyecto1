// 
// 
// 

#include "UsSensor.h"

UsSensor::UsSensor(byte triggerPin, byte echoPin)
{
	this->triggerPin = triggerPin;
	this->echoPin = echoPin;
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

unsigned int UsSensor::getDistance()
{
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);

	unsigned int result = pulseIn(echoPin, HIGH, 10000);

	if (result == 0) {
		result = 0xffff;
	}

	return result;
}
