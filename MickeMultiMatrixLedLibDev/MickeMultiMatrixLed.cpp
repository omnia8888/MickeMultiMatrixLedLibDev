// 
// 
// 

#include "MickeMultiMatrixLed.h"
#include "MatrixSymbols.h"

MickeMultiMatrixLed::MickeMultiMatrixLed(byte dataPin, byte clkPin, byte csPin, byte numOfDisplays)
{
	_pinData = dataPin;
	_pinClk = clkPin;
	_pinLoad = csPin;
	_numOfdisplays = numOfDisplays;
}



/*Defines the control pins and inits all Led Matrix displays
controlling MAX7219 units with Parameters:
* dataPin		pin on the Arduino where data gets shifted out
* clockPin		pin for the clock
* csPin		pin for selecting the device
* numDevices	maximum number of devices that can be controled
* displayIntens	Set the initial display brightness*/
void MickeMultiMatrixLed::initMatrixDisplays(byte displIntens)
{

	pinMode(_pinData, OUTPUT);
	pinMode(_pinClk, OUTPUT);
	pinMode(_pinLoad, OUTPUT);


	//initiation of the max 7219
	maxAll(max7219_reg_scanLimit, 0x07);
	maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
	maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
	maxAll(max7219_reg_displayTest, 0x00); // no display test

	for (byte e = 1; e <= 8; e++)
	{    // empty registers, turn all LEDs off 
		maxAll(e, 0);
	}
	maxAll(max7219_reg_intensity, displIntens & 0x0f);    // the first 0x0f is the value you can set
												   // range: 0x00 to 0x0f
}



void MickeMultiMatrixLed::displaySymbol(byte row, byte col, byte *symbol, bool visable)
{
	byte value;
	//Print out each row of symbol on multi display
	for (uint8_t i = 0; i < LED_MATRIX_MODULE_ROWS; i++)
	{
		value = symbol[i];
		displayRow(i, col, value);
	}

}




void MickeMultiMatrixLed::displayRow(byte row, byte col, byte value)
{

	byte displayNo, ledRow, ledCol,
		oneDispVal, ledState;

	//On what display starts the row
	byte startDisplay = (col / 8);
	Serial.print("Start Display = ");
	Serial.println(startDisplay);

	//Start Column index on the row start display
	byte startCol = (col % 8);
	Serial.print("Start col = ");
	Serial.println(startCol);
	
	//Get the total value for row data if start column is 
	//not on the beginning of an single display
	int totalVal = value << (startCol);

	//Get data and update one display
	oneDispVal = lowByte(totalVal);
	oneDisplayRow(startDisplay, row, oneDispVal);
	
	Serial.print("LowB one displVal = ");
	Serial.println(oneDispVal);

	//Check if value spans to next display
	oneDispVal = highByte(totalVal);
	if (oneDispVal>0)
	{
		//Continue and update second display
		oneDisplayRow((startDisplay + 1), row, oneDispVal);

	}

	Serial.print("HiB one displVal = ");
	Serial.println(oneDispVal);

	
	//Check display value for individual led state on two displays.
	//for (byte i = 0; i < 15; i++)
	//{
	//	ledState = (value >> i) & 1;
	//	ledCol = (col + i);

	//	//Update one individual led segment state
	//	//oneDot(row, ledCol, ledState);

	//	//Serial.print(i);
	//	//Serial.print("=");
	//	//Serial.println(ledState);

	//}
}

void MickeMultiMatrixLed::putByte(byte data)
{
	byte i = 8;
	byte mask;
	while (i > 0)
	{
		mask = 0x01 << (i - 1);      // get bitmask
		digitalWrite(_pinClk, LOW);   // tick
		if (data & mask)
		{            // choose bit
			digitalWrite(_pinData, HIGH);// send 1
		}
		else
		{
			digitalWrite(_pinData, LOW); // send 0
		}
		digitalWrite(_pinClk, HIGH);   // tock
		--i;                         // move to lesser bit
	}
}

void MickeMultiMatrixLed::maxAll(byte reg, byte col)
{    // initialize  all  MAX7219's in the system
	int c = 0;
	digitalWrite(_pinLoad, LOW);  // begin     
	for (c = 1; c <= _numOfdisplays; c++)
	{
		putByte(reg);  // specify register
		putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
	}
	digitalWrite(_pinLoad, LOW);
	digitalWrite(_pinLoad, HIGH);
}

void MickeMultiMatrixLed::oneDisplayRow(byte displ, byte row, byte value)
{
	int c = 0;
	digitalWrite(_pinLoad, LOW);  // begin     

	for (c = _numOfdisplays; c > displ; c--)
	{
		putByte(0);    // means no operation
		putByte(0);    // means no operation
	}

	putByte(row+1);  // specify register
	putByte(value);//((data & 0x01) * 256) + data >> 1); // put data 

	for (c = (displ+1) - 1; c >= 1; c--)
	{
		putByte(0);    // means no operation
		putByte(0);    // means no operation
	}

	digitalWrite(_pinLoad, LOW); // and load da stuff
	digitalWrite(_pinLoad, HIGH);
}


