/*
 *	  NOTE - main.cpp
 *
 * Created - 2021.05.10
 *  Author - 2033112012 CLJ
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "MCU.HPP"




SW sw;
LCD lcd;

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
	
    Setting::beginPort(C, IN);
	Setting::beginPort(E, OUT);
	
	Setting::beginTimer(2, OVF);
	Setting::beginTimer(1, COMP);
	
	sw.beginSW(C, ON);
	lcd.beginLCD(E, HIGH);
	lcd.initLCD();
	
	sei();
	
    while (true) 
    {
		_delay_ms(2);
		
		if (Title == ON)
		{
			lcd.changeLine(1, 2);
			lcd.printLCD("Counter System");
			lcd.changeLine(2, 11);
			lcd.printLCD("by CLJ");
			
			_delay_ms(300);
		}
		
		_delay_ms(2);
    }
	
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/




ISR(TIMER2_OVF_vect)
{
	sw.initSW();
	
	if (sw.result != SW_OFF)
	{
		switch (sw.result)
		{
			case SW_0:				// Start and Restart when Time's set
				Title = OFF;
				
				if (Set == ON && Setted == OFF)
				{
					lcd.clearLine(ALL);
					
					lcd.changeLine(1, 1);
					lcd.printLCD("Counting");
					
					Start = ON;
					Pause = OFF;
				}
				
				else if (Set == OFF && Setted == OFF)
				{
					lcd.clearLine(ALL);
					
					lcd.changeLine(1, 1);
					lcd.printLCD("Please Push SW 3");
					lcd.changeLine(2, 2);
					lcd.printLCD("to Set the Time");
					
					_delay_ms(4000);
					
					lcd.clearLine(ALL);
					
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
					
					lcd.clearLine(ALL);
					
					lcd.changeLine(1, 1);
					lcd.printLCD("Set Time");
					
					lcd.changeLine(2, 12);
					lcd.setData(encodeLCD(i));
					lcd.setData(encodeLCD(j));
					lcd.printLCD(":");
					lcd.setData(encodeLCD(k));
					lcd.setData(encodeLCD(l));
				}
				
				break;
			
			case SW_3:				// Set the Time when Time's not set and it's in Setting
				if (Set == OFF && Setted == ON)
				{
					Set = ON;
					Setted = OFF;
					
					lcd.clearLine(1);
					
					lcd.changeLine(1, 1);
					lcd.printLCD("Set Complete");
					
					_delay_ms(2000);
					
					lcd.clearLine(ALL);
					
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
					
					lcd.changeLine(2, 12);
					lcd.setData(encodeLCD(i));
					lcd.setData(encodeLCD(j));
					lcd.printLCD(":");
					lcd.setData(encodeLCD(k));
					lcd.setData(encodeLCD(l));
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
					
					lcd.changeLine(2, 12);
					lcd.setData(encodeLCD(i));
					lcd.setData(encodeLCD(j));
					lcd.printLCD(":");
					lcd.setData(encodeLCD(k));
					lcd.setData(encodeLCD(l));
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
					
					lcd.changeLine(2, 12);
					lcd.setData(encodeLCD(i));
					lcd.setData(encodeLCD(j));
					lcd.printLCD(":");
					lcd.setData(encodeLCD(k));
					lcd.setData(encodeLCD(l));
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
					
					lcd.changeLine(2, 12);
					lcd.setData(encodeLCD(i));
					lcd.setData(encodeLCD(j));
					lcd.printLCD(":");
					lcd.setData(encodeLCD(k));
					lcd.setData(encodeLCD(l));
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
			
			lcd.changeLine(2, 12);
			
			lcd.setData(encodeLCD(i));
			lcd.setData(encodeLCD(j));
			lcd.printLCD(":");
			lcd.setData(encodeLCD(k));
			lcd.setData(encodeLCD(l));
			
			l--;
			
			if (l < 0)
			{
				l = 9;
				k--;
				
				if (k < 0)
				{
					k = 5;
					j--;
					
					if (j < 0)
					{
						j = 9;
						i--;
						
						if (i < 0)
						{
							i = 0;
							j = 0;
							k = 0;
							l = 0;
							
							lcd.clearLine(1);
							
							lcd.changeLine(1, 1);
							lcd.printLCD("Done");
							
							Start = OFF;
							Set = OFF;
						}
					}
				}
			}
			
		}
		
		else
		{
			lcd.clearLine(1);
			
			lcd.changeLine(1, 1);
			lcd.printLCD("Pause");
		}
	}
}