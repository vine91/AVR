/*
 *		NOTE	- _0616.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.06.16
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


ISR(TIMER1_COMPA_vect);




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
	beginPort(E, OUT);
	beginTimer(1, COMP);
	
	PORTE = 0x01;
	
	sei();
	
	while (true)
	{
		
	}
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/


ISR(TIMER1_COMPA_vect)
{
	PORTE = PORTE << 1;
	
	if (PORTE == 0x80)
	{
		PORTE = 0x01;
	}
}