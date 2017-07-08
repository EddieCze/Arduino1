#include "Arduino.h"
//The setup function is called once at startup of the sketch

#include "LedControl.h"

LedControl lc = LedControl(12, 11, 10, 1);

void printNumber(int v) {
	int ones;
	int tens;
	int hundreds;
	boolean negative;

	if (v < -999 || v > 999)
		return;
	if (v<0) {
		negative = true;
		v = v*-1;
	}
	ones = v % 10;
	v = v / 10;
	tens = v % 10;
	v = v / 10;
	hundreds = v;
	if (negative) {
		//print character '-' in the leftmost column
		lc.setChar(0, 3, '-', false);
	}
	else {
		//print a blank in the sign column
		lc.setChar(0, 3, ' ', false);
	}
	//Now print the number digit by digit
	lc.setDigit(0, 2, (byte)hundreds, false);
	lc.setDigit(0, 1, (byte)tens, false);
	lc.setDigit(0, 0, (byte)ones, false);
}

void setup()
{
	for (int index = 0; index<lc.getDeviceCount(); index++)
		lc.shutdown(index, false);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
}
