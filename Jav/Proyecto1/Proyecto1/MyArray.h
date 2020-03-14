// MyArray.h

#ifndef _MYARRAY_h
#define _MYARRAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MyArray
{
 public:
	String moves[16] = {};
};

#endif

