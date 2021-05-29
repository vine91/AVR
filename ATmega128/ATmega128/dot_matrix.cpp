/*
 *		NOTE	- Dot_Matrix.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.27
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/mcu.hpp"
#include "Modules/SW.hpp"
#include "Modules/LCD.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


unsigned char scan[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
unsigned char font[8] = { 0x8F, 0x88, 0x84, 0x83, 0x00, 0xFF, 0x81, 0xFF };




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
	beginPort(A, OUT);
	beginPort(B, OUT);
	
	while (true)
	{
		
		for (int i=0; i<8; i++)
		{
			
			PORTA = scan[i];
			_delay_ms(1000);
			
			for (int j=0; j<8; j++)
			{
				PORTB = 0xF0;
			}
			
		}
		
	}
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/