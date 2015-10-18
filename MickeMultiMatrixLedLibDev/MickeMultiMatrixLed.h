// MickeMultiMatrixLed.h

#ifndef _MICKEMULTIMATRIXLED_h
#define _MICKEMULTIMATRIXLED_h


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/*Hardware dependent display module parameters*/
#define LED_MATRIX_MODULE_ROWS 8 //Defines the number of rows on a single dot matrix module used
#define LED_MATRIX_MODULE_COLUMNS 8 //Defines the number of columns on a single dot matrix module used

class MickeMultiMatrixLed
{
 protected:


 public:
	 MickeMultiMatrixLed(byte dataPin, byte clkPin, byte csPin, byte numOfDisplays);

	void putByte(byte data);
	
	//void maxSingle(byte reg, byte col);

	void maxAll(byte reg, byte col);

	//void maxOne(byte maxNr, byte reg, byte col);
	
	void oneDisplayRow(byte displ,byte row,byte value);
	
	//void displayDebugTestSym();

	 void initMatrixDisplays(byte intens=8);

	 //void initLedMatrix();

	void displaySymbol(byte row, byte col, byte *symbol, bool visable);

	void displayRow(byte row, byte col, byte value);

	
	//void oneDot(byte row, byte col, bool state);


private:

	//const byte maxDisplayNumIndex = (NUM_OF_DISPLAY_MODULES - 1);
	const byte maxSingleRowIndex = (LED_MATRIX_MODULE_ROWS - 1);
	const byte maxSingleColIndex = (LED_MATRIX_MODULE_COLUMNS - 1);

	int _pinClk;
	int _pinData;
	int _pinLoad;
	int _numOfdisplays;

	// define max7219 registers
	byte max7219_reg_noop = 0x00;
	byte max7219_reg_digit0 = 0x01;
	byte max7219_reg_digit1 = 0x02;
	byte max7219_reg_digit2 = 0x03;
	byte max7219_reg_digit3 = 0x04;
	byte max7219_reg_digit4 = 0x05;
	byte max7219_reg_digit5 = 0x06;
	byte max7219_reg_digit6 = 0x07;
	byte max7219_reg_digit7 = 0x08;
	byte max7219_reg_decodeMode = 0x09;
	byte max7219_reg_intensity = 0x0a;
	byte max7219_reg_scanLimit = 0x0b;
	byte max7219_reg_shutdown = 0x0c;
	byte max7219_reg_displayTest = 0x0f;

};


#endif

