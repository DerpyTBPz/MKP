/*
 * AVRGCC8.c
 *
 * Created: 06.06.2024 21:24:17
 *  Author: Administrator
 */ 

#include "main.h"
#include "uartlib.h"
#include "TWI.h"

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
void CalculateTemp();	
void TempTo7Seg();
void NumToArr(int numbr);
void TempToArr(int temp);
unsigned char DecToDigit(unsigned char Dec);

mode = fast;
int j = 0;
int n = 0;
int timeArr[DIGITS];
int tempArr[DIGITS];
int HH = 11;
int MM = 59;
int SS = 50;
int time = 0;
long int temp = 270;
double cTemp;
char data[6] = {0};
char sendData[2] = {0x2C, 0x06};

char string[128];
char tmpStr[128];
int timeMode = 0;
int flag = 0;
char tmp[3];
int blink = 0;
int segMode = 0;

int main(void)
{	
	DDRA = 0xF0;
	DDRC = 0xFF;
	DDRD |= RED | GREEN | BLUE | BTN1 | BTN2;
	MCUCR = 0x0F;
	GICR = 0xC0;
	
	_delay_ms(1);
	TimerInit();
	UARTInit();
	
	sei();
	
	while(1)
	{
		if (segMode == 0)
		{
			SendTime();
		}
		else
		{	
			//TempToArr(temp);
			ltoa((long int)(cTemp), tmpStr, 10);
			TempToArr((long int)(cTemp));
			SendTemperature();
			//TempTo7Seg();					
		}
		
		if (timeMode == 1)
		{
			while(1)
			{			
				SendString("Enter hours (HH)");
				UARTSend('\r');
 				UARTSend('\n');
				tmp[0] = UARTReceive();
				tmp[1] = UARTReceive();				
				HH = atoi(tmp);				
				if (HH > 23)
				{
					SendString("Wrong hours");
					UARTSend('\r');
 					UARTSend('\n');
					break;
				}
				_delay_ms(100);
				
				SendString("Enter minutes (MM)");
				UARTSend('\r');
 				UARTSend('\n');				
				tmp[0] = UARTReceive();
				tmp[1] = UARTReceive();				
				MM = atoi(tmp);				
				if (MM > 59)
				{
					SendString("Wrong minutes");
					UARTSend('\r');
 					UARTSend('\n');
					break;
				}
				_delay_ms(100);
				
				SendString("Enter seconds (SS)");
				UARTSend('\r');
 				UARTSend('\n');				
				tmp[0] = UARTReceive();
				tmp[1] = UARTReceive();				
				SS = atoi(tmp);	
				if (SS > 59)
				{
					SendString("Wrong seconds");
					UARTSend('\r');
 					UARTSend('\n');
					break;
				}	
				_delay_ms(100);
				timeMode = 0;	
				break;
			}			
		}
	}
}

void TimerInit()
{
	//TIMER0
// 	TCCR0 |= (1 << WGM00) | (1 << CS02) | (1 << CS00);
// 	OCR0 = 5;
// 	TIMSK |= (1 << OCIE0);

 	//TIMER1	
	TCNT1 |= 0;
	OCR1A |= 15625;
	TCCR1A |= (1 << FOC1A);
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
	TIMSK |= (1 << OCIE1A);
	
	//TIMER2
	TCCR2 |= (1<<WGM21) | (1<<CS22) | (1<<CS21);
	OCR2 = 2;
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
				if (HH == 24)
				{
					HH = 0;
				}
				if (HH > 12)
				{
					blink = (HH - 12) * 2;
				}
				else if (HH == 0)
				{
					blink = 24;					
				}
				else
				{
					blink = HH * 2;
				}	
			}
		}		
		time = (HH * 100) + MM;			
		NumToArr(time);
		
		PORTC = 0x00;
		PORTA = 0x00;
		CalculateTemp();
		
// 		if (segMode == 1)
// 		{			
// 			PORTC = 0x00;
// 			PORTA = 0x00;
// 			CalculateTemp();
// 		}
	}
	
	if (blink != 0)	
	{
		PORTD ^= RED | GREEN | BLUE;
		blink--;
	}
}

ISR(TIMER2_COMP_vect)
{
	if (segMode == 0)
	{
		PORTC = 0x00;
		PORTA = 0x00;
		PORTC = DecToDigit(timeArr[j]);
		
		if ((j == 2) && ((SS % 2) == 0) && (segMode == 0))
		{			
			PORTC ^= 0b10000000;	
		}	
			
		PORTA = (1 << (7 - j));			
		j++;
		j %= 4;
	}	
	else
	{
		PORTC = 0x00;
		PORTA = 0x00;
		PORTC = DecToDigit(tempArr[j]);
		
		if (j == 3)
		{			
			PORTC |= 0b10000000;	
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

ISR(INT1_vect)
{
	segMode++;
	
	if (segMode == 1)
	{		
		//TIMSK ^= (1 << OCIE2);		
	}
	else
	{
		//TIMSK ^= (1 << OCIE2);
 		segMode = 0;
	}
}

void CalculateTemp()
{	
	TIMSK ^= (1 << OCIE2);
	
	TWBR = (mode == standard) ? 32 : 2;
	TWSR &= ~(0b11 << TWPS0); // Clearing TWSP to 0
	TWCR |= (1 << TWEN); // Enable TWI, generating the SCLK
	_delay_ms(1);
	
	twi_master_tx_rx(0x44, sendData, 2, data, 6);
	
	temp = (data[0] * 256 + data[1]);
	cTemp = ((double)(175 * temp / 65535.0) - 45) * 10;	
	
	TWBR = 0;
	TWSR = 0;
	TWCR = 0;
	
	TIMSK ^= (1 << OCIE2);
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
}

void SendTemperature()
{
	itoa(tempArr[3], string, 10);
	SendString(string);
	itoa(tempArr[2], string, 10);
	SendString(string);
	SendString(".");
	itoa(tempArr[1], string, 10);
	SendString(string);
	SendString(" C");
	
	UARTSend('\r');
 	UARTSend('\n');
}

void TempTo7Seg()
{	
	PORTC = DecToDigit(tempArr[0]);
	PORTA = (1 << 7);
	
	PORTC = DecToDigit(tempArr[1]);
	PORTA = (1 << 6);
	
	PORTC = DecToDigit(tempArr[2]);
	PORTA = (1 << 5);
	
	PORTC = DecToDigit(tempArr[3]);
	PORTA = (1 << 4);
}

void NumToArr(int numbr)
{	
	for (int k = 0; k < DIGITS; k++)
	{		
		timeArr[k] = numbr % 10;
		numbr /= 10;
	}
}

void TempToArr(int tempr)
{	
	tempArr[0] = 12;
	for (int k = 1; k < DIGITS; k++)
	{		
		tempArr[k] = tempr % 10;
		tempr /= 10;
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
		case 10:
			Digit = 0b01110111;
			break;
		case 11:
			Digit = 0b01111100;
			break;
		case 12:
			Digit = 0b01011001;
			break;
		case 13:
			Digit = 0b00111110;
			break;
		case 14:
			Digit = 0b01111001;
			break;
		case 15:
			Digit = 0b01110001;
			break;
		default:
			Digit = 0b00000000;
			break;			
 	}	
	 
	return Digit;
}
