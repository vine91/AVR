/*
 *	  NOTE - MCU.HPP
 *
 * Created - 2021.05.10
 *  Author - 2033112012 CLJ
 */


#ifndef MCU_HPP_
#define MCU_HPP_


#define OFF		0
#define ON		1
#define LOW		0
#define HIGH	1
#define IN		0
#define OUT		1

#define A	0
#define B	1
#define C	2
#define D	3
#define E	4
#define F	5

#define SW_OFF	0x00
#define SW_0	0x01
#define SW_1	0x02
#define SW_2	0x04
#define SW_3	0x08
#define SW_4	0x10
#define SW_5	0x20
#define SW_6	0x40
#define SW_7	0x80




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
		return lowValue;
	}
	
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
	int EIMSKValue = 0x00;
	
	for (int i=0; i<=7; i++)
	{
		if (extendedIndex == i)
		{
			EIMSKValue = insertBit(i, HIGH);
			
			EIMSK += EIMSKValue;
		}
	}
	
	EICRA = 0x00;
}


/*----------------------------------------//
		  Begin Timer Interrupt
//----------------------------------------*/

void Setting::beginTimer (int timerIndex, int timerMode)
{
	
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
	volatile unsigned int m_newValue;
	volatile unsigned int m_oldValue;
	

public:
	void beginSW (int switchPort, bool isReversal) { m_SwitchPort = switchPort; m_isReversal = isReversal; }
	void initSW (void);
	
	volatile unsigned int result;

};


/*----------------------------------------//
			  Switch Source
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

private:
	unsigned int m_LCDPort;
	bool m_isDataLong;

public:
	// PORT
	void beginLCD (int LCDPort, bool isDataLong) { m_LCDPort = LCDPort; m_isDataLong = isDataLong; }
	void attachPort (int portValue);
	
	// INFO
	void setInstruction (int instructionValue);
	void setData (int dataValue);
	void writeString (const char *stringValue);
	void changeLine (int lineIndex, int fileIndex);
	void clearLine (int clearMode);
	void initLCD (void);

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
			 Set Instruction
//----------------------------------------*/

void LCD::setInstruction (int instructionValue)
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


/*----------------------------------------//
				 Set Data
//----------------------------------------*/

void LCD::setData (int dataValue)
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


/*----------------------------------------//
				Write String
//----------------------------------------*/

void LCD::writeString (const char *stringValue)
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
	
	if (clearMode == 0)
	{
		changeLine(1, 1);
		writeString("                ");
		
		changeLine(2, 1);
		writeString("                ");
	}
	
	else if (clearMode == 1)
	{
		changeLine(1, 1);
		writeString("                ");
	}
	
	else if (clearMode == 2)
	{
		changeLine(2, 1);
		writeString("                ");
	}
	
}


/*----------------------------------------//
			  Initialize LCD
//----------------------------------------*/

void LCD::initLCD (void)
{
	setInstruction(0x06);			// SET ENTRY		[ I/D = Right						S = Shift L	]
	setInstruction(0x0c);			// CONTROL DISPLAY	[ D = Display H		C = Cursor L	B = Blink L ]
	setInstruction(0x28);			// SET FUNCTION		[ DL = 4 Bit		N = 2 LINE		F = 5 x 7	]
	setInstruction(0x01);			// CLEAR DISPLAY ALL
}



#endif /* MCU_HPP_ */