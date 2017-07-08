/*
The circuit :
* LCD RS pin to digital pin 12
* LCD Enable pin to digital pin 11
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R / W pin to ground
* 10K resistor :
*ends to + 5V and ground
* wiper to LCD VO pin(pin 3)
*/

#include <LiquidCrystal.h>
#include <DS3231.h>

DS3231 clock;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	// Print a message to the LCD.
	clock.begin();
	}


void loop() {
	//RTCDateTime now = clock.readTemperature;
	String temp = String(clock.readTemperature());
	lcd.setCursor(0, 0);
	lcd.print("Temp:        C");
	lcd.setCursor(7, 0);
	lcd.print(temp);
	lcd.display();
	delay(10000);
	lcd.clear();
}