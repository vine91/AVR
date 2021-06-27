/*
 *		NOTE	- main.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.06.16
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"
#include "Modules/LCD.hpp"

using namespace MCU::Setting;


class Traffic
{

private:
	unsigned int m_TrafficPort;

public:
	Traffic (int trafficPort) { m_TrafficPort = trafficPort; }
	void attachPort (int portValue);

};

Traffic east(F);
Traffic south(E);
Traffic west(B);
Traffic north(A);

DataLongLCD lcd(C, D);

ISR(TIMER1_COMPA_vect);

void select(int directionValue, int signalValue);

unsigned int g_Count = 0;
unsigned int g_Direction = 0;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
	beginPort(A, OUT);
	beginPort(B, OUT);
	beginPort(C, OUT);
	beginPort(D, OUT);
	beginPort(E, OUT);
	beginPort(F, OUT);

	beginTimer(1, COMP);
	
	lcd.init();
	
	sei();
	
	while (true)
	{
		
		switch (g_Direction)
		{
			case 0:
				lcd.setLine(1, 4);
				lcd.print("East Driveway");
				lcd.setLine(2, 2);
				lcd.print("North Crosswalk");
				break;
			
			case 1:
				lcd.setLine(1, 3);
				lcd.print("South Driveway");
				lcd.setLine(2, 3);
				lcd.print("East Crosswalk");
				break;
			
			case 2:
				lcd.setLine(1, 4);
				lcd.print("West Driveway");
				lcd.setLine(2, 2);
				lcd.print("South Crosswalk");
				break;
			
			case 3:
				lcd.setLine(1, 3);
				lcd.print("North Driveway");
				lcd.setLine(2, 3);
				lcd.print("West Crosswalk");
				break;
			
			default:
				break;
		}
		
		if (g_Count == 0)
		{
			select(g_Direction, 0xAC);
			select((g_Direction+1) % 4, 0xA1);
			select((g_Direction+2) % 4, 0xA1);
			select((g_Direction+3) % 4, 0x51);
		}
		
		else if (g_Count == 5)
		{
			select(g_Direction, 0xA2);
			select((g_Direction+3) % 4, 0xA1);
		}
		
		else if (g_Count == 6)
		{
			select(g_Direction, 0xA1);
			
			g_Count = 0;
			g_Direction++;
			
			if (g_Direction > 3)
			{
				g_Direction = 0;
			}
		}
		
	}
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/


ISR(TIMER1_COMPA_vect)
{
	g_Count++;
	lcd.clear(ALL);
}


void select(int directionValue, int signalValue)
{
	
	switch (directionValue)
	{
		case 0:
			east.attachPort(signalValue);
			break;
		
		case 1:
			south.attachPort(signalValue);
			break;
		
		case 2:
			west.attachPort(signalValue);
			break;
		
		case 3:
			north.attachPort(signalValue);
			break;
		
		default:
			break;
	}
	
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