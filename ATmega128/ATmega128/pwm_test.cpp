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
			OCR0 = i;
			_delay_ms(5);
		}
		
		OCR0 = 0;
		
		for (int i=0; i<=255; i++)
		{
			OCR1A = i;
			_delay_ms(5);
		}
		
		OCR1A = 0;
		
		for (int i=0; i<=255; i++)
		{
			OCR1B = i;
			_delay_ms(5);
		}
		
		OCR1B = 0;
		
		for (int i=0; i<=255; i++)
		{
			OCR2 = i;
			_delay_ms(5);
		}
		
		OCR2 = 0;
		
	}

	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/