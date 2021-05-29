/*
 *		NOTE	- motor.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "motor.hpp"
#include "mcu.hpp"

using namespace MCU;




/*----------------------------------------//
			Attach DC Motor Port
//----------------------------------------*/

void Motor::attachPort (int portValue)
{
	
	switch (m_MotorPort)
	{
		// PORTA
		case A:
			PORTA = portValue;
			break;
		
		// PORTB
		case B:
			PORTB = portValue;
			break;
		
		// PORTC
		case C:
			PORTC = portValue;
			break;
		
		// PORTD
		case D:
			PORTD = portValue;
			break;
		
		// PORTE
		case E:
			PORTE = portValue;
			break;
		
		// PORTF
		case F:
			PORTF = portValue;
			break;
		
		default:
			break;
	}
	
}


/*----------------------------------------//
			  Set Motor Speed
//----------------------------------------*/

void Motor::setSpeed (int speedValue)
{
    m_Speed = speedValue;
}


/*----------------------------------------//
			  Get Motor Speed
//----------------------------------------*/

void Motor::getSpeed (void)
{
    Features::delayCycle(m_Speed);
}


/*----------------------------------------//
			 	Start Motor
//----------------------------------------*/

void Motor::start (bool isClockWise)
{
	
	if (isClockWise == true)
	{
		attachPort( insertBit(0, HIGH) | insertBit(1, LOW) );
		getSpeed();
		stop();
	}
	
	else
	{
		attachPort( insertBit(0, LOW) | insertBit(1, HIGH) );
		getSpeed();
		stop();
	}
	
	isOn = true;
	
}


/*----------------------------------------//
			 	 Stop Motor
//----------------------------------------*/

void Motor::stop (void)
{
    attachPort( insertBit(0, LOW) | insertBit(1, LOW) );
    isOn = false;
}