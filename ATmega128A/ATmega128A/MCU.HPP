/*
 *	  NOTE - MCU.HPP
 *
 * Created - 2021.05.10
 *  Author - 2033112012 CLJ
 */


#ifndef MCU_HPP_
#define MCU_HPP_


#define OFF 0
#define ON	1

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
			if (isOutput == true)
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
			int value = 0x01;
			
			value = value << i;
			
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
	void initPortLCD (int portLCD);
	void setInstruction (int instructionInfo);
	void setData (int dataInfo);
	void sendString (char *stringInfo);
	void changeLine (bool isFirstLine, int fileIndex);
	void clearLCD (int clearValue);
	void initLCD (void);

};


/*----------------------------------------//
		  	Initialize LCD Port
//----------------------------------------*/

void LCD::initPortLCD (int portLCD)
{
	
	#define BIT_HIGH (PORTx, y)	PORTx |= (1 << y);
	#define BIT_LOW (PORTx, y)	PORTx &= ~(1 << y);
	
	int portValue;
	int portResult;

	for (int i=2; i<=7; i++)
	{
		if (portLCD == i)
		{
			// PORTA
			if (i == A)
			{
				PORTA = portValue;
			}
			
			// PORTB
			else if (i == B)
			{
				PORTB = portValue;
			}
			
			// PORTC
			else if (i == C)
			{
				PORTC = portValue;
			}
			
			// PORTD
			else if (i == D)
			{
				PORTD = portValue;
			}
			
			// PORTE
			else if (i == E)
			{
				PORTE = portValue;
			}
			
			// PORTF
			else if (i == F)
			{
				PORTF = portValue;
			}

			m_ResisterSelectHigh	= BIT_HIGH (portValue, 5);
			m_ResisterSelectLow		= BIT_LOW (portValue, 5);
			m_ReadWriteHigh			= BIT_HIGH (portValue, 6);
			m_ReadWriteLow			= BIT_LOW (portValue, 6);
			m_Enable				= BIT_HIGH (portValue, 7);
			m_Disable				= BIT_LOW (portValue, 7);
			
			portValue = m_PortLCD;

		}
	}
	
}


/*----------------------------------------//
		  	  Set Instruction
//----------------------------------------*/

void LCD::setInstruction (int instructionInfo)
{
	_delay_ms(2);
	
	
	m_PortLCD = ((instructionInfo >> 4) & 0x0F);

	m_ResisterSelectLow;
	m_ReadWriteLow;

	m_Enable;
	_delay_us(1);
	m_Disable;
	_delay_us(1);
	
	
	m_PortLCD = (instructionInfo & 0x0F);
	
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

void LCD::setData (int dataInfo)
{
	_delay_ms(2);
	
	
	m_PortLCD = ((dataInfo >> 4) & 0x0F);

	m_ResisterSelectHigh;
	m_ReadWriteLow;

	m_Enable;
	_delay_us(1);
	m_Disable;
	_delay_us(1);
	
	
	m_PortLCD = (dataInfo & 0x0F);
	
	m_ResisterSelectHigh;
	m_ReadWriteLow;

	m_Enable;
	_delay_us(1);
	m_Disable;
	_delay_us(1);
}


/*----------------------------------------//
		  		Send String
//----------------------------------------*/

void LCD::sendString (char *stringInfo)
{

	while (*stringInfo != '\0')
	{
		setData(*stringInfo)
		*stringInfo ++;
	}

}


/*----------------------------------------//
		  		change Line
//----------------------------------------*/

void LCD::changeLine (bool isFirstLine, int fileIndex)
{

	for (int i=0; i<16; i++)
	{
		if (isFirstLine == true && fileIndex (i + 1))
		{
			int value = 0x80 + i;

			setInstruction(value);
		}

		else if (isFirstLine == false && fileIndex (i + 1))
		{
			int value = 0xC0 + i;

			setInstruction(value);
		}
	}

}



#endif /* MCU_HPP_ */