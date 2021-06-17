/*
 *		NOTE	- _0617.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.06.17
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"
#include "Modules/LCD.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;

unsigned char read_adc(unsigned char adc_input)
{
	ADMUX=adc_input | (0<<REFS1) | (0<<REFS0) | (1<<ADLAR);
	// Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=(1<<ADSC);
	// Wait for the AD conversion to complete
	while ((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADCH;
}


DataLongLCD lcd(A, B);
unsigned int result;



/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
	beginPort(A, OUT);
	beginPort(B, OUT);
	beginPort(E, OUT);
	
	ADMUX=(0<<REFS1) | (0<<REFS0) | (1<<ADLAR);
	ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
	SFIOR=(0<<ACME);
	
	lcd.init();
	
	while (true)
	{
		result = read_adc(1);
		
		if (result > 111 && result < 131)
		{
			PORTE = 0x01;
		}
		
		_delay_ms(250);
	}
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/