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

void sensorOff (void);

bool left = OFF;
bool leftMiddle = OFF;
bool middle = OFF;
bool rightMiddle = OFF;
bool right = OFF;
bool all = OFF;
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


void sensorOff (void)
{
	left = OFF;
	leftMiddle = OFF;
	middle = OFF;
	rightMiddle = OFF;
	right = OFF;
	all = OFF;
}


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
				sensorOff();
				left = ON;
				break;
				
			case 0x05:
				sensorOff();
				leftMiddle = ON;
				break;
				
			case 0x04:
				sensorOff();
				middle = ON;
				break;
				
			case 0x14:
				sensorOff();
				rightMiddle = ON;
				break;
				
			case 0x10:
				sensorOff();
				right = ON;
				break;
				
			case 0x15:
				sensorOff();
				all = ON;
			
			default:
				break;
		}
	}

	olddata = newdata;
	
	if (left == ON)
	{
		leftMotor.setSpeed(6);
		rightMotor.setSpeed(7);
	}
	
	else if (leftMiddle == ON)
	{
		leftMotor.setSpeed(7);
		rightMotor.setSpeed(10);
	}
	
	else if (middle == ON)
	{
		leftMotor.setSpeed(10);
		rightMotor.setSpeed(10);
	}
	
	else if (rightMiddle == ON)
	{
		leftMotor.setSpeed(10);
		rightMotor.setSpeed(7);
	}
	
	else if (right == ON)
	{
		leftMotor.setSpeed(7);
		rightMotor.setSpeed(6);
	}
	
	else if (all == ON)
	{
		leftMotor.setSpeed(0);
		rightMotor.setSpeed(5);
	}

	else
	{
		leftMotor.setSpeed(5);
		rightMotor.setSpeed(0);
	}

}
