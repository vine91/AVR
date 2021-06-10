/*
 *		NOTE	- _0610.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.06.10
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"
#include "Modules/SW.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);
ISR(INT3_vect);




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
	beginPort(B, OUT);
	beginPort(C, IN);
	
	beginExtend(0, MAINTAIN);
	beginExtend(1, MAINTAIN);
	beginExtend(2, MAINTAIN);
	beginExtend(3, MAINTAIN);
	
	beginPWM(OC1B, CORRECT);
	beginPWM(OC2, CORRECT);
	
	sei();
	
	while (true)
	{
		
		for (int i=0; i<=255; i++)
		{
			OCR1B = i;
			_delay_ms(10);
		}
		
		OCR1B = 0;
		
		for (int i=0; i<=255; i++)
		{
			OCR2 = i;
			_delay_ms(10);
		}
		
		OCR2 = 0;
		
	}
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/