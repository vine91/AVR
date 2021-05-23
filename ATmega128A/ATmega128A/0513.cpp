/*
 *	  NOTE - 0513.cpp
 *
 * Created - 2021.05.13
 *  Author - 2033112012 CLJ
 */

#include <avr/io.h>
#include "MCU.HPP"



DataLongLCD lcd(A, B);
SW sw(C, OFF);


int main (void)
{
	
	Setting::beginPort(A, OUT);
	Setting::beginPort(B, OUT);
	Setting::beginPort(C, IN);
	
	lcd.initLCD();
	
	while (1)
	{
		lcd.changeLine(1, 1);
		lcd.printLCD("Test System");
		lcd.changeLine(2, 1);
		lcd.printLCD("by CLJ");
	}
	
}


