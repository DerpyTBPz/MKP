/*
 * AVRGCC4.c
 *
 * Created: 13.04.2024 9:29:10
 *  Author: student
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BTN1	0x04
#define		BTN2	0x08
#define		DIGITS	4

ISR(TIMER1_COMPA_vect);
ISR(TIMER2_COMP_vect);
ISR(ADC_vect);
ISR(INT0_vect);
ISR(INT1_vect);

void UARTSend(char x);
char UARTReceive();
void SendString(char* str);
void ReceiveString(char* str);
void Start();

void TimerInit();
void ACPInit();

void ToggleACP(int en);
void SwitchACPMode(int mode);

unsigned char DecToDigit(unsigned char Dec);
void NumToArr(int numbr);

int enACP = 0;
int modeACP = 1;

float volt = 25;
int res = 0;

int j = 0;
int arr[DIGITS];
char string[128];
char text;

int trigger = 0;

char type = '\0';
char resc[6];

int numOfSamp = 0;
int treshold = 0;
char acpMode = '0';
char workingMode = '0';
char command = '0';


int main(void)
{
	DDRA = 0xF0;
	DDRC = 0xFF;
	DDRD |= BTN1 | BTN2 | RED | GREEN;

 	DDRD |= 0xFF;
 	MCUCR = 0x0F;
 	GICR = 0xC0;
	
	PORTA = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	
	UCSRA = 0x00;
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UBRRL = 25;  
		
// 	TimerInit();
 	ACPInit();

	sei();
	
	while(1)
	{	
		type = UARTReceive();
		if (type == 'n') // NUMBER OF SAMPLES (1 - 9999)
		{								
			for (int i = 0; i < 4; i++)
			{					
				resc[i] = UARTReceive();
			}
			numOfSamp = atoi(resc);	
		}
		else if (type == 't') // THESHOLD (1 - 1022)
		{
			for (int i = 0; i < 4; i++)
			{					
				resc[i] = UARTReceive();
			}
			treshold = atoi(resc);
		}
		else if (type == 'a') // ACP MODE (1 - 8BIT; 2 - 10BIT)
		{
			acpMode = UARTReceive();
		}
		else if (type == 'w') // WORKING MODE (1 - HIGHER THEN TRESHOLD; 2 - ALL; 3 - LOWER THEN TRESHOLD)
		{
			workingMode = UARTReceive();
		}
		else if (type == 'c') // COMMAND (1 - START; 2 - PAUSE; 3 - STOP)
		{							
			command = UARTReceive();
			if (command == '1')
			{
				ADCSRA |= (1<<ADSC);
			}
			else if (command == '2')
			{
				//PAUSE
			}
			else if (command == '3')
			{
				int numOfSamp = 0;
				int treshold = 0;
				char acpMode = '0';
				char workingMode = '0';
				char command = '0';								
			}
		}
			
		type = '\0';
	}			
}

void Start()
{
	while (UARTReceive() != '3')
	{
		ADCSRA |= (1<<ADSC);
	}	
}

void TimerInit()
{
	MCUCR = 0x0F;
	GICR = 0xC0;
	
	//TIMER0
// 	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
// 	OCR0 = 20;
//  TIMSK |= (1 << OCIE0);

	//TIMER1
// 	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
// 	TCCR1B |= (1<<WGM12) | (1<<CS10);
// 	OCR1A = 4;
// //	TIMSK |= (1 << OCIE1A);	
// //	TIMSK |= (1 << TOIE1);
// 	TIFR |= (1 << TOV1);

	//TIMER2
// 	TCCR2 |= (1<<WGM21) | (1<<CS22) | (1<<CS21);
// 	OCR2 = 10;
// 	TIMSK |= (1 << OCIE2);
}

void ACPInit()
{
	ADMUX |= (1<<REFS0) | (1<<MUX1); 
//	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE);
	ADCSRA |= (1<<ADEN) | (1<<ADIE);
}

ISR(ADC_vect)
{	
	res = ADCL;
	res |= (ADCH << 8);
	
	if (acpMode == '1')
	{
		res /= 4;
	}	
// 	else if (acpMode == '2')
// 	{
// 		itoa(res, string, 10);
// 	}
	
	if ((workingMode == '1') && (res < treshold))
	{
		itoa(treshold, string, 10);
	}
	else if ((workingMode == '1') && (res > treshold))
	{
		itoa(res, string, 10);
	}
	else if ((workingMode == '3') && (res < treshold))
	{
		itoa(res, string, 10);
	}
	else if ((workingMode == '3') && (res > treshold))
	{
		itoa(treshold, string, 10);
	}
	else 
	{
		itoa(res, string, 10);
	}
	
	SendString(string);
}

ISR(INT0_vect) // RESET
{
	int numOfSamp = 0;
	int treshold = 0;
	char acpMode = '0';
	char workingMode = '0';
	char command = '0';
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

void NumToArr(int numbr)
{	
	for (int k = 0; k < DIGITS; k++)
	{		
		arr[k] = numbr % 10;
		numbr /= 10;
	}
}

void ReceiveString(char* str)
{
	char ret[64];
	int i = 0;
	while(1)
	{
		char tmp = UARTReceive();
		if (tmp != '\0')
		{
			ret[i] = tmp;
			i++;
		}
		else 
		{
			break;
		}
	}
	str = *ret;
}

void ToggleACP(int en)
{
	if (en == 0)
	{
		PORTD = RED;
	}
	else if (en == 1)
	{
		PORTD = GREEN;	
	} 
}

void SwitchACPMode(int mode)
{
	switch(mode)
	{
		case 0: 
			DDRC = 0x0;
			break;
		case 1:		
			DDRC = 0xFF;
			NumToArr(res);	
			break;			
		case 2:
			DDRC = 0xFF;
			volt = (float)((0.5 * res) / 1024) * 10000;
 			NumToArr(volt);
			break;
		default:
			DDRC = 0x0;
			break;
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