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
	PORTA = 0xF0;
	PORTC = 0x06;
    while(1)
    {
        //TODO:: Please write your application code 
    }
}