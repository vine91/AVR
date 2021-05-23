/*
 *	  NOTE - MCU.HPP
 *
 * Created - 2021.05.10
 *  Author - 2033112012 CLJ
 */


#ifndef MCU_HPP_
#define MCU_HPP_

#include <util/delay.h>

#define OFF		0
#define ON		1
#define LOW		0
#define HIGH	1
#define IN		0
#define OUT		1
#define CCW		0
#define CW		1

#define A		0
#define B		1
#define C		2
#define D		3
#define E		4
#define F		5
#define COMP	6
#define OVF		7
#define CAPT	8
#define ALL		9

#define SW_OFF	0x00
#define SW_0	0x01
#define SW_1	0x02
#define SW_2	0x04
#define SW_3	0x08
#define SW_4	0x10
#define SW_5	0x20
#define SW_6	0x40
#define SW_7	0x80

using String = const char *;
using NonOptimal = volatile unsigned int;




/*----------------------------------------//
				Insert Bit
//----------------------------------------*/

int insertBit (int bitValue, bool isHigh)
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
			  Encode 10 to 16
//----------------------------------------*/

int encodeFND(int decimal)
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
			Encode 10 to ASKII
//----------------------------------------*/

int encodeLCD(int decimal)
{
	int ASKII = 0x00;
	
	if (decimal >= 0 && decimal <= 9)
	{
		ASKII = decimal + 0x30;
	}
	
	return ASKII;
}




/*
//==========================================
			NAMESPACE - Setting
==========================================//
*/

namespace Setting
{
	void beginPort (int port, bool isOutput);
	void beginExtended (int extendedIndex);
	void beginTimer (int timerIndex, int timerMode);
}


/*----------------------------------------//
			  Initialize Port
//----------------------------------------*/

void Setting::beginPort (int port, bool isOutput)
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

void Setting::beginExtended (int extendedIndex)
{
	
	EIMSK += insertBit(extendedIndex, HIGH);
	
	if (extendedIndex <= 3)
	{
		EICRA = 0x00;
	}
	
	else if (extendedIndex >= 4)
	{
		EICRB = 0x00;
	}
	
}


/*----------------------------------------//
		  Begin Timer Interrupt
//----------------------------------------*/

void Setting::beginTimer (int timerIndex, int timerMode)
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
				OCR2 = 0xFF;		// Compare with 0xFF
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
				OCR1AH = 0x3D;
				OCR1AL = 0x09;		// Compare with 0x3D09
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




/*
//==========================================
			CLASS - SW (Switch)
==========================================//
*/

class SW
{

private:
	unsigned int m_SwitchPort;
	bool m_isReversal;
	NonOptimal m_newValue;
	NonOptimal m_oldValue;

public:
	SW (int switchPort, bool isReversal) { m_SwitchPort = switchPort; m_isReversal = isReversal; }
	void initSW (void);
	
	NonOptimal result;

};


/*----------------------------------------//
			 Initialize Switch
//----------------------------------------*/

void SW::initSW (void)
{
	
	switch (m_SwitchPort)
	{
		// PORTA
		case A:
			m_newValue = PINA;
			break;
		
		// PORTB
		case B:
			m_newValue = PINB;
			break;
		
		// PORTC
		case C:
			m_newValue = PINC;
			break;
		
		// PORTD
		case D:
			m_newValue = PIND;
			break;
		
		// PORTE
		case E:
			m_newValue = PINE;
			break;
		
		// PORTF
		case F:
			m_newValue = PINF;
			break;
		
		default:
			break;
	}
	
	if (m_isReversal == true)
	{
		result = m_oldValue & ~m_newValue;
		m_oldValue = m_newValue;
	}
	
	else
	{
		result = m_oldValue & m_newValue;
		m_oldValue = ~m_newValue;
	}
	
}




/*
//==================================================================================================
							Interface Connector Pin Setting of LCD
====================================================================================================
	Pin		|	Signal	|								Setting
----------------------------------------------------------------------------------------------------
	1		|	Vss		|	Ground					( GND )
	2		|	Vdd		|	DC 5V					( VCC )
	3		|	Vo		|	Brightness Setting		( Vdd - Vo = 3 ~ 13V)						-P4-
	4		|	RS		|	Resister Select			( H = Data			L = Instruction )		-P5-
	5		|	R/W		|	Read / Write			( H = LCD to MCU	L = MCU to LCD )		-P6-
	6		|	E		|	Enable					( H = Enable		L = Disable )			-P7-
	7		|	DB0		|	DATA BUS 0				( LSB )
	8		|	DB1		|	DATA BUS 1
	9		|	DB2		|	DATA BUS 2
	10		|	DB3		|	DATA BUS 3
	11		|	DB4		|	DATA BUS 4															-P0-
	12		|	DB5		|	DATA BUS 5															-P1-
	13		|	DB6		|	DATA BUS 6															-P2-
	14		|	DB7		|	DATA BUS 7				( MSB )										-P3-
	15		|	A		|	Anode					( VCC for LED or EL Back light )
	16		|	K		|	Cathode					( GND for LED or EL Back light )
--------------------------------------------------------------------------------------------------//


//==================================================================================================
										Instruction Setting
====================================================================================================
				Instruction				|	Signal	|	Code
										| Rs	R/W	|	DB7	 DB6  DB5  DB4		DB3  DB2  DB1  DB0
----------------------------------------------------------------------------------------------------
	Clear Display						|  0	 0	|	 0	  0	   0	0		 0	  0    0	1
	Return Home							|  0	 0	|	 0	  0	   0	0		 0	  0    1	-
	Set Entry							|  0	 0	|	 0	  0	   0	0		 0	  1   I/D	S
	Control Display ON/OFF				|  0	 0	|	 0	  0	   0	0		 1	  D    C	B
	Shift Cursor or Display				|  0	 0	|	 0	  0	   0	1		S/C	 R/L   -	-
	Set Function						|  0	 0	|	 0	  0	   1	DL		 N	  F    -	-
	Set CG RAM Address					|  0	 0	|	 0	  1		   CG RAM Address
	Set DD RAM Address					|  0	 0	|	 1			   DD RAM Address
----------------------------------------------------------------------------------------------------
	Read Busy Flag and Address Counter	|  0	 1	|	 BF			  Address Counter
----------------------------------------------------------------------------------------------------
	Write Data to CG RAM or DD RAM		|  1	 0	|					Write Data
	Read Data to CG RAM or DD RAM		|  1	 1	|					 Read Data
--------------------------------------------------------------------------------------------------//


//==================================================================================================
										DD RAM Address
====================================================================================================
 Line|											Address
----------------------------------------------------------------------------------------------------
  1  | 00H | 01H | 02H | 03H | 04H | 05H | 06H | 07H | 08H | 09H | 0AH | 0BH | 0CH | 0DH | 0EH | 0FH |
  2	 | 40H | 41H | 42H | 43H | 44H | 45H | 46H | 47H | 48H | 49H | 4AH | 4BH | 4CH | 4DH | 4EH | 4FH |
--------------------------------------------------------------------------------------------------//
*/


/*
//==========================================
			CLASS - LCD (Monitor)
==========================================//
*/

class LCD
{

protected:
	unsigned int m_LCDPort;
	unsigned int m_ExtendPort;
	bool m_isDataLong;

public:
	LCD (int LCDPort) { m_LCDPort = LCDPort; }

	// PORT
	void attachPort (int portValue);
	void attachExtendPort (int extendPortValue);
	void setInstruction (int instructionValue);
	void setData (int dataValue);

	// INFO
	void printLCD (String stringValue);
	void changeLine (int lineIndex, int fileIndex);
	void clearLine (int clearMode);
	void initLCD (void);

};


/*
//==========================================
			CLASS - Data Long LCD
==========================================//
*/

class DataLongLCD : public LCD
{

public:
	DataLongLCD (int LCDPort, int extendPort) : LCD (LCDPort) { m_ExtendPort = extendPort; m_isDataLong = true; }

};


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
			 Set Instruction
//----------------------------------------*/

void LCD::setInstruction (int instructionValue)
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
				 Set Data
//----------------------------------------*/

void LCD::setData (int dataValue)
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

void LCD::printLCD (String stringValue)
{
	
	while (*stringValue != '\0')
	{
		setData(*stringValue);
		stringValue ++;
	}
	
}


/*----------------------------------------//
				Change Line
//----------------------------------------*/

void LCD::changeLine (int lineIndex, int fileIndex)
{
	
	for (int i=0; i<16; i++)
	{
		if (lineIndex == 1 && fileIndex == (i + 1))
		{
			int sendValue = 0x80 + i;
			
			setInstruction(sendValue);
		}
		
		else if (lineIndex == 2 && fileIndex == (i + 1))
		{
			int sendValue = 0xC0 + i;
			
			setInstruction(sendValue);
		}
	}
	
}


/*----------------------------------------//
				Clear Line
//----------------------------------------*/

void LCD::clearLine (int clearMode)
{
	
	if (clearMode == ALL)
	{
		changeLine(1, 1);
		printLCD("                ");
		
		changeLine(2, 1);
		printLCD("                ");
	}
	
	else if (clearMode == 1)
	{
		changeLine(1, 1);
		printLCD("                ");
	}
	
	else if (clearMode == 2)
	{
		changeLine(2, 1);
		printLCD("                ");
	}
	
}


/*----------------------------------------//
			  Initialize LCD
//----------------------------------------*/

void LCD::initLCD (void)
{

	if (m_isDataLong == false)
	{
		setInstruction(0x28);			// Set Function		[ DL = 4 Bit		N = 2 LINE		F = 5 x 7	]
	}

	else
	{
		setInstruction(0x38);			// Set Function		[ DL = 8 Bit		N = 2 LINE		F = 5 x 7	]
	}

	setInstruction(0x0C);				// Control Display	[ D = Display H		C = Cursor L	B = Blink L ]
	setInstruction(0x06);				// Set Entry Mode	[ I/D = Right						S = Shift L	]
	setInstruction(0x01);				// Clear Display

}




/*
//==================================================================================================
								Interface Connector Pin Setting
====================================================================================================
	  Pin No.	 |		Symbol		|							 Setting
   P    S    F   |					|
----------------------------------------------------------------------------------------------------
   7    2   11   |		 Vcc		|			Supply voltage terminal for Logic
   8    6   15   |		 Vs			|			Supply voltage terminal for Motor Driver
   4    8    5   |		 Vref		|			Supply voltage terminal for Control
   1    5    1   |		 GND		|			Ground
   5    9    7   |		 IN1		|			Input 1
   6    1    9   |		 IN2		|			Input 2
   2    7    4   |		 OUT1		|			Output 1
  10    3   13   |		 OUT2		|			Output 2
--------------------------------------------------------------------------------------------------//


//==================================================================================================
										Mode Setting
====================================================================================================
	  Input		 |		Output		|							  Mode
   IN1	   IN2	 |	 OUT1	 OUT2	|
----------------------------------------------------------------------------------------------------
    0	    0	 |	   0	   0	|							  Stop
    1	    0	 |	   H	   L	|							Clock Wise
    0	    1	 |	   L	   H	|						Counter Clock Wise
    1	    1	 |	   L	   L	|							  Break
--------------------------------------------------------------------------------------------------//
*/


/*
//==========================================
			  CLASS - DC Motor
==========================================//
*/

class Motor
{

private:
	int m_MotorPort;

public:
	Motor (int motorPort) { m_MotorPort = motorPort; }
	void attachPort (int portValue);
	void setStop (void) { attachPort( insertBit(0, HIGH) | insertBit(1, HIGH) ); }
	void setBreak (void) { attachPort( insertBit(0, LOW) | insertBit(1, LOW) ); }
	void setStart (bool isClockWise);

};


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
			Set Start DC Motor
//----------------------------------------*/

void Motor::setStart (bool isClockWise)
{
	
	if (isClockWise == true)
	{
		attachPort( insertBit(0, HIGH) | insertBit(1, LOW) );
	}
	
	else
	{
		attachPort( insertBit(0, LOW) | insertBit(1, HIGH) );
	}
	
}




#endif /* MCU_HPP_ */