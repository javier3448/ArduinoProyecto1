#ifndef _ANDROID
#define _ANDROID

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Android
{
 public:
 static boolean flagCatch;
 static boolean flagDrop; 
 static int velocityX;
 static int velocityY;

};

#endif
