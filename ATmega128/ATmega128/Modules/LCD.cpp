/*
 *		NOTE	- LCD.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "LCD.hpp"
#include "MCU.hpp"

using namespace MCU;




/*----------------------------------------//
			 Attach LCD Port
//----------------------------------------*/

void LCD::attachPort (int portValue)
{
	
	switch (m_LCDPort)
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
		Attach Data Long LCD Port
//----------------------------------------*/

void LCD::attachExtendPort (int extendPortValue)
{
	
	switch (m_ExtendPort)
	{
		// PORTA
		case A:
			PORTA = extendPortValue;
			break;
		
		// PORTB
		case B:
			PORTB = extendPortValue;
			break;
		
		// PORTC
		case C:
			PORTC = extendPortValue;
			break;
		
		// PORTD
		case D:
			PORTD = extendPortValue;
			break;
		
		// PORTE
		case E:
			PORTE = extendPortValue;
			break;
		
		// PORTF
		case F:
			PORTF = extendPortValue;
			break;
		
		default:
			break;
	}
	
}


/*----------------------------------------//
			 Export Instruction
//----------------------------------------*/

void LCD::exportInstruction (int instructionValue)
{
	
	if (m_isDataLong == false)
	{
		int enableBit = insertBit(7, HIGH);
		int disableBit = insertBit(7, LOW);
		
		_delay_ms(2);
		
		attachPort( ((instructionValue >> 4) & 0x0F) | enableBit );
		_delay_us(1);
		attachPort( ((instructionValue >> 4) & 0x0F) | disableBit );
		_delay_us(1);
		
		
		attachPort( (instructionValue & 0x0F) | enableBit );
		_delay_us(1);
		attachPort( (instructionValue & 0x0F) | disableBit );
		_delay_us(1);
	}
	
	else
	{
		int enableBit = insertBit(2, HIGH);
		int disableBit = insertBit(2, LOW);
		
		_delay_ms(2);
		
		attachExtendPort(instructionValue);
		
		attachPort(enableBit);
		_delay_us(1);
		attachPort(disableBit);
		_delay_us(1);
	}
	
}


/*----------------------------------------//
				Export Data
//----------------------------------------*/

void LCD::exportData (int dataValue)
{
	
	if (m_isDataLong == false)
	{
		int enableBit = insertBit(7, HIGH) | insertBit(5, HIGH);
		int disableBit = insertBit(7, LOW) | insertBit(5, HIGH);
		
		_delay_ms(2);
		
		attachPort( ((dataValue >> 4) & 0x0F) | enableBit );
		_delay_us(1);
		attachPort( ((dataValue >> 4) & 0x0F) | disableBit );
		_delay_us(1);
		
		
		attachPort( (dataValue & 0x0F) | enableBit );
		_delay_us(1);
		attachPort( (dataValue & 0x0F) | disableBit );
		_delay_us(1);
	}
	
	else
	{
		int enableBit = insertBit(2, HIGH) | insertBit(0, HIGH);
		int disableBit = insertBit(2, LOW) | insertBit(0, HIGH);
		
		_delay_ms(2);
		
		attachExtendPort(dataValue);
		
		attachPort(enableBit);
		_delay_us(1);
		attachPort(disableBit);
		_delay_us(1);
	}
	
}


/*----------------------------------------//
				Print String
//----------------------------------------*/

void LCD::print (String stringValue)
{
	
	while (*stringValue != '\0')
	{
		exportData(*stringValue);
		stringValue ++;
	}
	
}


/*----------------------------------------//
				  Set Line
//----------------------------------------*/

void LCD::setLine (int lineIndex, int fileIndex)
{
	
	for (int i=0; i<16; i++)
	{
		if (lineIndex == 1 && fileIndex == (i + 1))
		{
			int sendValue = 0x80 + i;
			
			exportInstruction(sendValue);
		}
		
		else if (lineIndex == 2 && fileIndex == (i + 1))
		{
			int sendValue = 0xC0 + i;
			
			exportInstruction(sendValue);
		}
	}
	
}


/*----------------------------------------//
				 Clear Line
//----------------------------------------*/

void LCD::clear (int clearMode)
{
	
	if (clearMode == ALL)
	{
		setLine(1, 1);
		print("                ");
		
		setLine(2, 1);
		print("                ");
	}
	
	else if (clearMode == 1)
	{
		setLine(1, 1);
		print("                ");
	}
	
	else if (clearMode == 2)
	{
		setLine(2, 1);
		print("                ");
	}
	
}


/*----------------------------------------//
			  Initialize LCD
//----------------------------------------*/

void LCD::init (void)
{
	
	if (m_isDataLong == false)
	{
		exportInstruction(0x28);			// Set Function		[ DL = 4 Bit		N = 2 LINE		F = 5 x 7	]
	}
	
	else
	{
		exportInstruction(0x38);			// Set Function		[ DL = 8 Bit		N = 2 LINE		F = 5 x 7	]
	}
	
	exportInstruction(0x0C);				// Control Display	[ D = Display H		C = Cursor L	B = Blink L ]
	exportInstruction(0x06);				// Set Entry Mode	[ I/D = Right						S = Shift L	]
	exportInstruction(0x01);				// Clear Display
	
}