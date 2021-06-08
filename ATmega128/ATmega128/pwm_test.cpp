/*
 *		NOTE	- pwm_test.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.06.07
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"
#include "Modules/motor.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


Motor test0(OC0);
Motor test1(OC1A);
Motor test2(OC1B);
Motor test3(OC2);



/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
	beginPort(B, OUT);
	beginPWM(OC0);
	beginPWM(OC1A);
	beginPWM(OC1B);
	beginPWM(OC2);

	while (true)
	{
		
		for (int i=0; i<=255; i++)
		{
			test0.attachPin(i);
			_delay_ms(5);
		}
		
		test0.attachPin(0);
		
		for (int i=0; i<=255; i++)
		{
			test1.attachPin(i);
			_delay_ms(5);
		}
		
		test1.attachPin(0);
		
		for (int i=0; i<=255; i++)
		{
			test2.attachPin(i);
			_delay_ms(5);
		}
		
		test2.attachPin(0);
		
		for (int i=0; i<=255; i++)
		{
			test3.attachPin(i);
			_delay_ms(5);
		}
		
		test3.attachPin(0);
		
	}

	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/