/*
 * AVRGCC6.c
 *
 * Created: 25.05.2024 10:19:44
 *  Author: Administrator
 */ 

#include "i2clib.h"
#include "main.h"
#include "lcdlib.h"

void ColorToLCD();
void UARTtoLCD();
void Test();

void colorRGB(int R, int G, int B);
void color(int num);
ISR(INT0_vect);
ISR(INT1_vect);

#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BTN1	0x04
#define		BTN2	0x08

int count = 0;
int i = 0;
int flag = 0;
char string[128];
char empty[128];
char txt = 'a';

int main(void) 
{ 
//----------------------	
//	ColorToLCD();
	UARTtoLCD();
//----------------------
	
//	LCD_clear();
 
// 	_delay_ms(1000); 
// 	LCD_clear(); 
// 	LCD_setPosition(0,0);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		string[i] = UARTReceive();
// 	} 
// 		
//  	LCD_sendString(string); 
// 	// sendByte(0xC0,0); 
// 	LCD_setPosition(1,1); 
// 	LCD_sendString("bebebe"); 
// 	// sendByte(0x90,0); 
// 	LCD_setPosition(0,2); 
// 	LCD_sendString("Soft that works!"); 
// 	LCD_setPosition(1,3); 
// 	LCD_sendString("codecranch.com "); 
  
	while (1) 
	{ 
		//Test();
	} 
 
	return 0; 
}

void ColorToLCD()
{
	DDRD |= RED | GREEN | BLUE | BTN1 | BTN2;
	TCCR2 |= (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<CS20);	
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS10); 
	
	DDRC |= (1<<PC0) | (1<<PC1);
	I2C_Init(); 
	_delay_ms(50); 
	LCD_Init();
	
	UARTInit();
	
	LCD_clear();
		
	MCUCR = 0x0F;
	GICR = 0xC0; 
	sei();
	
	while (1)
	{
		
	}
}

void UARTtoLCD()
{
	DDRD |= 0xFF;
	DDRC |= (1<<PC0) | (1<<PC1);
	MCUCR = 0x0F;
	GICR = 0xC0;
	
	sei();
	
	I2C_Init(); 
	_delay_ms(250); 
	LCD_Init();
	UARTInit();
	_delay_ms(250); 
	
	LCD_clear();
	
// 	txt = UARTReceive();
// 	for (int i = 0; i < 5; i++)
// 	{
// 		string[i] = txt;
// 	}
//	LCD_sendString(string);
	
	while (1)
	{	
// /*		char string[128];*/
		while (1)
		{
			txt = UARTReceive();
			if (txt == '\r')
			{
				txt = 0;	
				SendString(string);	
				LCD_sendString(string);
				for (int j = 0; j < i; j++)
				{
					string[j] = '\0';
				}
				i = 0;
				break;
			}
			else
			{
				string[i] = txt;
				i++;
				txt = 0;
			}					
			PORTD ^= RED;		
			_delay_ms(10);
			PORTD ^= RED;
		}

		UARTSend(UARTReceive());
		
// 		PORTD ^= BLUE;
// 		_delay_ms(10);
// 		PORTD ^= BLUE;
// 		txt = UARTReceive();
// 		count++;
// 		UARTSend(txt);
// 		LCD_sendString("bababa");
		
		
		
// 		while (txt != '\0')
// 		{
// 			txt = UARTReceive();
// 			string[count] = txt;
// 			count++;
// 		}
// 		txt = 'a';
// 		LCD_setPosition(0,0);
// 		LCD_sendString(string);
		
// 		txt = UARTReceive();
// 		count++;
// 		if ((count == 15) && (flag != 1))
// 		{
// 			count = 0;
// 			flag = 1;
// 			sendByte(txt, 1);
// 		}
// 		else if ((count == 15) && (flag = 1))
// 		{
// 				LCD_clear();
// 				flag = 0;
// 				count = 0;
// 				sendByte(txt, 1);
// 			}
 		}
	
}

void Test()
{
	LCD_setPosition(0,0);
	//LCD_sendString(UARTReceive(), 1);
}

void colorRGB(int R, int G, int B)
{
	OCR2 = R; //RED 		
	OCR1AL = G; //GREEN
	OCR1BL = B; //BLUE
// 
// 	OCR2 = G; //RED 		
// 	OCR1AL = R; //GREEN
// 	OCR1BL = B; //BLUE

}

// ISR(INT0_vect)
// {
// 	count++;
// 	if (count >= 8)
// 	{
// 		count = 1;
// 	}
// 	LCD_clear();
// 	color(count);
// }
// 
// ISR(INT1_vect)
// {
// 	count--;
// 	if (count <= 0)
// 	{
// 		count = 7;
// 	}
// 	LCD_clear();
// 	color(count);
// }

// void color(int num)
// {
// 	switch (num)
// 		{
// 			case 1:
// 				colorRGB(255,0,0);				
// 				LCD_setPosition(0,0);
// 				LCD_sendString("(255, 0, 0)");
// 				LCD_setPosition(0,1);
// 				LCD_sendString("Red");
// 				break;
// 			case 2:
// 				colorRGB(255,165,0);				
// 				LCD_setPosition(0,0);
// 				LCD_sendString("(255, 165, 0)");
// 				LCD_setPosition(0,1);
// 				LCD_sendString("Orange");
// 				break;
// 			case 3:
// 				colorRGB(255,255,0);				
// 				LCD_setPosition(0,0);
// 				LCD_sendString("(255, 255, 0)");
// 				LCD_setPosition(0,1);
// 				LCD_sendString("Yellow");
// 				break;
// 			case 4:
// 				colorRGB(0,255,0);				
// 				LCD_setPosition(0,0);
// 				LCD_sendString("(0, 255, 0)");
// 				LCD_setPosition(0,1);
// 				LCD_sendString("Green");
// 				break;
// 			case 5:
// 				colorRGB(0,255,255);				
// 				LCD_setPosition(0,0);
// 				LCD_sendString("(0, 255, 255)");
// 				LCD_setPosition(0,1);
// 				LCD_sendString("Cyan");
// 				break;
// 			case 6:
// 				colorRGB(0,0,255);				
// 				LCD_setPosition(0,0);
// 				LCD_sendString("(0, 0, 255)");
// 				LCD_setPosition(0,1);
// 				LCD_sendString("Blue");
// 				break;			
// 			case 7:
// 				colorRGB(128,0,128);				
// 				LCD_setPosition(0,0);
// 				LCD_sendString("(128, 0, 128)");
// 				LCD_setPosition(0,1);
// 				LCD_sendString("Violet");
// 				break;
// 			default:
// 				colorRGB(0,0,0);
// 				break;
// 		}
// }

