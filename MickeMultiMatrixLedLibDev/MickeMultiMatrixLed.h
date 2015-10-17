// MickeMultiMatrixLed.h

#ifndef _MICKEMULTIMATRIXLED_h
#define _MICKEMULTIMATRIXLED_h


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include <LedControl.h>

/*Hardware dependent display module parameters*/
#define LED_MATRIX_MODULE_ROWS 8 //Defines the number of rows on a single dot matrix module used
#define LED_MATRIX_MODULE_COLUMNS 8 //Defines the number of columns on a single dot matrix module used

class MickeMultiMatrixLed:LedControl
{
 protected:


 public:
	 MickeMultiMatrixLed(LedControl);

	 void displayDebugTestSym();

	 void initLedMatrix();

	void displaySymbol(byte row, byte col, byte *symbol, bool visable);

	void displaySingleRow(byte row, byte col, byte value);

	void oneDot(byte row, byte col, bool state);

private:

	//const byte maxDisplayNumIndex = (NUM_OF_DISPLAY_MODULES - 1);
	const byte maxSingleRowIndex = (LED_MATRIX_MODULE_ROWS - 1);
	const byte maxSingleColIndex = (LED_MATRIX_MODULE_COLUMNS - 1);

};


#endif

