/*
 * WIRING
 * Now we create a new LedControl.
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221
 * There will only be a single MAX7221 attached to the arduino
 *
 * 14 Sgmt LED SCL,SDA
 * DS3231 SCL,SDA
 */

#include <DS3231.h>
#include <gfxfont.h>
#include <LedControl.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

DS3231 clock;

LedControl lc = LedControl(12, 11, 10, 1);
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void setup() {
	lc.shutdown(0, false);
	lc.setIntensity(0, 1);
	lc.clearDisplay(0);

	Wire.begin();
	alpha4.begin(0x70);
	alpha4.clear();
	alpha4.setBrightness(0);

	clock.begin();

}

void printNumber(int v) {
	int ones;
	int tens;
	int hundreds;
	int thousands;

	ones = v % 10;
	v = v / 10;
	tens = v % 10;
	v = v / 10;
	hundreds = v % 10;
	v = v / 10;
	thousands = v;

	//Now print the number digit by digit
	lc.setDigit(0, 7, (byte)thousands, false);
	lc.setDigit(0, 6, (byte)hundreds, true);
	lc.setDigit(0, 5, (byte)tens, false);
	lc.setDigit(0, 4, (byte)ones, false);
}

void printClock() {
	int ones;
	int tens;

	RTCDateTime now = clock.getDateTime();

	int min = now.minute;
	ones = min % 10;
	min = min / 10;
	tens = min % 10;
	lc.setDigit(0, 0, (byte)ones, false);
	lc.setDigit(0, 1, (byte)tens, false);


	int hour = now.hour;
	ones = hour % 10;
	hour = hour / 10;
	tens = hour % 10;

	if (now.second % 2 == 0)
	{
		lc.setDigit(0, 2, (byte)ones, true);
	}
	else
	{
		lc.setDigit(0, 2, (byte)ones, false);
	}

	lc.setDigit(0, 3, (byte)tens, false);

	delay(10);
}


char displaybuffer[5] = { '/', '-', '\\', '|' };

void loop() {

	printNumber(clock.readTemperature() * 100);


	RTCDateTime now = clock.getDateTime();

	printClock();

	if (now.second == 0 || now.second == 30)
	{
		for (int y = 0; y <= 10; y++)
		{
			for (int i = 0; i <= 3; i++)
			{
				// set every digit to the buffer
				alpha4.writeDigitAscii(0, displaybuffer[i]);
				alpha4.writeDigitAscii(1, displaybuffer[i]);
				alpha4.writeDigitAscii(2, displaybuffer[i]);
				alpha4.writeDigitAscii(3, displaybuffer[i]);

				// write it out!
				alpha4.writeDisplay();
				delay(30);
			}
		}
	}
	alpha4.writeDigitAscii(0, ' ');
	alpha4.writeDigitAscii(1, ' ');
	alpha4.writeDigitAscii(2, ' ');
	alpha4.writeDigitAscii(3, ' ');
	alpha4.writeDisplay();
}

