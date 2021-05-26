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

#include "MCU.HPP"

using namespace Setting;


SW sw(B, ON);
Motor motor(D);

//ISR(TIMER0_OVF_vect);
//ISR(TIMER1_COMPA_vect);

int startSwitch;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
    beginPort(A, IN);
    beginPort(B, IN);
    beginPort(D, OUT);
	
	beginTimer(0, OVF);
	beginTimer(1, COMP);
	
	//motor.setLeftSpeed(40);
	//motor.setRightSpeed(40);
	
	sei();
	
    while (true) 
    {
		PORTD = 0b00000001;			//0001
		_delay_ms(2000);
		PORTD = 0b00000010;			//0010
		_delay_ms(2000);
		PORTD = 0b00000011;			//0010
		_delay_ms(2000);
		
		/*
		PORTD = 0x01;			//0001	Left 1 0 CW
		_delay_ms(2000);
		PORTD = 0x00;
		
		PORTD = 0x02;			//0010	Right 1 0 CW
		_delay_ms(2000);
		PORTD = 0x00;
		
		PORTD = 0x04;			//0100	Left 0 1 CCW
		_delay_ms(2000);
		PORTD = 0x00;
		
		PORTD = 0x08;			//1000	Right 0 1 CCW
		_delay_ms(2000);
		PORTD = 0x00;
		*/
    }
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/

/*
ISR(TIMER0_OVF_vect)
{
	
	sw.initSW();
	
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
		PORTD = 0x01;
	}
	
	else
	{
		PORTD = 0x00;
	}
	
}


ISR(TIMER1_COMPA_vect)
{
	
	if (startSwitch == ON)
	{
		
	}
	
	else
	{
		
	}
	
}*/