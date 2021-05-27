/*
 *		NOTE	- Counter_System.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.10
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#include "mcu.Hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


SW sw(C, OFF);
DataLongLCD lcd(A, B);

ISR(TIMER2_OVF_vect);
ISR(TIMER1_COMPA_vect);

int Title = ON;
int Start = OFF;
int Pause = ON;
int Set = OFF;
int Setted = OFF;

int i, j;
int k, l;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main (void)
{
    beginPort(C, IN);
	beginPort(B, OUT);
	beginPort(A, OUT);
	
	beginTimer(2, OVF);
	beginTimer(1, COMP);
	
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


ISR(TIMER2_OVF_vect)
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


ISR(TIMER1_COMPA_vect)
{
	
	if (Start == ON)
	{
		if (Pause == OFF)
		{
			
			lcd.setLine(2, 12);
			
			lcd.exportData(ASKII(i));
			lcd.exportData(ASKII(j));
			lcd.print(":");
			lcd.exportData(ASKII(k));
			lcd.exportData(ASKII(l));
			
			l--;
			
			if (l < 0)
			{
				l = 9;
				k--;
			}
			
			if (k < 0)
			{
				k = 5;
				j--;
			}
			
			if (j < 0)
			{
				j = 9;
				i--;
			}
			
			if (i < 0)
			{
				i = 0;
				j = 0;
				k = 0;
				l = 0;
				
				lcd.clear(1);
				
				lcd.setLine(1, 1);
				lcd.print("Done");
				
				Start = OFF;
				Set = OFF;
			}
			
		}
		
		else
		{
			lcd.clear(1);
			
			lcd.setLine(1, 1);
			lcd.print("Pause");
		}
	}
	
}