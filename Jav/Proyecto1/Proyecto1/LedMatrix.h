#ifndef _LEDMATRIX_h
#define _LEDMATRIX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Max7219Driver.h"

class LedMatrix
{
private:

	static const unsigned int BLINK_PERIOD = 300; //Numero de ciclos que se mantiene apagada o en predida en update blink
	int updateBlinkCount = 0;
	byte updatePantallaCount = 0;
	
	Max7219Driver driver;

public:
	static constexpr byte SIZEOF_MATRIX = 8;

	byte matrix[SIZEOF_MATRIX];
	
	void update();
	void fill(byte val);//solo para debugging
	void clear();
	void paintSadFace();
	void paintDot(byte x, byte y);
	void clearDot(byte x, byte y);
	
	LedMatrix();
	
	friend void loop();
	friend void setup();
};

#endif

