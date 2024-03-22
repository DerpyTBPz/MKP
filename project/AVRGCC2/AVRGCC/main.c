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


ISR(TIMER0_COMP_vect);

void task1();
void task2();
void task3();

unsigned char DecToDigit(unsigned char Dec);
void NumToArr(int num);

int j = 0;
int arr[DIGITS];

int main(void)
{
	
	task2();
// 	task3();
//  	DDRA = 0xF0;
//  	DDRC = 0xFF;
//  	DDRD |= BTN1 | BTN2;
//  	PORTA = 0x40;	
//  	
//  	unsigned char i = 0;
//  	
//  	PORTC = DecToDigit(0);
//  	
//  	//PORTC = 0b000101111;
//  	
//  	
//  /*	char num = DecToDigit(1);*/
//  
//  	
//  	while(1)
//      {
//  		char d = DecToDigit(i);
//  //		PORTC= 0b01100110;	
//  //		PORTC= 0b11111111;	
//    		
//  		 // task1();
//  		 
//  		 if (PIND & BTN1)
//  		 {
//  			 i++;
//  			 d = DecToDigit(i);
//  			 PORTC = d;
//  			 _delay_ms(100);
//  		 }
//  		 else if (PIND & BTN2)
//  		 {
//  			 i--;
//  			 d = DecToDigit(i);
//  			 PORTC = d;
//  			 _delay_ms(100);
//  		 }			 
//  		 	
//   		
//         //TODO:: Please write your application code 
// 		
//     }
}

unsigned char DecToDigit(unsigned char Dec)
{	
	unsigned char Digit;
	
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

switch(Dec)
	{
		case 0:
			Digit = 0b00111111;				
			break;
		case 1:
			Digit = 0b00000110;					
			break;
		case 2:
			Digit = 0b01011011;					
			break;
		case 3:
			Digit = 0b01001111;
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

/*
void task1()
{
	i++;
   	PORTC = DecToDigit(i);
 	_delay_ms(500);
}
*/

void task2()
{
	DDRA = 0xF0;
	DDRC = 0xFF;
	DDRD |= BTN1 | BTN2;
	PORTA = 0x80;	
	
	unsigned char i = 0;
	
	PORTC = DecToDigit(0);
	
	//PORTC = 0b000101111;	
	
/*	char num = DecToDigit(1);*/

	
	while(1)
    {
		char d = DecToDigit(i);
//		PORTC= 0b01100110;	
//		PORTC= 0b11111111;	
  		
		 // task1();
		 
		 if (PIND & BTN1)
		 {
			 i++;
			 d = DecToDigit(i);
			 PORTC = d;
			 _delay_ms(300);
		 }
		 else if (PIND & BTN2)
		 {
			 i--;
			 d = DecToDigit(i);
			 PORTC = d;
			 _delay_ms(300);
		 }			 
		 	
 		
        //TODO:: Please write your application code 
		
    }
}

void task3()
{
	DDRA = 0xF0;
	DDRC = 0xFF;
	PORTA = 0x00;
	PORTC = 0x00;
	
	
	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
	OCR0 = 20;
	TIMSK |= (1 << OCIE0);
	DDRD = 0xB0;
	PORTD = 0x0;
	sei();	
	
	NumToArr(1024);
	
	while(1)
	{
		
	}	
}


void task4()
{
	DDRA = 0xF0;
	DDRC = 0xFF;
	PORTA = 0x00;
	PORTC = 0x00;
	
	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
	OCR0 = 20;
	TIMSK |= (1 << OCIE0);
	DDRD = 0xB0;
	PORTD = 0x0;
	sei();	
	
	NumToArr(1024);
	
	while(1)
	{
		
	}	
	
}

ISR(TIMER0_COMP_vect)
{	
	PORTC = 0x00;
	PORTA = 0x00;
	
	PORTC = DecToDigit(arr[j]);
	
	PORTA = (1 << (7 - j));
	j++;
	j %= 4;
}

void NumToArr(int num)
{
	int k = 0;
	for (k = 0; k < DIGITS; k++)
	{
		arr[k] = num % 10;
		num /= 10;

	}
}