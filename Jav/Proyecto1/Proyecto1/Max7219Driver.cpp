#include "Max7219Driver.h"

Max7219Driver::Max7219Driver(int ssPin) :SS_PIN(ssPin)
{
	setUp();
}

int Max7219Driver::transfer(byte memory_address, byte value)
{
	digitalWrite(SS_PIN, LOW);
	int read = SPI.transfer(memory_address);//most significant goes first
	read = (read << 8) | SPI.transfer(value);
	digitalWrite(SS_PIN, HIGH);
	return read;
}

int Max7219Driver::setRow(int row, byte value)
{
	if (row < 0 || row>7)
		return 0xff;
	return transfer(row + 1, value);
}

void Max7219Driver::clear()
{
	for (int i = 0; i < 8; i++)
		setRow(i, 0);
}

void Max7219Driver::setUp()
{
	pinMode(SS_PIN, OUTPUT);
	pinMode(PIN_SPI_MOSI, OUTPUT);
	pinMode(PIN_SPI_SCK, OUTPUT);
	digitalWrite(SS_PIN, HIGH);

	beginTransaction();

	transfer(SHUTDOWN, 0x00);//Apaga la pantalla para que se programen los valores iniciales primero sin riesgo a dannarla
	transfer(INTENSITY, 0x07);
	transfer(SCAN_LIMIT, 0x07);//scan-limit a 8 digitos (i.e. 8 columnas)
	transfer(DECODE_MODE, 0x00);//Quita el decode mode por si estaba previamente activado
	transfer(TEST, 0x00);//Quita el test mode por si estaba previamente activado
	transfer(SHUTDOWN, 0x01);//Se quita el shutdown
	clear();
}

void Max7219Driver::beginTransaction()
{
	SPI.begin();
	SPI.beginTransaction(SPISettings(35000000, MSBFIRST, SPI_MODE0));
}

int Max7219Driver::getSSPin()
{
	return SS_PIN;
}
