/*
 *		NOTE	- SW.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "SW.hpp"
#include "mcu.hpp"




/*----------------------------------------//
			 Initialize Switch
//----------------------------------------*/

void SW::init (void)
{
	
	switch (m_SwitchPort)
	{
		// PORTA
		case A:
			m_NewValue = PINA;
			break;
		
		// PORTB
		case B:
			m_NewValue = PINB;
			break;
		
		// PORTC
		case C:
			m_NewValue = PINC;
			break;
		
		// PORTD
		case D:
			m_NewValue = PIND;
			break;
		
		// PORTE
		case E:
			m_NewValue = PINE;
			break;
		
		// PORTF
		case F:
			m_NewValue = PINF;
			break;
		
		default:
			break;
	}
	
	if (m_isReversal == true)
	{
		result = m_OldValue & ~m_NewValue;
		m_OldValue = m_NewValue;
	}
	
	else
	{
		result = m_OldValue & m_NewValue;
		m_OldValue = ~m_NewValue;
	}
	
}