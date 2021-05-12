/*
 *	  NOTE - MCU.HPP
 *
 * Created - 2021.05.10
 *  Author - 2033112012 CLJ
 */


/*
//==================================================================================================
								Interface Connector Pin Setting
====================================================================================================
	Pin		|	Signal	|								Setting
----------------------------------------------------------------------------------------------------
	1		|	Vss		|	Ground					( GND )
	2		|	Vdd		|	DC 5V					( VCC )
	3		|	Vo		|	Brightness Setting		( Vdd - Vo = 3 ~ 13V)					-PE4-
	4		|	RS		|	Resister Select			( H = Data			L = Instruction )	-PE5-
	5		|	R/W		|	Read / Write			( H = LCD to MCU	L = MCU to LCD )	-PE6-
	6		|	E		|	Enable					( H = Enable		L = Disable )		-PE7-
	7		|	DB0		|	DATA BUS 0				( LSB )
	8		|	DB1		|	DATA BUS 1
	9		|	DB2		|	DATA BUS 2
	10		|	DB3		|	DATA BUS 3
	11		|	DB4		|	DATA BUS 4														-PE0-
	12		|	DB5		|	DATA BUS 5														-PE1-
	13		|	DB6		|	DATA BUS 6														-PE2-
	14		|	DB7		|	DATA BUS 7				( MSB )									-PE3-
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


#ifndef MCU_HPP_
#define MCU_HPP_


#define OFF 0
#define ON	1

#define OUT 0
#define IN	1
#define A	2
#define B	3
#define C	4
#define D	5
#define E	6
#define F	7


namespace Setting
{
	void initPort (int port, bool isMode);
	void beginExtended (int extendedIndex);
	void beginTimer (int timerIndex, int timerMode);
}


/*----------------------------------------//
			  Initialize Port
//----------------------------------------*/

void Setting::initPort (int port, bool isMode)
{
	
	int ddrValue;
	int portValue;
	
	for (int i=2; i<=7; i++)
	{
		if (port == i)
		{
			// INPUT or OUTPUT
			if (isMode == IN)
			{
				ddrValue = 0x00;
			}
			
			else
			{
				ddrValue = 0xFF;
				portValue = 0x00;
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


class LCD
{

private:
	unsigned int m_PortLCD;
	unsigned int m_ResisterSelectionHigh;				// Resister Selection
	unsigned int m_ResisterSelectionLow;
	unsigned int m_ReadWriteHigh;						// Read and Write
	unsigned int m_ReadWriteLow;
	unsigned int m_Enable;								// Enable
	unsigned int m_Disable;

public:
	void initPortLCD (int portLCD);
	void setInstruction (int instructionInfo);
	void setData (int dataInfo);
	void setString (int stringInfo);
	void setLine (int line, int file);
	void clearLCD (int resetLCD);
	void initLCD (void);

};

void LCD::initPortLCD (int portLCD)
{
	
	#define BIT_HIGH (PORTx, y)	PORTx |= (1 << y);
	#define BIT_LOW (PORTx, y)	PORTx &= ~(1 << y);
	
	int portValue;
	int portValueLCD;

	for (int i=2; i<=7; i++)
	{
		if (portLCD == i)
		{
			m_ResisterSelectionHigh	= BIT_HIGH (portValue, 5);
			m_ResisterSelectionLow	= BIT_LOW (portValue, 5);
			m_ReadWriteHigh			= BIT_HIGH (portValue, 6);
			m_ReadWriteLow			= BIT_LOW (portValue, 6);
			m_Enable				= BIT_HIGH (portValue, 7);
			m_Disable				= BIT_LOW (portValue, 7);
			
			m_PortLCD = portValueLCD;
			
			
			// PORTA
			if (i == A)
			{
				PORTA = portValue;
				portValueLCD = PORTA;
			}
			
			// PORTB
			else if (i == B)
			{
				PORTB = portValue;
				portValueLCD = PORTB;
			}
			
			// PORTC
			else if (i == C)
			{
				PORTC = portValue;
				portValueLCD = PORTC;
			}
			
			// PORTD
			else if (i == D)
			{
				PORTD = portValue;
				portValueLCD = PORTD;
			}
			
			// PORTE
			else if (i == E)
			{
				PORTE = portValue;
				portValueLCD = PORTE;
			}
			
			// PORTF
			else if (i == F)
			{
				PORTF = portValue;
				portValueLCD = PORTF;
			}
		}
	}
	
}


#endif /* MCU_HPP_ */