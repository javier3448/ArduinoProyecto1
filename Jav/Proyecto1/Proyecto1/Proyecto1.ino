#include "Crane.h"
#include "LedMatrix.h"
/*
 * Proyecto1.ino
 *
 * Created: 3/3/2020 4:52:55 PM
 * Author: Javier
 */ 

LedMatrix ledMatrix = LedMatrix();

byte x = 0;
byte y = 0;

void setup()
{
	Serial.begin(9600);
	Serial.println("");
	//ledMatrix.clear();
	//ledMatrix.update();
	//ledMatrix.drawDot(1, 1);
	ledMatrix.clear();
	ledMatrix.paintSadFace();
	
	pinMode(22, OUTPUT);
	delay(500);
	tone(22, 32, 1000);
}

unsigned long lastUpdated = millis();
byte d0 = 0xaa;
byte d1 = 0x55;

bool toggle = false;
void loop()
{
	if(millis() - lastUpdated > 200){
		//d0 = ~d0;
		//d1 = ~d1;
		//ledMatrix.matrix[0] = d0;
		//ledMatrix.matrix[1] = d1;
		//ledMatrix.matrix[2] = d0;
		//ledMatrix.matrix[3] = d1;
		//ledMatrix.matrix[4] = d0;
		//ledMatrix.matrix[5] = d1;
		//ledMatrix.matrix[6] = d0;
		//ledMatrix.matrix[7] = d1;
		
		if(toggle){
			ledMatrix.paintDot(x, y);
		}
		else{
			ledMatrix.clearDot(x, y);
		}
		x++;
		if(x >= 8){
			x = 0;
			y++;
		}
		if(y > 8){
			y = 0;
			toggle = !toggle;
		}
		
		Serial.print("x axis: ");
		Serial.println(map(analogRead(A0), 0, 1024, -100, 100));
		Serial.print("y axis: ");
		Serial.println(map(analogRead(A1), 0, 1024, -100, 100));
		lastUpdated = millis();
	}
}

