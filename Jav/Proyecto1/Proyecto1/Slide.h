// Slide.h

#ifndef _SLIDE_h
#define _SLIDE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Servo.h>
#include "UsSensor.h"

class Slide
{
private:
	Servo servo;
	UsSensor usSensor;

	byte hasPrizePin;
	bool hasPrize = false;
	bool hadPrize = false;
	bool doorOpen = false;
	
	static const unsigned int HAS_PRIZE_DISTANCE = 80;
	
	byte servoPin;

public:
	Slide(byte hasPrizeEchoPin, byte hasPrizeTriggerPin, byte doorPin);
	
	void update();
	
	byte getHasPrize();
	byte getHadPrize();
	
	void open();
	void close();
	
	bool isDoorOpen();
};

#endif

