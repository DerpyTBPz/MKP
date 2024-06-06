/*
 * AVRGCC8.c
 *
 * Created: 06.06.2024 21:24:17
 *  Author: Administrator
 */ 

#include "main.h"
#include "uartlib.h"

#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BTN1	0x04
#define		BTN2	0x08
#define		DIGITS	4

ISR(TIMER2_COMP_vect);

void TimerInit();
void NumToArr(int numbr);
unsigned char DecToDigit(unsigned char Dec);

int j = 0;
int arr[DIGITS];
int num = 1488;
int hr, mn, sc;

int main(void)
{	
	DDRA = 0xF0;
	DDRC = 0xFF;
	DDRD |= RED | GREEN | BLUE | BTN1 | BTN2;
	MCUCR = 0x0F;
	GICR = 0xC0;
		
	PORTA = 0x00;
	PORTC = 0x00;
	
	TimerInit();
		
	PORTD = 0x0;
	sei();
	
	while(1)
	{
		NumToArr(num);
	}
}

void TimerInit()
{
	//TIMER0
	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
	OCR0 = 20;
	TIMSK |= (1 << OCIE0);

// 	//TIMER1
// 	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
// 	TCCR1B |= (1<<WGM12) | (1<<CS10);
// 	OCR1A = 10;
// 	TIMSK |= (1 << OCIE1A);		
	
	//TIMER2
	TCCR2 |= (1<<WGM21) | (1<<CS22) | (1<<CS21);
	OCR2 = 10;
	TIMSK |= (1 << OCIE2);
}

ISR(TIMER0_COMP_vect)
{	
	
}

ISR(TIMER2_COMP_vect)
{	
	PORTC = 0x00;
	PORTA = 0x00;
	
	PORTC = DecToDigit(arr[j]);	
	
	if (j == 2)
	{			
		PORTC |= 0b10000000;	
	}	
		
	PORTA = (1 << (7 - j));			
	j++;
	j %= 4;
}

void NumToArr(int numbr)
{	
	for (int k = 0; k < DIGITS; k++)
	{		
		arr[k] = numbr % 10;
		numbr /= 10;
	}
}

unsigned char DecToDigit(unsigned char Dec)
{	
	unsigned char Digit;
	
	switch(Dec)
	{
		case 0:
			Digit = 0b01011111;				
			break;
		case 1:
			Digit = 0b00000110;					
			break;
		case 2:
			Digit = 0b00111011;					
			break;
		case 3:
			Digit = 0b00101111;
			break;
		case 4:
			Digit = 0b01100110;
			break;
		case 5:
			Digit = 0b01101101;
			break;
		case 6:
			Digit = 0b01111101;
			break;
		case 7:
			Digit = 0b00000111;
			break;
		case 8:
			Digit = 0b01111111;
			break;		
		case 9:
			Digit = 0b01101111;
			break;
		default:
			Digit = 0b00000000;
			break;			
 	}	
	 
	return Digit;
}
