/*
 * Reset.h
 *
 * Created: 2020-10-21 오후 1:59:36
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
	3		|	Vo		|	Brightness Setting		( Vdd - Vo = 3 ~ 13V)
	4		|	Rs		|	Resister Select			( H = Data			L = Instruction )
	5		|	R/W		|	Read / Write			( H = LCD to MCU	L = MCU to LCD )
	6		|	E		|	Enable					( H = Enable		L = Disable )
	7		|	D0		|	DATA BIT 0				( LSB )
	8		|	D1		|	DATA BIT 1
	9		|	D2		|	DATA BIT 2
	10		|	D3		|	DATA BIT 3
	11		|	D4		|	DATA BIT 4
	12		|	D5		|	DATA BIT 5
	13		|	D6		|	DATA BIT 6
	14		|	D7		|	DATA BIT 7				( MSB )
	15		|	A		|	Anode					( VCC for LED or EL Back light )
	16		|	K		|	Cathode					( GND for LED or EL Back light )
--------------------------------------------------------------------------------------------------//


//==================================================================================================
										Instruction Setting
====================================================================================================
				Instruction				|	Signal	|	Code
										| Rs	R/W	|	DB7	 DB6  DB5  DB4  DB3  DB2  DB1  DB0
----------------------------------------------------------------------------------------------------
	Clear Display						|  0	 0	|	 0	  0	   0	0	 0	  0    0	1
	Return Home							|  0	 0	|	 0	  0	   0	0	 0	  0    1	-
	Set Entry							|  0	 0	|	 0	  0	   0	0	 0	  1   I/D	S
	Control Display ON/OFF				|  0	 0	|	 0	  0	   0	0	 1	  D    C	B
	Shift Cursor or Display				|  0	 0	|	 0	  0	   0	1	S/C	 R/L   -	-
	Set Function						|  0	 0	|	 0	  0	   1	DL	 N	  F    -	-
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


#ifndef RESET_H_
#define RESET_H_

#define ON 1
#define OFF 0

volatile unsigned int SW_Event_N;
volatile unsigned int SW_Event_O;
volatile unsigned int SW_Address;


/*----------------------------------------//
			Reset ATmega128 MCU
//----------------------------------------*/

void MCU_Reset(void)
{
	
	DDRA = 0xFF;			// PORTA OUTPUT
	PORTA = 0x00;
	
	DDRB = 0xFF;			// PORTB OUTPUT
	PORTB = 0x00;
	
	DDRC = 0x00;			// PORTC INPUT

	DDRD = 0xFF;			// PORTD OUTPUT
	PORTD = 0x00;
	
	DDRE = 0xFF;			// PORTE OUTPUT
	PORTE = 0x00;
	
	DDRF = 0xFF;			// PORTF OUTPUT
	PORTF = 0x00;
	
/*----------------------------------------------*/
	
	//EIMSK = 0x01;			// EXTENDED INTERRUPT
	//EICRA = 0x00;			// EXTENDED INTERRUPT TRIGER

/*----------------------------------------------*/

	TIMSK = 0x50;			// TIMER INTERRUPT
/*
	TCCR0 = 0x07;			// CLOCK 1024		[ T/I	0, 2 ]
	TCNT0 = 0x00;			// COUNTING			[ T/I	0, 2 ]
	//OCR0 = 0x99;			// COMPARING		[ T/I	0, 2 ]
*/
	TCCR2 = 0x05;
	TCNT2 = 0x00;
	//OCR2 = 0x99;

	TCCR1A = 0x00;			// CTC MODE			[ T/I	1, 3 ]
	TCCR1B = 0x0D;			// CLOCK 1024
	TCNT1H = 0x00;			// COUNTING			[ T/I	1, 3 ]
	TCNT1L = 0x00;
	OCR1AH = 0x3D;			// COMPARING		[ T/I	1, 3 ]
	OCR1AL = 0x09;
	
}


/*----------------------------------------//
				Reset Switch
//----------------------------------------*/

void SW_Reset(void)
{
	
	#define SW_OFF 0x00
	#define SW_0 0x01
	#define SW_1 0x02
	#define SW_2 0x04
	#define SW_3 0x08
	#define SW_4 0x10
	#define SW_5 0x20
	#define SW_6 0x40
	#define SW_7 0x80
	
	SW_Event_N = PINC;
	SW_Address = SW_Event_O & (~SW_Event_N);
	SW_Event_O = SW_Event_N;

}

#endif /* RESET_H_ */