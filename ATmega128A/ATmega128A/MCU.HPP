/*
 *	  NOTE - MCU.HPP
 *
 * Created - 2021.05.10
 *  Author - 2033112012 CLJ
 */


#ifndef MCU_HPP_
#define MCU_HPP_


#define LOW		0
#define HIGH	1

#define IN	0
#define OUT	1
#define A	2
#define B	3
#define C	4
#define D	5
#define E	6
#define F	7



namespace Setting
{
	void initPort (int port, bool isOutput);
	void beginExtended (int extendedIndex);
	void beginTimer (int timerIndex, int timerMode);
	void initSwitch (int portSwitch);
}


/*----------------------------------------//
			  Initialize Port
//----------------------------------------*/

void Setting::initPort (int port, bool isOutput)
{
	
	int ddrValue;
	int portValue;
	
	for (int i=2; i<=7; i++)
	{
		if (port == i)
		{
			// INPUT or OUTPUT
			if (isOutput == OUT)
			{
				ddrValue = 0xFF;
				portValue = 0x00;
			}
			
			else
			{
				ddrValue = 0x00;
			}
			
			
			// PORTA
			if (i == A)
			{
				DDRA = ddrValue;
				PORTA = portValue;
			}
			
			// PORTB
			else if (i == B)
			{
				DDRB = ddrValue;
				PORTB = portValue;
			}
			
			// PORTC
			else if (i == C)
			{
				DDRC = ddrValue;
				PORTC = portValue;
			}
			
			// PORTD
			else if (i == D)
			{
				DDRD = ddrValue;
				PORTD = portValue;
			}
			
			// PORTE
			else if (i == E)
			{
				DDRE = ddrValue;
				PORTE = portValue;
			}
			
			// PORTF
			else if (i == F)
			{
				DDRF = ddrValue;
				PORTF = portValue;
			}

		}
	}
	
}


/*----------------------------------------//
		 Begin Extended Interrupt
//----------------------------------------*/

void Setting::beginExtended (int extendedIndex)
{
	
	for (int i=0; i<=7; i++)
	{
		if (extendedIndex == i)
		{
			int value = 1 << i;
			
			EIMSK += value;
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


/*----------------------------------------//
		  	Initialize Switch
//----------------------------------------*/

void Setting::initSwitch (int portSwitch)
{
	
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


class LCD
{

private:
	unsigned int m_PortLCD;
	unsigned int m_ResisterSelectHigh;					// Resister Select
	unsigned int m_ResisterSelectLow;
	unsigned int m_ReadWriteHigh;						// Read and Write
	unsigned int m_ReadWriteLow;
	unsigned int m_Enable;								// Enable
	unsigned int m_Disable;

public:
	// PORT
	void beginLCD (int portLCD);
	void attachBit (bool isHigh, int bitValue);
	void attachPortLCD (int portValue);
	void initPortLCD (void);

	// INFO
	void setInstruction (int instructionValue);
	void setData (int dataValue);
	void writeString (char *stringValue);
	void writeLine (int lineIndex, int fileIndex);
	void clearLCD (int clearMode);
	void initLCD (void);

};


/*----------------------------------------//
		  		Begin LCD
//----------------------------------------*/

void LCD::beginLCD (int portLCD)
{
	for (int i=2; i<=7; i++)
	{
		if (portLCD == i)
		{
			m_PortLCD = i;
		}
	}
}


/*----------------------------------------//
		  		Attach Bit
//----------------------------------------*/

void LCD::attachBit (bool isHigh, int bitValue)
{
	// PORTA
	if (m_PortLCD == A)
	{
		if (isHigh == HIGH)
		{
			PORTA |= (1 << bitValue)
		}

		else
		{
			PORTA &= ~(1 << bitValue)
		}
	}

	// PORTB
	else if (m_PortLCD == B)
	{
		if (isHigh == HIGH)
		{
			PORTB |= (1 << bitValue)
		}

		else
		{
			PORTB &= ~(1 << bitValue)
		}
	}

	// PORTC
	else if (m_PortLCD == C)
	{
		if (isHigh == HIGH)
		{
			PORTC |= (1 << bitValue)
		}

		else
		{
			PORTC &= ~(1 << bitValue)
		}
	}

	// PORTD
	else if (m_PortLCD == D)
	{
		if (isHigh == HIGH)
		{
			PORTD |= (1 << bitValue)
		}

		else
		{
			PORTD &= ~(1 << bitValue)
		}
	}

	// PORTE
	else if (m_PortLCD == E)
	{
		if (isHigh == HIGH)
		{
			PORTE |= (1 << bitValue)
		}

		else
		{
			PORTE &= ~(1 << bitValue)
		}
	}

	// PORTF
	else if (m_PortLCD == F)
	{
		if (isHigh == HIGH)
		{
			PORTF |= (1 << bitValue)
		}

		else
		{
			PORTF &= ~(1 << bitValue)
		}
	}
}


/*----------------------------------------//
		  	  Attach LCD Port
//----------------------------------------*/

void LCD::attachPortLCD (int portValue)
{
	// PORTA
	if (m_PortLCD == A)
	{
		PORTA = portValue;
	}

	// PORTB
	else if (m_PortLCD == B)
	{
		PORTB = portValue;
	}

	// PORTC
	else if (m_PortLCD == C)
	{
		PORTC = portValue;
	}

	// PORTD
	else if (m_PortLCD == D)
	{
		PORTD = portValue;
	}

	// PORTE
	else if (m_PortLCD == E)
	{
		PORTE = portValue;
	}

	// PORTF
	else if (m_PortLCD == F)
	{
		PORTF = portValue;
	}
}


/*----------------------------------------//
		  	Initialize LCD Port
//----------------------------------------*/

void LCD::initPortLCD (void)
{
	m_ResisterSelectHigh	= attachBit(HIGH, 5);
	m_ResisterSelectLow		= attachBit(LOW, 5);
	m_ReadWriteHigh			= attachBit(HIGH, 6);
	m_ReadWriteLow			= attachBit(LOW, 6);
	m_Enable				= attachBit(HIGH, 7);
	m_Disable				= attachBit(LOW, 7);
}


/*----------------------------------------//
		  	  Set Instruction
//----------------------------------------*/

void LCD::setInstruction (int instructionValue)
{
	_delay_ms(2);
	
	
	attachPortLCD((instructionValue >> 4) & 0x0F);

	m_ResisterSelectLow;
	m_ReadWriteLow;

	m_Enable;
	_delay_us(1);
	m_Disable;
	_delay_us(1);
	

	attachPortLCD(instructionValue & 0x0F);
	
	m_ResisterSelectLow;
	m_ReadWriteLow;

	m_Enable;
	_delay_us(1);
	m_Disable;
	_delay_us(1);
}


/*----------------------------------------//
				 Set Data
//----------------------------------------*/

void LCD::setData (int dataValue)
{
	_delay_ms(2);
	
	
	attachPortLCD((dataValue >> 4) & 0x0F);

	m_ResisterSelectHigh;
	m_ReadWriteLow;

	m_Enable;
	_delay_us(1);
	m_Disable;
	_delay_us(1);
	
	
	attachPortLCD(dataValue & 0x0F);
	
	m_ResisterSelectHigh;
	m_ReadWriteLow;

	m_Enable;
	_delay_us(1);
	m_Disable;
	_delay_us(1);
}


/*----------------------------------------//
		  		Write String
//----------------------------------------*/

void LCD::writeString (char *stringValue)
{

	while (*stringValue != '\0')
	{
		setData(*stringValue)
		*stringValue ++;
	}

}


/*----------------------------------------//
		  		Write Line
//----------------------------------------*/

void LCD::writeLine (int lineIndex, int fileIndex)
{

	for (int i=0; i<16; i++)
	{
		if (lineIndex == 1 && fileIndex (i + 1))
		{
			int value = 0x80 + i;

			setInstruction(value);
		}

		else if (lineIndex == 2 && fileIndex (i + 1))
		{
			int value = 0xC0 + i;

			setInstruction(value);
		}
	}

}


/*----------------------------------------//
		  		Clear LCD
//----------------------------------------*/

void LCD::clearLCD (int clearMode)
{

	if (clearMode == 0)
	{
		writeLine(1, 1);
		writeString("                ");

		writeLine(2, 1);
		writeString("                ");
	}

	else if (clearMode == 1)
	{
		writeLine(1, 1);
		writeString("                ");
	}

	else if (clearMode == 2)
	{
		writeLine(2, 1);
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