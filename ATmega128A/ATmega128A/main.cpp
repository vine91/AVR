/*
 *		NOTE	- main.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.06.16
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"

#define EAST	0
#define NORTH	1
#define WEST	2
#define SOUTH	3

using namespace MCU::Features;
using namespace MCU::Setting;


class Traffic
{

private:
	unsigned int m_TrafficPort;

public:
	Traffic (int trafficPort) { m_TrafficPort = trafficPort; }
	void attachPort (int portValue);

};


ISR(TIMER1_COMPA_vect);

void select(int directionValue, int signalValue);

Traffic east(F);
Traffic north(A);
Traffic west(B);
Traffic south(E);

unsigned int count = 0;
unsigned int direction = 0;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
	beginPort(B, OUT);
	beginPort(E, OUT);
	beginPort(F, OUT);
	beginPort(A, OUT);
	
	beginTimer(1, COMP);
	
	sei();
	
	while (true)
	{
		if (count == 0)
		{
			select(direction, 0xAC);
			select( (direction+1)%4, 0xA1);
			select( (direction+2)%4, 0xA1);
			select( (direction+3)%4, 0x51);
		}
		
		else if (count == 5)
		{
			select(direction, 0xA2);
			select( (direction+3)%4, 0xA1);
		}
		
		else if (count == 6)
		{
			select(direction, 0xA1);
			
			direction++;
			
			if (direction > 3)
			{
				direction = 0;
			}
			
			count = 0;
		}
	}
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/


ISR(TIMER1_COMPA_vect)
{
	count++;
}


/*----------------------------------------//
			  Class Traffic
//----------------------------------------*/

void Traffic::attachPort(int portValue)
{
	
	switch (m_TrafficPort)
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
		
		// PORTG
		case G:
			PORTG = portValue;
			break;
		
		default:
			break;
	}
	
}


void select(int directionValue, int signalValue)
{
	
	switch (directionValue)
	{
		case EAST:
			east.attachPort(signalValue);
			break;
		
		case NORTH:
			north.attachPort(signalValue);
			break;
		
		case WEST:
			west.attachPort(signalValue);
			break;
		
		case SOUTH:
			south.attachPort(signalValue);
			break;
		
		default:
			break;
	}
	
}