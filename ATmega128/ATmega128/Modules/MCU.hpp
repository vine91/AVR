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
#define COMP	6
#define OVF		7
#define CAPT	8

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
	
	namespace Features
	{
		void delayCycle (unsigned char CycleValue);
		int hex (int decimal);
		int ASKII (int decimal);
	}
	
	namespace Setting
	{
		void beginPort (int port, bool isOutput);
		void beginExtend (int extendIndex);
		void beginTimer (int timerIndex, int timerMode);
	}
	
}




#endif /* MCU_HPP_ */