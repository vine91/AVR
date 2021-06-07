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
#define COMP	7
#define OVF		8
#define CAPT	9

#define OC0		0
#define OC1A	1
#define OC1B	2
#define OC1C	3
#define OC2		4
#define OC3A	5
#define OC3B	6
#define OC3C	7

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
	void delay_usec (unsigned char cycleValue);
	void delay_msec (unsigned int timeValue);
	
	namespace Features
	{
		int hex (int decimal);
		int ASKII (int decimal);
	}
	
	namespace Setting
	{
		void beginPort (int port, bool isOutput);
		void beginExtend (int extendIndex);
		void beginTimer (int timerIndex, int timerMode);
		void beginPWM (int timerPin);
	}
	
}




#endif /* MCU_HPP_ */