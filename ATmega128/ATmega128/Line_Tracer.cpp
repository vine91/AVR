/*
 *		NOTE	- Line_Tracer.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.24
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#include "mcu.Hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


SW sw(B, ON);
Motor motor(D);

ISR(TIMER0_OVF_vect);
//ISR(TIMER1_COMPA_vect);

int startSwitch;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
    beginPort(B, IN);
    beginPort(E, IN);
    beginPort(D, OUT);
	
	beginTimer(0, OVF);
	beginTimer(1, COMP);
	
	motor.setLeftSpeed(40);
	motor.setRightSpeed(40);
	
	sei();
	
    while (true) 
    {
		
    }
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/


ISR(TIMER0_OVF_vect)
{
	
	sw.init();
	
	if (sw.result != SW_OFF)
	{
		switch (sw.result)
		{
			case SW_0:
				startSwitch = ON;
				break;
			
			case SW_1:
				startSwitch = OFF;
				break;
			
			default:
				break;
		}
	}
	
	if (startSwitch == ON)
	{
		motor.startLeft(CW);
		motor.startRight(CCW);
	}
	
	else
	{
		motor.stop();
	}
	
}

/*
ISR(TIMER1_COMPA_vect)
{
	
	if (startSwitch == ON)
	{
		
	}
	
	else
	{
		
	}
	
}
*/