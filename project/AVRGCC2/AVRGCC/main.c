/*
 * AVRGCC.c
 *
 * Created: 02.03.2024 10:04:05
 *  Author: student
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0xF0;
	DDRC = 0xFF;
	PORTA = 0x10;
	PORTC = 0x06;
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

char DecToDigit(char Dec)
{	
	char Digit = 0;
	
	switch(Dec)
	{
		case 0:
			Digit = 0x00111111;
			break;
		case 1:
			Digit = 0x00000110;
			break;
		case 2:
			Digit = 0x01011011;
			break;
		case 3:
			Digit = 0x01001111;
			break;
		case 4:
			Digit = 0x01100110;
			break;
		case 5:
			Digit = 0x01101101;
			break;
		case 6:
			Digit = 0x01111101;
			break;
		case 7:
			Digit = 0x00000111;
			break;
		case 8:
			Digit = 0x01111111;
			break;		
		case 9:
			Digit = 0x01101111;
			break;
			
	}		
	
}