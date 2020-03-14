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
	
    matrix[0] = 0b00000000;
    matrix[1] = 0b00000000;
    matrix[2] = 0b00100100;
    matrix[3] = 0b00010000;
    matrix[4] = 0b00010000;
    matrix[5] = 0b00100100;
    matrix[6] = 0b00000000;
    matrix[7] = 0b00000000;
	
	update();
}

void LedMatrix::paintDot(byte x, byte y)
{
	if(x >= 8 || y >= SIZEOF_MATRIX)
		return;
	
	x = SIZEOF_MATRIX - x - 1;
	y = SIZEOF_MATRIX - y - 1;
	
	matrix[x] |= (1 << y);
	update();
}

void LedMatrix::clearDot(byte x, byte y)
{
	if(x >= 8 || y >= SIZEOF_MATRIX)
		return;
	
	x = SIZEOF_MATRIX - x - 1;
	y = SIZEOF_MATRIX - y - 1;
	
	matrix[x] &= ~(1 << y);
	update();
}
