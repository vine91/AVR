/*
 *	  NOTE - main.cpp
 *
 * Created - 2021.05.10
 *  Author - 2033112012 CLJ
 */

#include <avr/io.h>
#include <util/delay.h>

#include "MCU.HPP"




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
	
    Setting::beginPort(A, OUT);
	Setting::beginPort(C, IN);
	Setting::beginPort(F, OUT);
	
	SW portC;
	LCD portF;
	
	portC.beginSW(C, ON);
	portF.beginLCD(F, HIGH);
	portF.initLCD();
	
	PORTA = 0x01;
	
	
    while (true) 
    {
		portC.initSW();
		
		if (portC.result != SW_OFF)
		{
			switch (portC.result)
			{
				case SW_0:
					PORTA = PORTA << 1;
					break;
					
				case SW_1:
					PORTA = PORTA >> 1;
			}
		}
		
		portF.changeLine(1, 3);
		portF.writeString("Testing System");
		portF.changeLine(2, 11);
		portF.writeString("by CLJ");
    }
	
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/