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
ISR(INT0_vect);
ISR(INT1_vect);

void task1();
void task2();
void task3();
void task4();
void task_tst();

unsigned char DecToDigit(unsigned char Dec);
void NumToArr(int num);
void NumToArr8(int num);
void NumToArr16(int num);

int num = 0;
int wait = 0;

int flag0 = 0;
int flag1 = 0;

int res = 0;
int j = 0;
int b = 0;
int arr[DIGITS];
int arr8[DIGITS] = {0, 0, 0, 0};
int arr16[DIGITS] = {0, 0, 0, 0};

int main(void)
{
	
//	task2();
// 	task3();
	task4();
	
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

//  switch(Dec)
// 	{
// 		case 0:
// 			Digit = 0b00111111;				
// 			break;
// 		case 1:
// 			Digit = 0b00000110;					
// 			break;
// 		case 2:
// 			Digit = 0b01011011;					
// 			break;
// 		case 3:
// 			Digit = 0b01001111;
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
// 		case 10:
// 			Digit = 0b01110111;
// 			break;
// 		case 11:
// 			Digit = 0b01111100;
// 			break;
// 		case 12:
// 			Digit = 0b00111001;
// 			break;
// 		case 13:
// 			Digit = 0b01011110;
// 			break;
// 		case 14:
// 			Digit = 0b01111001;
// 			break;
// 		case 15:
// 			Digit = 0b01110001;
// 			break;
// 			
// 		default:
// 			Digit = 0b00000000;
// 			break;			
//  	}	


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
	DDRD |= BTN1 | BTN2;
	MCUCR = 0x0F;
	GICR = 0xC0;
		
	PORTA = 0x00;
	PORTC = 0x00;
	
	
	//TIMER0
// 	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
// 	OCR0 = 20;
// 	TIMSK |= (1 << OCIE0);
	
	//TIMER1
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS10);
	OCR1A = 10;
	TIMSK |= (1 << OCIE1A);	
	
	PORTD = 0x0;
	sei();
	
	
	
	while(1)
	{
		//NumToArr(num);
		NumToArr8(num);
		//NumToArr16(num);
		
		if ((PIND & BTN1) || (PIND & BTN2))
		{			
			wait++;
		}
		else
		{			
			wait = 0;
		}
		
		if (wait >= 50)
		{
			num = 0;
		}		
		
		flag0 = 0;
		flag1 = 0;
	}	
	
}

void task_tst()
{
	DDRA = 0xF0;
	DDRC = 0xFF;
	DDRD |= BTN1 | BTN2;
	MCUCR = 0x0F;
	GICR = 0xC0;
		
	PORTA = 0x00;
	PORTC = 0x00;
	
	
	//TIMER0
// 	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
// 	OCR0 = 20;
// 	TIMSK |= (1 << OCIE0);
	
	//TIMER1
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS10);
	OCR1A = 10;
	TIMSK |= (1 << OCIE1A);	
	
	PORTD = 0x0;
	sei();
	
	
	
	while(1)
	{
		//NumToArr(num);
		NumToArr8(res);
		//NumToArr16(num);
		
		
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

ISR(TIMER1_COMPA_vect)
{	
	PORTC = 0x00;
	PORTA = 0x00;
	
	//PORTC = DecToDigit(arr[j]);	
	PORTC = DecToDigit(arr8[j]);
	//PORTC = DecToDigit(arr16[j]);
	
	PORTA = (1 << (7 - j));
	j++;
	j %= 4;
}

ISR(INT0_vect)
{	
	if (flag0 > 0)
	{
		
	}
	else 
	{
		num++;		
	}
	flag0++;	
}

ISR(INT1_vect)
{	
	if (flag1 > 0)
	{
		
	}
	else 
	{
		if (num != 0)
		{
			num--;
		}
	}
	
	flag1++;		
}

void NumToArr(int num)
{	
	for (int k = 0; k < DIGITS; k++)
	{		
		arr[k] = num % 10;
		num /= 10;
	}
}

void NumToArr8(int num)
{	
	for (int k = 0; k < DIGITS; k++)
	{
		arr8[k] = num % 8;
		num /= 8;
	}
}

void NumToArr16(int num)
{		
	for (int k = 0; k < DIGITS; k++)
	{
		arr16[k] = num % 16;
		num /= 16;
	}
}

