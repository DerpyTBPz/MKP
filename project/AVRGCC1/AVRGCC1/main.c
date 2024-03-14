/*
 * AVRGCC1.c
 *
 * Created: 17.02.2024 9:34:34
 *  Author: student
 */ 
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

/* board
#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BUT1	0x04
#define		BUT2	0x0
*/

#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BUT1	0x04
#define		BUT2	0x08

// port change for simulator (comment on board)
// #define		DDRD	DDRA
// #define		PORTD	PORTA



void task1();
void task2();
void task3();
void task4();
void task5();
void task6();

void test();

// BUT1 INT
ISR(INT0_vect)
{
	PORTD ^= BLUE;	
}

// BUT2 INT
ISR(INT1_vect)
{
	PORTD ^= RED;
}

ISR_ALIASOF(INT1_vect, INT0_vect)
{
	PORTD ^= RED;
};


int main(void)
{
// 	task1();
// 	task2();
// 	task3();
// 	task4();
// 	task5();
	task6();
	 
//	test();
		
    while(1)
    {	
        //TODO:: Please write your application code 
	}
}

void task1()
{
	DDRD |= GREEN;
	while(1)
	{
		_delay_ms(1000);
		PORTD = GREEN;
		_delay_ms(1000);
		PORTD = 0x00;
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
	MCUCR = 0x03; //0x0F 0x03
	GICR = 0x40; //0xC0 0x40
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

void task6()
{
	DDRD = 0xB0;
	MCUCR = 0x0F; //0x0F 0x03
	GICR = 0xC0; //0xC0 0x40
	sei();	
}

void test()
{
	DDRD |= RED | GREEN | BLUE | BUT1 | BUT2;
	PIND |= BUT1 | BUT2;
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