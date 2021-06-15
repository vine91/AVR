/*
 *		NOTE	- Calculator.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.19
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"
#include "Modules/SW.hpp"
#include "Modules/LCD.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


ISR(TIMER0_OVF_vect);

DataLongLCD lcd(A, B);
SW sw(C, OFF);

int add (int value, int object);
int minus (int value, int object);
int multiple (int value, int object);
int division (int value, int object);

int result;
int g_Value;
int g_Object;

int i, j;
int k, l;

bool Title = ON;
bool Start = OFF;
bool Pause = ON;
bool Set = OFF;
bool Setted = OFF;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
	beginPort(C, IN);
	beginPort(B, OUT);
	beginPort(A, OUT);
	
	beginTimer(0, COMP);
	
	lcd.init();
	
	sei();
    
    while (true) 
    {
		_delay_ms(2);
		
		if (Title == ON)
		{
			lcd.setLine(1, 2);
			lcd.print("Counter System");
			lcd.setLine(2, 11);
			lcd.print("by CLJ");
			
			_delay_ms(300);
		}
		
		_delay_ms(2);
    }
    
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/


ISR(TIMER0_OVF_vect)
{
	
	sw.init();
	
	if (sw.result != SW_OFF)
	{
		switch (sw.result)
		{
			case SW_0:				// Start and Restart when Time's set
				Title = OFF;
				
				if (Set == ON && Setted == OFF)
				{
					lcd.clear(ALL);
					
					lcd.setLine(1, 1);
					lcd.print("Counting");
					
					Start = ON;
					Pause = OFF;
				}
				
				else if (Set == OFF && Setted == OFF)
				{
					lcd.clear(ALL);
					
					lcd.setLine(1, 1);
					lcd.print("Please Push SW 3");
					lcd.setLine(2, 2);
					lcd.print("to Set the Time");
					
					_delay_ms(4000);
					
					lcd.clear(ALL);
					
					Title = ON;
				}
				
				break;
				
			case SW_1:				// Pause when Time's started
				Pause = ON;
				break;
				
			case SW_2:				// Go to Setting when Time's not set
				Title = OFF;
				
				if (Set == OFF && Setted == OFF)
				{
					Setted = ON;
					
					lcd.clear(ALL);
					
					lcd.setLine(1, 1);
					lcd.print("Set Time");
					
					lcd.setLine(2, 12);
					lcd.exportData(ASKII(i));
					lcd.exportData(ASKII(j));
					lcd.print(":");
					lcd.exportData(ASKII(k));
					lcd.exportData(ASKII(l));
				}
				
				break;
			
			case SW_3:				// Set the Time when Time's not set and it's in Setting
				if (Set == OFF && Setted == ON)
				{
					Set = ON;
					Setted = OFF;
					
					lcd.clear(1);
					
					lcd.setLine(1, 1);
					lcd.print("Set Complete");
					
					_delay_ms(2000);
					
					lcd.clear(ALL);
					
					Title = ON;
				}
				
				break;
			
			case SW_4:				// Control the Time when it's in Setting
				if (Set == OFF && Setted == ON)
				{
					if (i != 5)
					{
						i++;
					}
					
					else
					{
						i = 0;
					}
					
					lcd.setLine(2, 12);
					lcd.exportData(ASKII(i));
					lcd.exportData(ASKII(j));
					lcd.print(":");
					lcd.exportData(ASKII(k));
					lcd.exportData(ASKII(l));
				}
				
				break;
				
			case SW_5:
				if (Set == OFF && Setted == ON)
				{
					if (j != 9)
					{
						j++;
					}
					
					else
					{
						j = 0;
					}
					
					lcd.setLine(2, 12);
					lcd.exportData(ASKII(i));
					lcd.exportData(ASKII(j));
					lcd.print(":");
					lcd.exportData(ASKII(k));
					lcd.exportData(ASKII(l));
				}
				
				break;
			
			case SW_6:
				if (Set == OFF && Setted == ON)
				{
					if (k != 5)
					{
						k++;
					}
					
					else
					{
						k = 0;
					}
					
					lcd.setLine(2, 12);
					lcd.exportData(ASKII(i));
					lcd.exportData(ASKII(j));
					lcd.print(":");
					lcd.exportData(ASKII(k));
					lcd.exportData(ASKII(l));
				}
				
				break;
			
			case SW_7:
				if (Set == OFF && Setted == ON)
				{
					if (l != 9)
					{
						l++;
					}
					
					else
					{
						l = 0;
					}
					
					lcd.setLine(2, 12);
					lcd.exportData(ASKII(i));
					lcd.exportData(ASKII(j));
					lcd.print(":");
					lcd.exportData(ASKII(k));
					lcd.exportData(ASKII(l));
				}
				
				break;
			
			default:
				break;
		}
	}
	
}

int add (int value, int object)
{
    value += object;
    return value;
}

int minus (int value, int object)
{
    value -= object;
    return value;
}

int multiple (int value, int object)
{
    value *= object;
    return value;
}

int division (int value, int object)
{
    value /= object;
    return value;
}