/*
 Name:		MickeMultiMatrixLedLibDev.ino
 Created:	10/17/2015 2:13:43 AM
 Author:	Micke
*/


#include "MickeMultiMatrixLed.h"

/*Hardware dependent defines:
Pin configurations for the daisychained MAX72XX* devices with Matrix Led displays*/
#define PIN_DATA_IN 12
#define PIN_CLK 11
#define PIN_LOAD 10

#define NUM_OF_DISPLAY_MODULES 5

const byte maxDisplayNumIndex = (NUM_OF_DISPLAY_MODULES - 1);


//Create instance of the public Arduino LedControl Library
//Thats needed for Multi Matrix controller.

//Create Multi Matrix Ledcontrol object.
MickeMultiMatrixLed mmm(PIN_DATA_IN,PIN_CLK,PIN_LOAD,NUM_OF_DISPLAY_MODULES);

// the setup function runs once when you press reset or power the board
void setup()
{


	//For debugging
	Serial.begin(9600);
	delay(1000);

	//Init Displays
	mmm.initMatrixDisplays();


	
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

	mmm.oneDisplayRow(4, 4, B11111111);
	byte r = 7, c = 22;
	mmm.displayRow(r, c, B11011011);

	//mmm.displayRow(6, 9, B11111111);

}

// the loop function runs over and over again until power down or reset
void loop()
{

	byte *symbolToDisplay;

	//symbolToDisplay = symbolSun;

	//mmML.displaySymbol(0, 4, symbolToDisplay, true);

	//if you use more than one MAX7219, it should look like this

	//mmm.maxAll(1, 1);                       //  + - - - - - - -
	//mmm.maxAll(2, 3);                       //  + + - - - - - -
	//mmm.maxAll(3, 7);                       //  + + + - - - - -
	//mmm.maxAll(4, 15);                      //  + + + + - - - -
	//mmm.maxAll(5, 31);                      //  + + + + + - - -
	//mmm.maxAll(6, 63);                      //  + + + + + + - -
	//mmm.maxAll(7, 127);                     //  + + + + + + + -
	//mmm.maxAll(8, 255);                     //  + + + + + + + +

	//mmm.oneDisplayRow(4, 4, B11011011);


}