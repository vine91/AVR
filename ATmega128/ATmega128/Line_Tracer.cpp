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


ISR(INT0_vect);
ISR(INT1_vect);
ISR(TIMER2_COMP_vect);

SW sensor(E, SENSOR);
Motor right(OC0);
Motor left(OC1C);

bool startSwitch = OFF;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
	beginPort(B, OUT);
	beginPort(D, IN);
	beginPort(E, IN);
	
	beginExtend(0, DOWN);
	beginExtend(1, DOWN);
	beginTimer(2, COMP);
	
	beginPWM(OC0, CORRECT);
	beginPWM(OC1C, CORRECT);
	
	left.stop();
	right.stop();
	
	left.setSpeed(25);
	right.setSpeed(25);
	
	sei();
	
    while (true) 
    {
		
		if (startSwitch == ON)
		{
			left.start();
			right.start();
		}
		
		else
		{
			left.stop();
			right.stop();
		}
		
    }
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/


ISR(INT0_vect)
{
	cli();
	startSwitch = ON;
	sei();
}


ISR(INT1_vect)
{
	cli();
	startSwitch = OFF;
	sei();
}


ISR(TIMER2_COMP_vect)
{
	
	if (startSwitch == ON)
	{
		
		sensor.setMax(0x15);
		sensor.init();
		
		switch (sensor.result)
		{
			case 0x01:
				left.setSpeed(18);
				right.setSpeed(22);
				break;
			
			case 0x05:
				left.setSpeed(22);
				right.setSpeed(25);
				break;
			
			case 0x04:
				left.setSpeed(25);
				right.setSpeed(25);
				break;
			
			case 0x14:
				left.setSpeed(25);
				right.setSpeed(22);
				break;
			
			case 0x10:
				left.setSpeed(22);
				right.setSpeed(18);
				break;
			
			case 0x00:
				if (sensor.oldData == 0x01)
				{
					left.setSpeed(0);
					right.setSpeed(18);
				}
				
				else if (sensor.oldData == 0x10)
				{
					left.setSpeed(18);
					right.setSpeed(0);
				}
			
			default:
				break;
		}
		
	}
	
	if (sensor.result == sensor.maxData)
	{
		sensor.oldData = sensor.oldData;
	}
	
	else
	{
		sensor.oldData = sensor.result;
	}
	
}