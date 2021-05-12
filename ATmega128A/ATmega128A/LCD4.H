/*
 * LCD4.h
 *
 * Created: 2020-11-19 오후 2:18:43
 *  Author: 2033112012
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


#ifndef LCD4_H_
#define LCD4_H_

#define BH(PORTx, y)	PORTx |= (1 << y);
#define BL(PORTx, y)	PORTx &= ~(1 << y);

#define RS_H		BH(PORTE, 5)			// RESISTER SELECTION
#define RS_L		BL(PORTE, 5)
#define RW_H		BH(PORTE, 6)			// READ AND WRITE
#define RW_L		BL(PORTE, 6)
#define E_H			BH(PORTE, 7)			// ENABLE
#define E_L			BL(PORTE, 7)


/*----------------------------------------//
			LCD Monitor Preferences
//----------------------------------------*/

void LCD_Instruction(unsigned int x)
{
	
	_delay_ms(2);
	
	
	PORTE = ((x >> 4) & 0x0F);
	
	RS_L;
	RW_L;
	E_H;
	_delay_us(1);
	E_L;
	_delay_us(1);
	
	
	PORTE = (x & 0x0F);
	
	RS_L;
	RW_L;
	E_H;
	_delay_us(1);
	E_L;
	_delay_us(1);
	
}


/*----------------------------------------//
			Display char on LCD
//----------------------------------------*/

void LCD_Char(unsigned int x)
{
	
	_delay_ms(2);
	
	
	PORTE = ((x >> 4) & 0x0F);
	
	RS_H;
	RW_L;
	E_H;
	_delay_us(1);
	E_L;
	_delay_us(1);
	
	
	PORTE = (x & 0x0F);
	
	RS_H;
	RW_L;
	E_H;
	_delay_us(1);
	E_L;
	_delay_us(1);
	
}


/*----------------------------------------//
			Display String on LCD
//----------------------------------------*/

void LCD_String(char *x)
{
	
	while (*x != '\0')
	{
		LCD_Char(*x);
		x++;
	}
	
}


/*----------------------------------------//
		Set DD RAM Address with line
//----------------------------------------*/

void LCD_Line(unsigned int x, unsigned int y)
{
	int Line = x;
	int Num = y;
	int Send = 0x00;
	int i;
	
	
	for (i=0; i<16; i++)
	{
		
		if (Line == 1 && Num == (i + 1))
		{
			Send = 0x80 + i;
			
			LCD_Instruction(Send);
		}
		
		if (Line == 2 && Num == (i + 1))
		{
			Send = 0xC0 + i;
			
			LCD_Instruction(Send);
		}
		
	}
}


/*----------------------------------------//
			Clear LCD Monitor
//----------------------------------------*/

void LCD_Clear(int x)
{
	
	if (x == 0)						// CLEAR DISPLAY LINE 1, 2
	{
		LCD_Line(1, 1);
		LCD_String("                ");
		
		LCD_Line(2, 1);
		LCD_String("                ");
	}
	
	if (x == 1)						// CLEAR DISPLAY LINE 1
	{
		LCD_Line(1, 1);
		LCD_String("                ");
	}
	
	if (x == 2)						// CLEAR DISPLAY LINE 2
	{
		LCD_Line(2, 1);
		LCD_String("                ");
	}
	
}

/*----------------------------------------//
			Reset LCD Monitor
//----------------------------------------*/

void LCD_Reset(void)
{
	
	LCD_Instruction(0x06);			// SET ENTRY		[ I/D = Right						S = Shift L	]
	
	LCD_Instruction(0x0c);			// CONTROL DISPLAY	[ D = Display H		C = Cursor L	B = Blink L ]
	
	LCD_Instruction(0x28);			// SET FUNCTION		[ DL = 4 Bit		N = 2 LINE		F = 5 x 7	]
	
	LCD_Instruction(0x01);			// CLEAR DISPLAY ALL
	
}

#endif /* LCD4_H_ */