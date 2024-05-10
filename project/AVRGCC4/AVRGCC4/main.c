/*
 * AVRGCC4.c
 *
 * Created: 13.04.2024 9:29:10
 *  Author: student
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define		RED		0x20
#define		GREEN	0x80
#define		BLUE	0x10 
#define		BTN1	0x04
#define		BTN2	0x08
#define		DIGITS	4

ISR(TIMER1_COMPA_vect);
ISR(TIMER2_COMP_vect);
ISR(ADC_vect);
ISR(INT0_vect);
ISR(INT1_vect);

void TimerInit();
void ACPInit();
void ToggleACP(int en);
void SwitchACPMode(int mode);
unsigned char DecToDigit(unsigned char Dec);
void NumToArr(int numbr);

/*int num = 0;*/
int wait = 0;

int enACP = 0;
int modeACP = 0;

float volt = 0;
int res = 0;
int j = 0;
int arr[DIGITS];

int main(void)
{
	DDRA = 0xF0;
	DDRC = 0xFF;
	DDRD |= BTN1 | BTN2 | RED | GREEN;
	
	PORTA = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	
	PORTD = RED;
		
 	TimerInit();
 	ACPInit();
	
// 	ADMUX |= (1<<REFS0) | (1<<MUX1); 
// 	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE);

	sei();
	
	while(1)
	{	
//		NumToArr(res);
		
//		ToggleACP(enACP);
//		SwitchACPMode(modeACP);		
		
//  		volt = (float)((0.5 * res) / 1024) * 10000;
//   		NumToArr(volt);
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
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS10);
	OCR1A = 4;
//	TIMSK |= (1 << OCIE1A);	
//	TIMSK |= (1 << TOIE1);
	TIFR |= (1 << TOV1);
	
	//TIMER2
	TCCR2 |= (1<<WGM21) | (1<<CS22) | (1<<CS21);
	OCR2 = 10;
	TIMSK |= (1 << OCIE2);
}

void ACPInit()
{
	ADMUX |= (1<<REFS0) | (1<<MUX1); 
	ADCSRA |= (1<<ADSC) | (1<<ADIE) | (1<<ADATE);
//	SFIOR |= (1<<ADTS2) | (1<<ADTS1);
	
	//ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE);
}

ISR(ADC_vect)
{	
	if (enACP == 0)
	{
		res = 0;
		volt = 0;
	}
	else 
	{
		res = ADCL;
		res |= (ADCH << 8);
	}	
}

// ISR(TIMER1_OVF_vect)
// {
// 	if (enACP == 0)
// 	{
// 		res = 0;
// 		volt = 0;
// 	}
// 	else 
// 	{
// 		res = ADCL;
// 		res |= (ADCH << 8);
// 	}
// }

ISR(TIMER2_COMP_vect)
{	
	PORTC = 0x00;
	PORTA = 0x00;
	//DDRD = 0xB0;
	
	if (modeACP != 0)
	{
		if (modeACP == 1)
		{
			NumToArr(res);
		}
		else if (modeACP == 2)
		{
			volt = (float)((0.5 * res) / 1024) * 10000;
			NumToArr(volt);
		}
		
		PORTC = DecToDigit(arr[j]);
		PORTA = (1 << (7 - j));	
	
		if (j == 3)
		{
			PINC |= 0b10000000;	
		}	
	
		j++;
		j %= 4;
	}
	
}

ISR(INT0_vect)
{
	enACP++;
	if (enACP >= 2)
	{
		enACP = 0;
	}
	
	ToggleACP(enACP);
}

ISR(INT1_vect)
{
	modeACP++;
	if (modeACP >= 3)
	{
		modeACP = 0;
	}
}

void ToggleACP(int en)
{
	//ADCSRA ^= (1<<ADEN);
	
	if (en == 0)
	{
		PORTD = RED;
// 		res = 0;
// 		volt = 0;
		ADCSRA = (1<<ADSC) | (1<<ADIE) | (1<<ADATE);
	}
	else if (en == 1)
	{
		PORTD = GREEN;	
		ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE);
	}

// 	if (res != 0)
// 	{
// 		PORTD ^= RED;
// 		PORTD ^= GREEN;
// 	
// 		ADCSRA ^= (1<<ADEN);
// 	}
// 	else 
// 	{
// 		ADCSRA |= (1<<ADEN);	
// 	}
	
// 	PORTD ^= RED;
// 	PORTD ^= GREEN;
// 	
// 	ADCSRA ^= (1<<ADEN);		 
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
	
	if (mode == 0)
	{
		PORTC = 0x0;
	}
	else if (mode == 1)
	{
		
	}
	else if (mode == 1)
	{
		
	}
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

