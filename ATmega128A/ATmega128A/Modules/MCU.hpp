/*
 *		NOTE	- MCU.hpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#ifndef MCU_HPP_
#define MCU_HPP_

#define OFF		0
#define ON		1
#define LOW		0
#define HIGH	1
#define IN		0
#define OUT		1

#define A		0
#define B		1
#define C		2
#define D		3
#define E		4
#define F		5
#define G		6

#define MAINTAIN	0
#define DOWN		1
#define UP			2
#define COMP		3
#define OVF			4
#define CAPT		5

#define OC0			0
#define OC1A		1
#define OC1B		2
#define OC1C		3
#define OC2			4
#define OC3A		5
#define OC3B		6
#define OC3C		7
#define CORRECT		8
#define FAST		9

#define _OCR0		0xFF			// Compare with 0xFF	Timer0
#define _OCR2		0xA0			// Compare with 0xA0	Timer2
#define _OCR1AH		0x3D
#define _OCR1AL		0x09			// Compare with 0x3D09	Timer1
#define _OCR3AH		0x3D
#define _OCR3AL		0x09			// Compare with 0x3D09	Timer3

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>




/*
//==========================================
			  NAMESPACE - MCU
==========================================//
*/

namespace MCU
{
	
	int insertBit (int bitValue, bool isHigh);
	void delay_us (unsigned char cycleValue);
	void delay_ms (unsigned int timeValue);
	
	namespace Features
	{
		int hex (int decimal);
		int ASKII (int decimal);
	}
	
	namespace Setting
	{
		void beginPort (int port, bool isOutput);
		void beginExtend (int extendIndex, int extendMode);
		void beginTimer (int timerIndex, int timerMode);
		void beginPWM (int PWMIndex, int PWMMode);
	}
	
}




#endif /* MCU_HPP_ */