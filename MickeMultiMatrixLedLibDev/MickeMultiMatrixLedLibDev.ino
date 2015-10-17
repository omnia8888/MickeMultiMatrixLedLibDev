/*
 Name:		MickeMultiMatrixLedLibDev.ino
 Created:	10/17/2015 2:13:43 AM
 Author:	Micke
*/

/*
Name:		MatrixTemperature.ino
Created:	10/8/2015 5:25:37 AM
Author:	Micke
*/

//We always have to include the library
#include <LedControl.h>
#include "MickeMultiMatrixLed.h"
//#include "MatrixSymbols.h"


/*
Now we need a LedControl to work with.
***** These pin numbers will probably not work with your hardware *****
pin 12 is connected to the DataIn
pin 11 is connected to the CLK
pin 10 is connected to LOAD
We have only a single MAX72XX.
*/

/*Hardware dependent defines:
Pin configurations for the daisychained MAX72XX* devices with Matrix Led displays*/
#define PIN_DATA_IN 12
#define PIN_CLK 11
#define PIN_LOAD 10

#define NUM_OF_DISPLAY_MODULES 5

const byte maxDisplayNumIndex = (NUM_OF_DISPLAY_MODULES - 1);


//Create instance of the public Arduino LedControl Library
//Thats needed for Multi Matrix controller.
LedControl lc = LedControl(12, 11, 10, NUM_OF_DISPLAY_MODULES);

//Create Multi Matrix Ledcontrol object.
MickeMultiMatrixLed mmML(lc);

// the setup function runs once when you press reset or power the board
void setup()
{



	//For debugging
	Serial.begin(9600);
	delay(1000);

	//Init Displays
	mmML.initLedMatrix();

	mmML.oneDot(1, 2, true);

	mmML.displayDebugTestSym();
	//int x, z;
	//byte b;
	//x = (33 + 256);
	//for (byte i = 0; i < 2; i++)
	//{
	//	z = x >> i * 7;
	//	b = lowByte(z);
	//	Serial.print(z);
	//	Serial.print("=");
	//	Serial.println(b);
	//}

}

// the loop function runs over and over again until power down or reset
void loop()
{

	byte *symbolToDisplay;

	//symbolToDisplay = symbolSun;

	//mmML.displaySymbol(0, 4, symbolToDisplay, true);

}