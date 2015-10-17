// 
// 
// 

#include "MickeMultiMatrixLed.h"
#include "MatrixSymbols.h"

MickeMultiMatrixLed::MickeMultiMatrixLed(LedControl _lc)
	:LedControl(_lc)
{

}

void MickeMultiMatrixLed::displayDebugTestSym()
{
	displaySymbol(0, 20, symbolTest, true);
}

//Inits all Displays
void MickeMultiMatrixLed::initLedMatrix()
{
	/*
	The MAX72XX is in power-saving mode on startup,
	we have to do a wakeup call
	*/
	for (int i = 0; i < 8; i++)
	{
		shutdown(i, false);
		/* Set the brightness to a medium values */
		setIntensity(i, 8);
		/* and clear the display */
		clearDisplay(i);
	}
	delay(1000);
}

void MickeMultiMatrixLed::displaySymbol(byte row, byte col, byte *symbol, bool visable)
{
	byte value;
	//Print out each row of symbol on multi display
	for (uint8_t i = 0; i < LED_MATRIX_MODULE_ROWS; i++)
	{
		value = symbol[i];
		displaySingleRow(i, col, value);
	}

}

/*	Sets the state of a single led segment on the multi display matrix.
with row and column index based on total display layout starting from upper left corner.
state(true = Led on, false = Led off)*/
void MickeMultiMatrixLed::oneDot(byte row, byte col, bool state)
{
	//Calculate on what display the dot is located.
	byte displayNum = (4 - (col / 8));
	//byte displayNum = (maxDisplayNumIndex - (col / 8));

	//Calculate column index on the single display
	byte singleCol = (col % 8);
	//Serial.println(singleCol);

	setLed(displayNum, row, singleCol, state);
}



void MickeMultiMatrixLed::displaySingleRow(byte row, byte col, byte value)
{

	int totalVal;
	byte displayNo, ledRow, ledCol,
		SingleDispVal, ledState;

	//Check display value for individual led state on two displays.
	for (byte i = 0; i < 15; i++)
	{
		ledState = (value >> i) & 1;
		ledCol = (col + i);

		//Update one individual led segment state
		oneDot(row, ledCol, ledState);

		//Serial.print(i);
		//Serial.print("=");
		//Serial.println(ledState);

	}
}

