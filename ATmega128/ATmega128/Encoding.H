/*
 * Encoding.h
 *
 * Created: 2020-11-12 오후 1:29:57
 *  Author: 2033112012
 */ 


#ifndef ENCODING_H_
#define ENCODING_H_


/*----------------------------------------//
		Encode 10 to 16 in FND
//----------------------------------------*/

int Encoding_FND(unsigned int x)
{
	int Dec = x;
	int Hex = 0x00;
	
	
	if (Dec >= 0 && Dec <= 9)
	{
		Hex = Dec;
	}
	
	if (Dec >= 10 && Dec <= 19)
	{
		Hex = Dec + 6;
	}
	
	if (Dec >= 20 && Dec <= 29)
	{
		Hex = Dec + 12;
	}
	
	if (Dec >= 30 && Dec <= 39)
	{
		Hex = Dec + 18;
	}
	
	if (Dec >= 40 && Dec <= 49)
	{
		Hex = Dec + 24;
	}
	
	if (Dec >= 50 && Dec <= 59)
	{
		Hex = Dec + 30;
	}
	
	if (Dec >= 60 && Dec <= 69)
	{
		Hex = Dec + 36;
	}
	
	if (Dec >= 70 && Dec <= 79)
	{
		Hex = Dec + 42;
	}
	
	if (Dec >= 80 && Dec <= 89)
	{
		Hex = Dec + 48;
	}
	
	if (Dec >= 90 && Dec <= 99)
	{
		Hex = Dec + 54;
	}
	
	
	return Hex;
}


/*----------------------------------------//
		Encode Dec to ASKII in LCD
//----------------------------------------*/

int Encoding_LCD(unsigned int x)
{
	int Dec = x;
	int ASKII = 0x00;
	
	
	if (Dec >= 0 && Dec <= 9)
	{
		ASKII = Dec + 0x30;
	}
	
	
	return ASKII;
}

#endif /* ENCODING_H_ */