/*
 * uartlib.c
 *
 * Created: 04.06.2024 22:10:43
 *  Author: Administrator
 */ 

#include "main.h"
#include "uartlib.h"

void UARTInit()
{		
	UCSRA = 0x00;
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UBRRL = 25;
}

void UARTSend(char Value)
{
	while (!(UCSRA & (1 << UDRE)))
	{
				
	}		
	UDR = Value;
}

char UARTReceive()
{
	while (!(UCSRA & (1 << RXC)))
	{
		
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
