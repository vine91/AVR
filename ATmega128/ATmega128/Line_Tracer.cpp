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

Motor rightMotor(C);
Motor leftMotor(D);
SW sw(B, ON);
SW sensor(E, ON);

bool isOn = false;

NonOptimal olddata;
NonOptimal newdata;
NonOptimal detection;
NonOptimal data;




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
	
	leftMotor.setSpeed(10);
	rightMotor.setSpeed(10);
	
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
	
	newdata = PINB;
	detection = olddata & (~ newdata);
	
	if (detection != 0x00)
	{
		switch (detection)
		{
			case 0x01:
				startSwitch = OFF;
				break;
			
			case 0x02:
				startSwitch = ON;
				break;
			
			default:
				break;
		}
	}
	
	if (startSwitch == ON)
	{
		leftmotor.start(CW);
		rightMotor.start(CCW);

		leftMotor.stop();
		rightMotor.stop();
	}
	
	else
	{
		leftMotor.stop();
		rightMotor.stop();
	}
	
}


ISR(TIMER2_COMP_vect)
{
	newdata = PINE;
	detection = olddata & (~ newdata);
	
	if (detection != 0x00)
	{
		switch (detection)
		{
			case 0x01:
				leftMotor.setSpeed(6);
				rightMotor.setSpeed(7);
				break;
				
			case 0x05:
				leftMotor.setSpeed(7);
				rightMotor.setSpeed(10);
				break;
				
			case 0x04:
				leftMotor.setSpeed(10);
				rightMotor.setSpeed(10);
				break;
				
			case 0x14:
				leftMotor.setSpeed(10);
				rightMotor.setSpeed(7);
				break;
				
			case 0x10:
				leftMotor.setSpeed(7);
				rightMotor.setSpeed(6);
				break;
				
			case 0x15:
				leftMotor.setSpeed(0);
				rightMotor.setSpeed(5);
			
			default:
				break;
		}
	}

	olddata = newdata;
}
