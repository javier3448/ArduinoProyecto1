// Max7219Driver.h

#ifndef _MAX7219DRIVER_h
#define _MAX7219DRIVER_h

#include <SPI.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Max7219Driver {
private:
	const int SS_PIN; //load pin on max7219
	void beginTransaction();

public:
	const static byte NO_OP = 0;
	const static byte DIGIT0 = 1;
	const static byte DIGIT1 = 2;
	const static byte DIGIT2 = 3;
	const static byte DIGIT3 = 4;
	const static byte DIGIT4 = 5;
	const static byte DIGIT5 = 6;
	const static byte DIGIT6 = 7;
	const static byte DIGIT7 = 8;
	const static byte DECODE_MODE = 9;
	const static byte INTENSITY = 10;
	const static byte SCAN_LIMIT = 11;
	const static byte SHUTDOWN = 12;
	const static byte TEST = 15;

	Max7219Driver(int ssPin);

	/*
	 * Se tuvo que haber iniciado una transaccion antes
	 */
	int transfer(byte memory_address, byte value);

	int setRow(int row, byte value);

	void clear();

	void setUp();

	int getSSPin();
};

#endif

