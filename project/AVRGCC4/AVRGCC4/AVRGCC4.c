/*
 * AVRGCC4.c
 *
 * Created: 13.04.2024 9:29:10
 *  Author: student
 */ 
// 
// #include <avr/io.h>
// #include <avr/interrupt.h>
// 
// #define DIGITS 4
// 
// ISR(ADC_vect);
// ISR(TIMER0_COMP_vect);
// unsigned char DecToDigit(unsigned char Dec);
// void NumToArr(int num);
// 
// int arr[DIGITS];
// int j = 0;
// int res = 0;
// 
// 
// 
// int main(void)
// {
// 	DDRA = 0xF0;
// 	DDRC = 0xFF;	
// 	MCUCR = 0x0F;
// 	GICR = 0xC0;
// 		
// 	PORTA = 0x00;
// 	PORTC = 0x00;
// 	
// 	ADMUX |= (1<<REFS0) | (1<<MUX1); 
// 	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE);
// 
// 	//TIMER1
// 	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
// 	TCCR1B |= (1<<WGM12) | (1<<CS10);
// 	OCR1A = 10;
// 	TIMSK |= (1 << OCIE1A);	
// 	
// 	PORTD = 0x0;
// 	sei();
// 	
// 	
// 	while(1)
// 	{
// 		NumToArr(8888);
// 		//NumToArr8(num);
// 		//NumToArr16(num);
// 	}	
// 	
// 	
// }
// 
// ISR(ADC_vect)
// {
// 	res = ADCL;
// 	res |= (ADCH << 8);
// }
// 
// ISR(TIMER0_COMP_vect)
// {
// 	PORTC = 0x00;
// 	PORTA = 0x00;
// 	
// 	PORTC = DecToDigit(arr[j]);
// 	
// 	PORTA = (1 << (7 - j));
// 	j++;
// 	j %= 4;
// }
// 
// ISR(TIMER1_COMPA_vect)
// {	
// 	PORTC = 0x00;
// 	PORTA = 0x00;
// 	
// 	//PORTC = DecToDigit(arr[j]);	
// 	PORTC = DecToDigit(arr[j]);
// 	//PORTC = DecToDigit(arr16[j]);
// 	
// 	PORTA = (1 << (7 - j));
// 	j++;
// 	j %= 4;
// }
// 
// unsigned char DecToDigit(unsigned char Dec)
// {	
// 	unsigned char Digit;
// 	
// 	switch(Dec)
// 	{
// 		case 0:
// 			Digit = 0b01011111;				
// 			break;
// 		case 1:
// 			Digit = 0b00000110;					
// 			break;
// 		case 2:
// 			Digit = 0b00111011;					
// 			break;
// 		case 3:
// 			Digit = 0b00101111;
// 			break;
// 		case 4:
// 			Digit = 0b01100110;
// 			break;
// 		case 5:
// 			Digit = 0b01101101;
// 			break;
// 		case 6:
// 			Digit = 0b01111101;
// 			break;
// 		case 7:
// 			Digit = 0b00000111;
// 			break;
// 		case 8:
// 			Digit = 0b01111111;
// 			break;		
// 		case 9:
// 			Digit = 0b01101111;
// 			break;
// 		default:
// 			Digit = 0b00000000;
// 			break;			
//  	}	
// }	 
// 
// void NumToArr(int num)
// {	
// 	for (int k = 0; k < DIGITS; k++)
// 	{		
// 		arr[k] = num % 10;
// 		num /= 10;
// 	}
// }


//----------------------


/*
 * AVRGCC.c
 *
 * Created: 02.03.2024 10:04:05
 *  Author: student
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define		BTN1	0x04
#define		BTN2	0x08
#define		DIGITS	4


ISR(TIMER1_COMPA_vect);
ISR(ADC_vect);
ISR(INT0_vect);

void task4();

unsigned char DecToDigit(unsigned char Dec);
void NumToArr(int num);

/*int num = 0;*/
int wait = 0;

int flag0 = 0;
int flag1 = 0;

int tmp = 0;
float volt = 0;
int res = 0;
int j = 0;
int b = 0;
int arr[DIGITS];

int main(void)
{
	DDRA = 0xF0;
	DDRC = 0xFF;	
	DDRD |= BTN1;
	MCUCR = 0x0F;
	GICR = 0xC0;
		
	PORTA = 0x00;
	PORTC = 0x00;
	PORTD = 0x0;
	
// 	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
// 	OCR0 = 20;
//  	TIMSK |= (1 << OCIE0);
	
// 	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
// 	TCCR1B |= (1<<WGM12) | (1<<CS10);
// 	OCR1A = 10;
// 	TIMSK |= (1 << OCIE1A);	
	
	TCCR2 |= (1<<WGM21) | (1<<CS22) | (1<<CS21);
	OCR2 = 10;
	TIMSK |= (1 << OCIE2);
	
	ADMUX |= (1<<REFS0) | (1<<MUX1); 
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE);

	//TIMER1
	sei();
	
	while(1)
	{	
// 		tmp++;
		volt = (float)((0.5 * res) / 1024) * 10000;
 		NumToArr(volt);
		
	}		

}


// void task4()
// {
// 	DDRA = 0xF0;
// 	DDRC = 0xFF;
// 
// 	MCUCR = 0x0F;
// 	GICR = 0xC0;
// 		
// 	PORTA = 0x00;
// 	PORTC = 0x00;
// 	
// 	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
// 	OCR0 = 20;
// 	TIMSK |= (1 << OCIE0);
// 	
// // 	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
// // 	TCCR1B |= (1<<WGM12) | (1<<CS10);
// // 	OCR1A = 10;
// // 	TIMSK |= (1 << OCIE1A);	
// 	
// 	ADMUX |= (1<<REFS0) | (1<<MUX1); 
// 	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE);
// 	
// 	PORTD = 0x0;
// 	sei();
// 	
// 	while(1)
// 	{	
// 		NumToArr(res);
// 	}		
// 	
// }

ISR(ADC_vect)
{
	res = ADCL;
	res |= (ADCH << 8);
	//NumToArr(res);
	
}

ISR(TIMER2_COMP_vect)
{	
	PORTC = 0x00;
	PORTA = 0x00;
	DDRD = 0xB0;
	
	PORTC = DecToDigit(arr[j]);
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

// void ResToVolt(int numbr)
// {
// 	voit = ((5 * res) / 1024) * 1000;	
// }

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


