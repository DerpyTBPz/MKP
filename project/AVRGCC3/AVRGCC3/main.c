/*
 * AVRGCC3.c
 *
 * Created: 16.03.2024 10:30:05
 *  Author: student
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BUT1	0x04
#define		BUT2	0x08

void colorRGB(int R, int G, int B);
void rainbowColor(int number);
void smGradient();

int count = 0;

int main(void)
{
	
//---------------------
	//smGradient();
	buttonRainbow();
//---------------------
	
    while(1)
    {

    }
}

void smGradient()
{
	DDRD |= RED | GREEN | BLUE | BUT1 | BUT2; 
	TCCR2 |= (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<CS20);	
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS10);

	int flag_R = 1, flag_G = 1, flag_B = 0;
	int red = 254, green = 0, blue = 0;
	
	while (1)
	{		
		_delay_ms(5);
		colorRGB(red, green, blue);
		
		if (flag_R && flag_G)
		{
			red--;
			green++;
			if (red == 0)
			{
				flag_R = 0;
				flag_B = 1;
			}
		}
		else if (flag_G && flag_B)
		{
			green--;
			blue++;
			if (green == 0)
			{
				flag_G = 0;
				flag_R = 1;
			}
		}
		else if (flag_B && flag_R)
		{			
			blue--;
			red++;
			if (blue == 0)
			{
				flag_B = 0;
				flag_G = 1;
			}
		}
	}
}

void buttonRainbow()
{
	DDRD |= RED | GREEN | BLUE | BUT1 | BUT2; 
	TCCR2 |= (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<CS20);	
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS10);
	
	MCUCR = 0x0F; //0x0F 0x03
	GICR = 0xC0; //0xC0 0x40
	sei();
		
	while(1)
	{	
		rainbowColor(count);
	}
}

void colorRGB(int R, int G, int B)
{
	OCR2 = B; //RED 		
	OCR1AL = G; //GREEN
	OCR1BL = R; //BLUE
}

void rainbowColor(int number)
{
	switch (number)
	{
		case 0:
			colorRGB(255,0,0);
			break;
		case 1:
			colorRGB(255,165,0);
			break;
		case 2:
			colorRGB(255,255,0);
			break;
		case 3:
			colorRGB(0,255,0);
			break;
		case 4:
			colorRGB(0,255,255);
			break;
		case 5:
			colorRGB(0,0,255);
			break;			
		case 6:
			colorRGB(128,0,128);
			break;
		default:
			colorRGB(0,0,0);
			break;
	}
}

ISR(INT0_vect)
{
	count++;
	if (count == 7)
	{
		count = 0;
	}
}

ISR(INT1_vect)
{
	count--;
	if (count == -1)
	{
		count = 6;
	}
}


