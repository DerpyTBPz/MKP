/*
 * AVRGCC5.c
 *
 * Created: 27.04.2024 10:03:31
 *  Author: student
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>


#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BUT1	0x04
#define		BUT2	0x08

void UARTSend(char x);
char UARTReceive();
void SendString(char * str);

char text[] = "Baba s bebe ";
char string[128];
int num = 2048;

int main(void)
{
	DDRD |= 0xFF;
	MCUCR = 0x0F;
	GICR = 0xC0;
	
	UCSRA = 0x00;
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UBRRL = 25;   
	
	sei();	
	
    while(1)
    {
		//PORTD ^= RED;
		
		//UARTSend(UARTReceive());	
		//itoa(num, string, 10);	
		
// 		SendString(string);
// 		UARTSend('\r');
// 		UARTSend('\n');
// 		_delay_ms(1000);		
		
// 		for (int i = 0; i < sizeof(text) - 1; i++)
// 		{
// 			UARTSend(text[i]);			
// 			_delay_ms(100);
// 		}					
		
		//_delay_ms(1000);	
		
        //TODO:: Please write your application code 	
		
    }
}

void UARTSend(char Value)
{
	while (!(UCSRA & (1 << UDRE)))
	{
		;
	}		
	UDR = Value;
}

char UARTReceive()
{
	while (!(UCSRA & (1 << RXC)))
	{
		;
	}		
	return UDR; 
}

void SendString(char* str)
{
	while(*str != '\0')
	{
		UARTSend(*str);
		str++;
	}
	//UARTSend(*str);
	UARTSend('\r');
	UARTSend('\n');
}

ISR(INT0_vect)
{
	num++;
	itoa(num, string, 10);	
	SendString(string);
}

ISR(INT1_vect)
{
	if (num != 0)
	{
		num--;
		itoa(num, string, 10);
		SendString(string);
	}
}

