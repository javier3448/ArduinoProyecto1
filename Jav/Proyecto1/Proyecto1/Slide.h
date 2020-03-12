// Slide.h

#ifndef _SLIDE_h
#define _SLIDE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Servo.h>

class Slide
{
private:
	Servo servo;

	byte hasPrizePin;
	bool hasPrize = false;
	bool hadPrize = false;
	bool doorOpen = false;
	
	byte servoPin;

public:
	Slide(byte hasPrizePin, byte doorPin);
	
	void update();
	
	byte getHasPrize();
	byte getHadPrize();
	
	void open();
	void close();
	
	bool isDoorOpen();
};

#endif

