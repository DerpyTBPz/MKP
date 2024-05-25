/*
 * AVRGCC6.c
 *
 * Created: 25.05.2024 10:19:44
 *  Author: Administrator
 */ 

#include "i2clib.h"
#include "main.h"
#include "lcdlib.h"

#define		RED		0x80
#define		GREEN	0x20
#define		BLUE	0x10 
#define		BTN1	0x04
#define		BTN2	0x08

int main(void) 
{ 
	DDRC |= (1<<PC0) | (1<<PC1); 
 
	I2C_Init(); 
	_delay_ms(50); 
	LCD_Init(); 
 
	_delay_ms(1000); 
	LCD_clear(); 
	LCD_setPosition(0,0); 
	LCD_sendString("<< Codecranch >>"); 
	// sendByte(0xC0,0); 
	LCD_setPosition(1,1); 
	LCD_sendString(">>          <<"); 
	// sendByte(0x90,0); 
	LCD_setPosition(0,2); 
	LCD_sendString("Soft that works!"); 
	LCD_setPosition(1,3); 
	LCD_sendString("codecranch.com "); 
  
 while (1) { 
  // _delay_ms(5000); 
  // LCD_BackLight(0); 
  // _delay_ms(5000); 
  // LCD_BackLight(1); 
 } 
 
 return 0; 
}