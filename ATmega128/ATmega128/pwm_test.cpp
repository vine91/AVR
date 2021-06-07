/*
 *		NOTE	- pwm_test.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.06.07
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
	beginPort(E, OUT);
	beginPWM(OC3A);
	beginPWM(OC3B);
	beginPWM(OC3C);

	while (true)
	{
		OCR3A = 0;
		_delay_ms(500);
		
		OCR3A = 64;
		_delay_ms(500);
		
		OCR3A = 128;
		_delay_ms(500);
		
		OCR3A = 192;
		_delay_ms(500);
		
		OCR3A = 255;
		_delay_ms(500);
		
		OCR3B = 0;
		_delay_ms(500);
		
		OCR3B = 64;
		_delay_ms(500);
		
		OCR3B = 128;
		_delay_ms(500);
		
		OCR3B = 192;
		_delay_ms(500);
		
		OCR3B = 255;
		_delay_ms(500);
		
		OCR3C = 0;
		_delay_ms(500);
		
		OCR3C = 64;
		_delay_ms(500);
		
		OCR3C = 128;
		_delay_ms(500);
		
		OCR3C = 192;
		_delay_ms(500);
		
		OCR3C = 255;
		_delay_ms(500);
	}

	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/