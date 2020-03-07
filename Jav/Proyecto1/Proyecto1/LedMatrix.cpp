// 
// 
// 

#include "LedMatrix.h"

LedMatrix::LedMatrix():driver(53)
{
	clear();
	//DDRC = 0xff;
	//DDRA = 0Xff;
}

void LedMatrix::update()
{
	for(byte i = 0; i < SIZEOF_MATRIX; i++){
		driver.setRow(i, matrix[(SIZEOF_MATRIX - 1) - i]);
	}
}

void LedMatrix::fill(byte val)
{
	memset(matrix, val, SIZEOF_MATRIX);
}

void LedMatrix::clear()
{
	memset(matrix, 0, SIZEOF_MATRIX);
}

void LedMatrix::paintSadFace()
{
	clear();
	
	matrix[0] = 0b00111100;
	matrix[1] = 0b01000010;
	matrix[2] = 0b10100101;
	matrix[3] = 0b10000001;
	matrix[4] = 0b10011001;
	matrix[5] = 0b10100101;
	matrix[6] = 0b10000001;
	matrix[7] = 0b01111110;
	
	update();
}

void LedMatrix::paintDot(byte x, byte y)
{
	if(x >= 8 || y >= SIZEOF_MATRIX)
		return;
	
	matrix[y] |= (1 << x);
	update();
}

void LedMatrix::clearDot(byte x, byte y)
{
	if(x >= 8 || y >= SIZEOF_MATRIX)
		return;
	
	matrix[y] &= ~(1 << x);
	update();
}
