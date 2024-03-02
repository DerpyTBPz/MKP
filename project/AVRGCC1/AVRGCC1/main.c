/*
 * AVRGCC1.c
 *
 * Created: 17.02.2024 9:34:34
 *  Author: student
 */ 
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BUT1	0x04
#define		BUT2	0x08

void task1();
void task2();
void task3();
void task4();

ISR(INT0_vect)
{
	PORTD ^= BLUE;	
}

int main(void)
{
	//int flag = 0;
	//DDRD |= RED | GREEN | BLUE | BUT1;
	//task4();
	//.PORTD = BLUE;
	//_delay_ms(1000);
	
// 	task1();
// 	task2();
// 	task3();
// 	task4();
 	task5();
		
    while(1)
    {		
		
		//task1();
		//task2();
		//task3(flag);
		
				
		
        //TODO:: Please write your application code 
	}
}

void task1()
{
	DDRD |= RED;
	while(1)
	{
		PORTD = RED;
	}
}

void task2()
{
	DDRD |= RED | GREEN | BLUE;
	while(1)
	{
		PORTD = RED;
		_delay_ms(1000);
		PORTD = GREEN;		
		_delay_ms(1000);	
		PORTD = BLUE;		
		_delay_ms(1000);
	}		
}

void task3()
{
	DDRD |= RED | GREEN | BLUE | BUT1;
	DDRD &= ~BUT1;

	while(1)
	{
		if (PIND & BUT1)
		{
			PORTD = BLUE;
		}
		else
		{
			PORTD = 0x0;		
		}
	}	
}

// void task3(int flag)
// {
// 	while(1)
// 	{		
// 		if (flag == 1)
// 		{
// 			if (PIND & BUT1)
// 			{			
// 				flag = 0;
// 				PORTD = RED;
// 			}
// 			else
// 			{
// 				PORTD = GREEN;			
// 			}
// 				
// 		}
// 		else
// 		{
// 			if (PIND & BUT1)
// 			{			
// 				flag = 1;
// 			}			
// 		}
// 	}		
// }

void task4()
{
	DDRD = 0xB0;
	MCUCR = 0x03;
	GICR = 0x40;
	sei();	
}

void task5()
{
	DDRD |= RED | GREEN | BLUE | BUT1 | BUT2;
	while(1)
	{
		if (PIND & BUT1)
		{
			PORTD = BLUE;
		}
		else if (PIND & BUT2)
		{
			PORTD = GREEN;		
		}
		else if (PIND & (BUT1 | BUT2))
		{
			PORTD = RED;
		}
		else
		{
			PORTD = 0x0;
		}
	}	
}