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

Motor rightCCW(OC1A);
Motor leftCW(OC1B);

SW sw(D, ON);
SW sensor(E, ON);

int startSwitch = OFF;
NonOptimal oldData;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
	beginPort(B, OUT);
	beginPort(D, IN);
	beginPort(E, IN);
	
	beginTimer(0, OVF);
	beginTimer(2, COMP);
	
	beginPWM(OC1A);
	beginPWM(OC1B);
	
	leftCW.stop();
	rightCCW.stop();
	
	leftCW.setSpeed(4);
	rightCCW.setSpeed(4);
	
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
		leftCW.start();
		rightCCW.start();
	}
	
	else
	{
		leftCW.stop();
		rightCCW.stop();
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
				leftCW.setSpeed(2);
				rightCCW.setSpeed(4);
				break;
			
			case 0x04:
				leftCW.setSpeed(4);
				rightCCW.setSpeed(4);
				break;
			
			case 0x10:
				leftCW.setSpeed(4);
				rightCCW.setSpeed(2);
				break;
			
			case 0x00:
				if (oldData == 0x01)
				{
					leftCW.setSpeed(0);
					rightCCW.setSpeed(2);
				}

				else if (oldData == 0x10)
				{
					leftCW.setSpeed(2);
					rightCCW.setSpeed(0);
				}
				
				else if (oldData == 0x04)
				{
					leftCW.setSpeed(3);
					rightCCW.setSpeed(3);
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