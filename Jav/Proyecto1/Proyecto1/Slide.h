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
	UsSensor usSensor;

	bool hasPrize = false;
	bool hadPrize = false;
	bool doorOpen = false;
	
	static const byte PIN_DOOR0 = 10;
	static const byte PIN_DOOR1 = 9;
	static const unsigned int HAS_PRIZE_DISTANCE = 500;
	
	byte servoPin;

	Servo servo;

public:
	//doorPin es basura, no se usa//TODO: QUITAR door
	Slide(byte hasPrizeEchoPin, byte hasPrizeTriggerPin, byte doorPin);
	
	void setup();
	
	void update();
	
	byte getHasPrize();
	byte getHadPrize();
	
	void open();
	void close();
	
	bool isDoorOpen();
	
	friend void setup();
	friend void loop();
};

#endif

