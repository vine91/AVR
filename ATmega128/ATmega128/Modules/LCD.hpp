/*
 *		NOTE	- LCD.hpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#ifndef LCD_HPP_
#define LCD_HPP_

#define ALL		0

typedef const char* String;
//using String = const char*;




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
										| RS	R/W	|	DB7	 DB6  DB5  DB4		DB3  DB2  DB1  DB0
----------------------------------------------------------------------------------------------------
	Clear Display						|  0	 W	|	 0	  0	   0	0		 0	  0    0	1
	Return Home							|  0	 W	|	 0	  0	   0	0		 0	  0    1	-
	Set Entry							|  0	 W	|	 0	  0	   0	0		 0	  1   I/D	S
	Control Display ON/OFF				|  0	 W	|	 0	  0	   0	0		 1	  D    C	B
	Shift Cursor or Display				|  0	 W	|	 0	  0	   0	1		S/C	 R/L   -	-
	Set Function						|  0	 W	|	 0	  0	   1	DL		 N	  F    -	-
	Set CG RAM Address					|  0	 W	|	 0	  1		   CG RAM Address
	Set DD RAM Address					|  0	 W	|	 1			   DD RAM Address
----------------------------------------------------------------------------------------------------
	Read Busy Flag and Address Counter	|  0	 R	|	 BF			  Address Counter
----------------------------------------------------------------------------------------------------
	Write Data to CG RAM or DD RAM		|  1	 W	|					Write Data
	Read Data to CG RAM or DD RAM		|  1	 R	|					 Read Data
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
	
	// PORT SETTINGS
	void attachPort (int portValue);
	void attachExtendPort (int extendPortValue);
	void exportInstruction (int instructionValue);
	void exportData (int dataValue);
	
	// FEATURES
	void print (String stringValue);
	void setLine (int lineIndex, int fileIndex);
	void clear (int clearMode);
	void init (void);

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




#endif /* LCD_HPP_ */