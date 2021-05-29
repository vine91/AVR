/*
 *		NOTE	- SW.hpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#ifndef SW_HPP_
#define SW_HPP_

#define SW_OFF	0x00
#define SW_0	0x01
#define SW_1	0x02
#define SW_2	0x04
#define SW_3	0x08
#define SW_4	0x10
#define SW_5	0x20
#define SW_6	0x40
#define SW_7	0x80

typedef volatile unsigned int NonOptimal;
//using NonOptimal = volatile unsigned int;




/*
//==========================================
			CLASS - SW (Switch)
==========================================//
*/

class SW
{

private:
	unsigned int m_SwitchPort;
	bool m_isReversal;
	NonOptimal m_NewValue;
	NonOptimal m_OldValue;

public:
	SW (int switchPort, bool isReversal) { m_SwitchPort = switchPort; m_isReversal = isReversal; }
	void init (void);

	NonOptimal result;

};




#endif /* SW_HPP_ */