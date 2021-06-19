/*
 *		NOTE	- line_tracer_ex.cpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.06.17
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#include "Modules/MCU.hpp"
#include "Modules/SW.hpp"
#include "Modules/motor.hpp"

using namespace MCU::Features;
using namespace MCU::Setting;


ISR(TIMER2_COMP_vect);

SW sensor(F, SENSOR);
Motor right(OC1A);
Motor left(OC1C);

bool g_isStart = ON;




/*========================================//
-------------   MAIN START   ---------------
//========================================*/

int main(void)
{
	beginPort(B, OUT);
	beginPort(F, IN);
	
	beginTimer(2, COMP);
	
	beginPWM(OC1A, CORRECT);
	beginPWM(OC1C, CORRECT);
	
	left.setSpeed(25);
	right.setSpeed(25);
	
	sei();
	
    while (true) 
    {
		left.start();
		right.start();
    }
	
	return 0;
}

/*========================================//
--------------   MAIN END   ----------------
//========================================*/


ISR(TIMER2_COMP_vect)
{
	
	if (g_isStart == ON)
	{
		
		sensor.setMax(0x15);
		sensor.init();
		
		switch (sensor.result)
		{
			case 0x08:
				left.setSpeed(18);				// 0b 0000 1000, Left Sensor
				right.setSpeed(22);				// 오른쪽으로 완전히 치우쳐 졌을때, 오른쪽 바퀴를 더 돌림.
				break;
			
			case 0x0A:
				left.setSpeed(22);				// 0b 0000 1000, Left Sensor ; 0b 0000 0010, Middle Sensor
				right.setSpeed(25);				// 오른쪽으로 치우쳐 졌을때, 오른쪽 바퀴를 돌림.
				break;
			
			case 0x02:
				left.setSpeed(25);				// 0b 0000 0010, Middle Sensor
				right.setSpeed(25);				// 가운데에 있을때, 전진.
				break;
			
			case 0x03:
				left.setSpeed(25);				// 0b 0000 0010, Middle Sensor ; 0b 0000 0001, Right Sensor
				right.setSpeed(22);				// 왼쪽으로 치우쳐 졌을때, 왼쪽 바퀴를 돌림.
				break;
			
			case 0x01:
				left.setSpeed(22);				// 0b 0000 0001, Right Sensor
				right.setSpeed(18);				// 왼쪽으로 완전히 치우쳐 졌을때, 왼쪽 바퀴를 더 돌림.
				
				break;
			
			case 0x00:
				if (sensor.oldData == 0x01)
				{
					left.setSpeed(0);
					right.setSpeed(18);
				}
				
				else if (sensor.oldData == 0x10)
				{
					left.setSpeed(18);
					right.setSpeed(0);
				}
			
			default:
				break;
		}
		
	}
	
	if (sensor.result == sensor.maxData)
	{
		sensor.oldData = sensor.oldData;
	}
	
	else
	{
		sensor.oldData = sensor.result;
	}
	
}