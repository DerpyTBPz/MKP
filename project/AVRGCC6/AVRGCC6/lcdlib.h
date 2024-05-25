/*
 * lcdlib.h
 *
 * Created: 25.05.2024 12:59:42
 *  Author: Administrator
 */ 


#ifndef LCDLIB_H_
#define LCDLIB_H_

void LCD_Init(void);
void sendHalfByte(unsigned char);
void sendByte(unsigned char, unsigned char);
void LCD_setPosition(unsigned char, unsigned char);
void LCD_sendString(char[]);
void LCD_clear(void);
void LCD_BackLight(unsigned char);

#endif /* LCDLIB_H_ */