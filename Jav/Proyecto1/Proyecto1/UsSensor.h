// UsSensor.h

#ifndef _USSENSOR_h
#define _USSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class UsSensor
{
private:
	byte triggerPin;
	byte echoPin;
	 

public:
	UsSensor(byte triggerPin, byte echoPin);
	
	unsigned int getDistance();
};


#endif

