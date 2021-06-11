/*
 *		NOTE	- SW.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "SW.hpp"
#include "MCU.hpp"




/*----------------------------------------//
			 Set Sensor Value
//----------------------------------------*/

void SW::setMax(int maxValue)
{
	maxData = maxValue;
}


/*----------------------------------------//
			 Initialize Switch
//----------------------------------------*/

void SW::init (void)
{
	
	switch (m_SwitchPort)
	{
		// PORTA
		case A:
			newData = PINA;
			break;
		
		// PORTB
		case B:
			newData = PINB;
			break;
		
		// PORTC
		case C:
			newData = PINC;
			break;
		
		// PORTD
		case D:
			newData = PIND;
			break;
		
		// PORTE
		case E:
			newData = PINE;
			break;
		
		// PORTF
		case F:
			newData = PINF;
			break;
		
		default:
			break;
	}
	
	switch (m_SwitchMode)
	{
		// REVERSAL
		case REVERSAL:
			result = oldData & ~newData;
			oldData = newData;
			break;
		
		// NONREVERSAL
		case NONREVERSAL:
			result = oldData & newData;
			oldData = ~newData;
			break;
		
		// SENSER
		case SENSOR:
			result = newData & maxData;
			break;
		
		default:
			break;
	}
	
}