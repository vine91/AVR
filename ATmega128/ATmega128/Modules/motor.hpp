/*
 *		NOTE	- motor.hpp
 *	 Copyright	- NULL
 *
 * 	 Created	- 2021.05.30
 *   Author		- 2033112012 CLJ
 * 	 Contact	- vine9151@gmail.com
 */


#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#define CCW		0
#define CW		1




/*
//==================================================================================================
								Interface Connector Pin Setting
====================================================================================================
	  Pin No.	 |		Symbol		|							 Setting
   P    S    F   |					|
----------------------------------------------------------------------------------------------------
   7    2   11   |		 Vcc		|			Supply voltage terminal for Logic
   8    6   15   |		 Vs			|			Supply voltage terminal for Motor Driver
   4    8    5   |		 Vref		|			Supply voltage terminal for Control
   1    5    1   |		 GND		|			Ground
   5    9    7   |		 IN1		|			Input 1
   6    1    9   |		 IN2		|			Input 2
   2    7    4   |		 OUT1		|			Output 1
  10    3   13   |		 OUT2		|			Output 2
--------------------------------------------------------------------------------------------------//


//==================================================================================================
										Mode Setting
====================================================================================================
	  Input		 |		Output		|							  Mode
   IN1	   IN2	 |	 OUT1	 OUT2	|
----------------------------------------------------------------------------------------------------
    0	    0	 |	   0	   0	|							  Stop
    1	    0	 |	   H	   L	|							Clock Wise
    0	    1	 |	   L	   H	|						Counter Clock Wise
    1	    1	 |	   L	   L	|							  Break
--------------------------------------------------------------------------------------------------//
*/


/*
//==========================================
			  CLASS - DC Motor
==========================================//
*/

class Motor
{

private:
	unsigned int m_MotorPort;
	unsigned int m_Speed;
	bool m_isOn;

public:
	Motor (int motorPort) { m_MotorPort = motorPort; }
	void attachPort (int portValue);
	
	// SET SPEED
	void setSpeed (int speedValue);
	
	// SET MOTOR
	void start (bool isClockWise);
	void stop (void);

};




#endif /* MOTOR_HPP_ */