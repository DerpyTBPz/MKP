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

ISR(TIMER0_COMP_vect);
ISR(TIMER1_COMPA_vect);
ISR(TIMER2_COMP_vect);

void TimerInit();
void NumToArr(int numbr);
unsigned char DecToDigit(unsigned char Dec);

int j = 0;
int arr[DIGITS];
int HH = 21;
int MM = 43;
int SS = 0;
int time = 0;
char timeArr[8];

char string[128];
int sendTime = 0;
int timeMode = 0;
int flag = 0;
char tmp[3];

int main(void)
{	
	DDRA = 0xF0;
	DDRC = 0xFF;
	DDRD |= RED | GREEN | BLUE | BTN1 | BTN2;
	MCUCR = 0x0F;
	GICR = 0xC0;
	
	TimerInit();
	UARTInit();
	
	sei();
	
	while(1)
	{
		SendTime();
		
		if (timeMode == 1)
		{
			while(1)
			{			
				SendString("Enter hours (HH)");			
				tmp[0] = UARTReceive();
				tmp[1] = UARTReceive();				
				HH = atoi(tmp);				
				if (HH > 23)
				{
					SendString("Wrong hours");
					break;
				}
				
				SendString("Enter minutes (MM)");				
				tmp[0] = UARTReceive();
				tmp[1] = UARTReceive();				
				MM = atoi(tmp);				
				if (MM > 59)
				{
					SendString("Wrong minutes");
					break;
				}
				
				SendString("Enter seconds (SS)");				
				tmp[0] = UARTReceive();
				tmp[1] = UARTReceive();				
				SS = atoi(tmp);			
			
			
// 				PORTA = 0xF0;
// 				PORTC = 0xFF;
// 				_delay_ms(1000);
// 				PORTC = 0x00;
// 				_delay_ms(1000);
			}			
		}
//		TimeArray(HH, MM, SS);
//		SendString(timeArr);
// 		if (sendTime == 1)
// 		{
// 			SendTime();
// 		}		
	}
}

void TimerInit()
{
	//TIMER0
// 	TCCR0 |= (1 << WGM00) | (1 << CS02) | (1 << CS00);
// 	OCR0 = 200;
// 	TIMSK |= (1 << OCIE0);

 	//TIMER1	
	TCNT1 |= 0;
	OCR1A |= 15625;
	TCCR1A |= (1 << FOC1A);
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
	TIMSK |= (1 << OCIE1A);
	
	
	//TIMER2
	TCCR2 |= (1<<WGM21) | (1<<CS22) | (1<<CS21);
	OCR2 = 5;
	TIMSK |= (1 << OCIE2);
}

ISR(TIMER0_COMP_vect)
{	
	
}

ISR(TIMER1_COMPA_vect)
{
	if (timeMode == 0)
	{
		SS++;
		if (SS == 60)
		{
			MM++;
			SS = 0;
			if (MM == 60)
			{
				HH++;
				MM = 0;
			}
		}
		time = (HH * 100) + MM;	
		NumToArr(time);
	}
	else if (timeMode == 1)
	{
		
	}
	
	
	//time = (MM * 100) + SS;
	
// 	
// 	timeStr = "Time is ";
// 	itoa(HH, string, 10);
// 	timeStr += string + ":";
// 	itoa(MM, string, 10);
// 	timeStr += string + ":";
// 	itoa(SS, string, 10);
// 	SendString(timeStr);
}

ISR(TIMER2_COMP_vect)
{	
	
	if (timeMode == 0)
	{
		
		PORTC = 0x00;
		PORTA = 0x00;
			
		PORTC = DecToDigit(arr[j]);
		
		if ((j == 2) && ((SS % 2) == 0))
		{			
			PORTC ^= 0b10000000;	
		}	
		
		PORTA = (1 << (7 - j));			
		j++;
		j %= 4;
	}
}

ISR(INT0_vect)
{
	timeMode++;
	
	if (timeMode == 1)
	{
		
	}
	else
	{		
		timeMode = 0;
	}
}

void SendTime()
{
	itoa(HH, string, 10);
	SendString(string);
	UARTSend(':');
	itoa(MM, string, 10);
	SendString(string);
	UARTSend(':');
	itoa(SS, string, 10);
	SendString(string);	
	
 	UARTSend('\r');
 	UARTSend('\n');
			
	sendTime = 0;
}

// void TimeArray(int H, int M, int S)
// {
// 	int tmp = (S * 10000) + (M * 100) + H;
// 	for (int k = 0; k < 8; k++)
// 	{
// 		if ((k == 2) || (k == 5))
// 		{
// 			timeArr[k] = ':';
// 		}
// 		else
// 		{
// 			timeArr[k] = (tmp % 10) + '0';
// 			tmp /= 10;
// 		}
// 		
// 	}
// }

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
