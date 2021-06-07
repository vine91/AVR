/*
 *		NOTE	- MCU.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "MCU.hpp"




/*----------------------------------------//
				Insert Bit
//----------------------------------------*/

int MCU::insertBit (int bitValue, bool isHigh)
{
	
	int highValue = 0x00;
	int lowValue = 0x00;
	
	if (isHigh == true)
	{
		return highValue |= (1 << bitValue);
	}
	
	else
	{
		return lowValue &= ~(1 << bitValue);
	}
	
}


/*----------------------------------------//
			Delay Micro Second
//----------------------------------------*/

void MCU::delay_usec (unsigned char cycleValue)
{
	
    register unsigned char i;
	
    for(i=0; i<cycleValue; i++)				// 4 cycle +
    {
        asm volatile("PUSH R0");			// 2 cycle +
        asm volatile("POP  R0");			// 2 cycle +
        asm volatile("PUSH R0");			// 2 cycle +
        asm volatile("POP  R0");			// 2 cycle +
        asm volatile("PUSH R0");			// 2 cycle +
        asm volatile("POP  R0");			// 2 cycle =
    }
											// 16 cycle = 1us in 16MHz System
}


/*----------------------------------------//
			Delay Milli Second
//----------------------------------------*/

void MCU::delay_msec (unsigned int timeValue)
{
	
	register unsigned int i;

	for(i=0;i<timeValue;i++)
	{
		delay_usec(250);
		delay_usec(250);
		delay_usec(250);
		delay_usec(250);
	}
	
}


/*----------------------------------------//
			 Convert 10 to 16
//----------------------------------------*/

int MCU::Features::hex (int decimal)
{
	int hexadecimal = 0x00;
	
	if (decimal >= 0 && decimal <= 9)
	{
		hexadecimal = decimal;
	}
	
	else if (decimal >= 10 && decimal <= 19)
	{
		hexadecimal = decimal + 6;
	}
	
	else if (decimal >= 20 && decimal <= 29)
	{
		hexadecimal = decimal + 12;
	}
	
	else if (decimal >= 30 && decimal <= 39)
	{
		hexadecimal = decimal + 18;
	}
	
	else if (decimal >= 40 && decimal <= 49)
	{
		hexadecimal = decimal + 24;
	}
	
	else if (decimal >= 50 && decimal <= 59)
	{
		hexadecimal = decimal + 30;
	}
	
	else if (decimal >= 60 && decimal <= 69)
	{
		hexadecimal = decimal + 36;
	}
	
	else if (decimal >= 70 && decimal <= 79)
	{
		hexadecimal = decimal + 42;
	}
	
	else if (decimal >= 80 && decimal <= 89)
	{
		hexadecimal = decimal + 48;
	}
	
	else if (decimal >= 90 && decimal <= 99)
	{
		hexadecimal = decimal + 54;
	}
	
	return hexadecimal;
}


/*----------------------------------------//
			Convert 10 to ASKII
//----------------------------------------*/

int MCU::Features::ASKII (int decimal)
{
	int ASKIIValue = 0x00;
	
	if (decimal >= 0 && decimal <= 9)
	{
		ASKIIValue = decimal + 0x30;
	}
	
	return ASKIIValue;
}


/*----------------------------------------//
				 Begin Port
//----------------------------------------*/

void MCU::Setting::beginPort (int port, bool isOutput)
{
	
	int ddrValue;
	int portValue;
	
	// INPUT or OUTPUT
	if (isOutput == true)
	{
		ddrValue = 0xFF;
		portValue = 0x00;
	}
	
	else
	{
		ddrValue = 0x00;
	}
	
	switch (port)
	{
		// PORTA
		case A:
			DDRA = ddrValue;
			PORTA = portValue;
			break;
		
		// PORTB
		case B:
			DDRB = ddrValue;
			PORTB = portValue;
			break;
		
		// PORTC
		case C:
			DDRC = ddrValue;
			PORTC = portValue;
			break;
		
		// PORTD
		case D:
			DDRD = ddrValue;
			PORTD = portValue;
			break;
		
		// PORTE
		case E:
			DDRE = ddrValue;
			PORTE = portValue;
			break;
		
		// PORTF
		case F:
			DDRF = ddrValue;
			PORTF = portValue;
			break;
		
		default:
			break;
	}
	
}


/*----------------------------------------//
		 Begin Extended Interrupt
//----------------------------------------*/

void MCU::Setting::beginExtend(int extendIndex)
{
	
	EIMSK += insertBit(extendIndex, HIGH);
	
	if (extendIndex <= 3)
	{
		EICRA = 0x00;
	}
	
	else if (extendIndex >= 4)
	{
		EICRB = 0x00;
	}
	
}


/*----------------------------------------//
		  Begin Timer Interrupt
//----------------------------------------*/

void MCU::Setting::beginTimer (int timerIndex, int timerMode)
{
	
	switch (timerIndex)
	{
		// TIMER INTERRUPT 0, 2 (8 BIT)
		case 0:
			if (timerMode == OVF)
			{
				TIMSK += insertBit(0, HIGH);
				
				TCCR0 = 0x07;		// 1024, Normal Mode
				TCNT0 = 0x00;		// Start Counting 0x00
			}
			
			else if (timerMode == COMP)
			{
				TIMSK += insertBit(1, HIGH);
				
				TCCR0 = 0x0F;		// 1024, CTC Mode
				TCNT0 = 0x00;		// Start Counting 0x00
				OCR0 = 0xFF;		// Compare with 0xFF
			}
			
			break;
		
		case 2:
			if (timerMode == OVF)
			{
				TIMSK += insertBit(6, HIGH);
				
				TCCR2 = 0x05;		// 1024, Normal Mode
				TCNT2 = 0x00;		// Start Counting 0x00
			}
			
			else if (timerMode == COMP)
			{
				TIMSK += insertBit(7, HIGH);
				
				TCCR2 = 0x0D;		// 1024, CTC Mode
				TCNT2 = 0x00;		// Start Counting 0x00
				OCR2 = 0xA0;		// Compare with 0xA0
			}
			
			break;
		
		// TIMER INTERRUPT 1, 3 (16 BIT)
		case 1:
			if (timerMode == OVF)
			{
				TIMSK += insertBit(2, HIGH);
				
				TCCR1A = 0x00;
				TCCR1B = 0x05;		// 1024, Normal Mode
				TCNT1H = 0x00;
				TCNT1L = 0x00;		// Start Counting 0x0000
			}
			
			else if (timerMode == COMP)
			{
				TIMSK += insertBit(4, HIGH);
				
				TCCR1A = 0x00;
				TCCR1B = 0x0D;		// 1024, CTC Mode
				TCNT1H = 0x00;
				TCNT1L = 0x00;		// Start Counting 0x0000
				OCR1AH = 0xFF;
				OCR1AL = 0xFF;		// Compare with 0xFFFF
			}
			
			break;
		
		case 3:
			if (timerMode == OVF)
			{
				ETIMSK += insertBit(2, HIGH);
				
				TCCR3A = 0x00;
				TCCR3B = 0x05;		// 1024, Normal Mode
				TCNT3H = 0x00;
				TCNT3L = 0x00;		// Start Counting 0x0000
			}
			
			else if (timerMode == COMP)
			{
				ETIMSK += insertBit(4, HIGH);
				
				TCCR3A = 0x00;
				TCCR3B = 0x0D;		// 1024, CTC Mode
				TCNT3H = 0x00;
				TCNT3L = 0x00;		// Start Counting 0x0000
				OCR3AH = 0x3D;
				OCR3AL = 0x09;		// Compare with 0x3D09
			}
			
			break;
		
		default:
			break;
	}
	
}