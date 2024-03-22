/*
 * AVRGCC3.c
 *
 * Created: 16.03.2024 10:30:05
 *  Author: student
 */ 

#include <avr/io.h>
#include <avr/delay.h>

#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BUT1	0x04
#define		BUT2	0x08

int main(void)
{
	DDRD |= RED | GREEN | BLUE | BUT1 | BUT2; 
	TCCR2 |= (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<CS20);	
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS10);
	
	int flag_R = 1, flag_G = 1, flag_B = 0;
	int red = 254, green = 0, blue = 0;
	int color1 = 255, color2 = 0, flag_C = 0;
	
    while(1)
    {
		_delay_ms(5);
		OCR2 = red; //RED 		
		OCR1AL = green; //GREEN
		OCR1BL = blue; //BLUE
// 		if (flag_R == 0)
// 		{
// 			red++;
// 			if (red == 255)
// 			{
// 				flag_R = 1;				
// 			}			
// 		}
// 		else 
// 		{
// 			red--;
// 			if (red == 0)
// 			{
// 				flag_R = 0;				
// 			}
// 		}
// 		
// 		if (flag_G == 0)
// 		{
// 			green++;
// 			if (green == 255)
// 			{
// 				flag_G = 1;				
// 			}			
// 		}
// 		else 
// 		{
// 			green--;
// 			if (green == 0)
// 			{
// 				flag_G = 0;				
// 			}
// 		}
// 		
// 		if (flag_B == 0)
// 		{
// 			blue++;
// 			if (blue == 255)
// 			{
// 				flag_B = 1;				
// 			}			
// 		}
// 		else 
// 		{
// 			blue--;
// 			if (blue == 0)
// 			{
// 				flag_B = 0;				
// 			}
// 		}
		
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
		
// 		OCR2 = 0; //RED 		
// 		OCR1AL = 200; //GREEN
// 		OCR1BL = 0; //BLUE
		
        
    }
}