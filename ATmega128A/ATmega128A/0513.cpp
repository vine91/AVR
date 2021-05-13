/*
 *	  NOTE - 0513.cpp
 *
 * Created - 2021.05.13
 *  Author - 2033112012 CLJ
 */

#include <avr/io.h>
#include <util/delay.h>

#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "MCU.HPP"


int main (void)
{
	
    Setting::initPort(F, OUT);
    LCD LCD1;
	LCD1.beginLCD(F);
	LCD1.initLCD();
    
    while (1)
    {
		LCD1.setInstruction(0x80);
		LCD1.setData(0x31);
		LCD1.setData(0x32);
    }
	
	/*
	Setting::initPort(A, OUT);
	
	while (1)
	{
		BL(PORTA, 6);
		_delay_ms(500);
		
		
	}
	*/
}


