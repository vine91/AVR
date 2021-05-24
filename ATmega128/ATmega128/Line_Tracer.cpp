/*
 *		NOTE	- Line_Tracer.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.24
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#include "MCU.HPP"


SW sw(B, ON);
Motor motor(D);




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
    
    Setting::beginPort(A, IN);
    Setting::beginPort(B, IN);
    Setting::beginPort(D, OUT);
    
    while (true) 
    {
        
    }
    
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/