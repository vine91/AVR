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


//ISR(TIMER0_OVF_vect);
//ISR(TIMER2_COMP_vect);

void sensorOff (void);

bool left = OFF;
bool leftMiddle = OFF;
bool middle = OFF;
bool rightMiddle = OFF;
bool right = OFF;
bool all = OFF;

volatile unsigned int olddata;
volatile unsigned int newdata;
volatile unsigned int detection;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
    beginPort(D, OUT);
	beginPort(E, IN);
	
	//beginTimer(0, OVF);
	//beginTimer(2, COMP);
	
	//motor.setLeftSpeed(40);
	//motor.setRightSpeed(40);
	
	//sei();
	
    while (true) 
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
			PORTD = 0x08;
			_delay_us(7);
			PORTD = 0x00;
		}
		
		else if (leftMiddle == ON)
		{
			PORTD = 0x08;
			_delay_us(7);
			PORTD = 0x00;
		}
		
		else if (middle == ON)
		{
			PORTD = 0x09;
			_delay_us(8);
			PORTD = 0x00;
		}
		
		else if (rightMiddle == ON)
		{
			PORTD = 0x01;
			_delay_us(7);
			PORTD = 0x00;
		}
		
		else if (right == ON)
		{
			PORTD = 0x01;
			_delay_us(7);
			PORTD = 0x00;
		}
		
		else if (all == ON)
		{
			PORTD = 0x08;
			_delay_us(7);
			PORTD = 0x00;
		}
		
		else
		{
			PORTD = 0x01;
			_delay_us(7);
			PORTD = 0x00;
		}
		
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


/*
ISR(TIMER0_OVF_vect)
{
	cli();
	
	sw.init();
	
	if (sw.result != SW_OFF)
	{
		_delay_ms(10);
		
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
		isON = ON;
	}
	
	else
	{
		PORTD = 0x00;
		
		isON = OFF;
	}
	
	sei();
}


ISR(TIMER2_COMP_vect)
{
	
	sensor.init();
	
	if (isON == true)
	{
		if (sensor.result != SW_OFF)
		{
			switch (sensor.result)
			{
				case SW_0:
					PORTD = 0x08;
					_delay_us(1);
					PORTD = 0x00;
					break;
				
				case SW_1:
					PORTD = 0x09;
					_delay_us(1);
					PORTD = 0x00;
					break;
				
				case SW_2:
					PORTD = 0x01;
					_delay_us(1);
					PORTD = 0x00;
					break;
				
				default:
					PORTD = 0x09;
					_delay_us(1);
					PORTD = 0x00;
					break;
			}
		}
	}
	
}
*/