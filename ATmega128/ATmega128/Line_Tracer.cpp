/*
 *		NOTE	- line_tracer.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.24
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"
#include "Modules/SW.hpp"
#include "Modules/motor.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


ISR(TIMER0_OVF_vect);
ISR(TIMER2_COMP_vect);

Motor left(C);
Motor right(D);

SW sw(B, ON);
SW sensor(E, ON);

int startSwitch = OFF;
NonOptimal oldData;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
	beginPort(C, OUT);
    beginPort(D, OUT);
	beginPort(B, IN);
	beginPort(E, IN);
	
	beginTimer(0, OVF);
	beginTimer(2, COMP);
	
	left.setSpeed(3);
	right.setSpeed(3);
	
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
	
	if (sw.result != 0x00)
	{
		switch (sw.result)
		{
			case SW_0:
				startSwitch = OFF;
				break;
			
			case SW_1:
				startSwitch = ON;
				break;
			
			default:
				break;
		}
	}
	
	if (startSwitch == ON)
	{
		left.start(CW);
		right.start(CCW);
	}
	
	else
	{
		left.stop();
		right.stop();
	}
	
}


ISR(TIMER2_COMP_vect)
{
	
	if (startSwitch == ON)
	{
		
		sensor.init();
		
		switch (sensor.result)
		{
			case 0x01:
				left.setSpeed(1);
				right.setSpeed(2);
				break;
			
			case 0x05:
				left.setSpeed(2);
				right.setSpeed(3);
				break;
			
			case 0x04:
				left.setSpeed(3);
				right.setSpeed(3);
				break;
			
			case 0x14:
				left.setSpeed(3);
				right.setSpeed(2);
				break;
			
			case 0x10:
				left.setSpeed(2);
				right.setSpeed(1);
				break;
			
			case 0x00:
				if (oldData == 0x01)
				{
					left.setSpeed(0);
					right.setSpeed(1);
				}

				else if (oldData == 0x10)
				{
					left.setSpeed(1);
					right.setSpeed(0);
				}
			
			default:
				break;
		}
		
	}
	
	if (sensor.result != 0x00)
	{
		oldData = sensor.result;
	}

	else
	{
		oldData = oldData;
	}
	
}