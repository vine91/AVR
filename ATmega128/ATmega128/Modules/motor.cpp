/*
 *		NOTE	- motor.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "motor.hpp"
#include "MCU.hpp"

using namespace MCU;




/*----------------------------------------//
			 Attach Motor Port
//----------------------------------------*/

void Motor::attachPin(int pinValue)
{
	
	switch (m_MotorPin)
	{
		// OC0
		case OC0:
			OCR0 = pinValue;
			break;
		
		// OC1A
		case OC1A:
			OCR1A = pinValue;
			break;
		
		// OC1B
		case OC1B:
			OCR1B = pinValue;
			break;
		
		// OC1C
		case OC1C:
			OCR1C = pinValue;
			break;
		
		// OC2
		case OC2:
			OCR2 = pinValue;
			break;
		
		// OC3A
		case OC3A:
			OCR3A = pinValue;
			break;
		
		// OC3B
		case OC3B:
			OCR3B = pinValue;
			break;
		
		// OC3C
		case OC3C:
			OCR3C = pinValue;
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
	
	for (int i=0; i<=100; i++)
	{
		if (speedValue == i)
		{
			m_Speed = i * 2.55;
		}
	}
	
}


/*----------------------------------------//
			 	Start Motor
//----------------------------------------*/

void Motor::start (void)
{
	attachPin(m_Speed);
	m_isOn = true;
}


/*----------------------------------------//
			 	 Stop Motor
//----------------------------------------*/

void Motor::stop (void)
{
    attachPin(0);
    m_isOn = false;
}