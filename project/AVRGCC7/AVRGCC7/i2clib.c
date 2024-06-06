/*
 * i2clib.c
 *
 * Created: 25.05.2024 12:33:10
 *  Author: Administrator
 */ 

#include "i2clib.h"
#include "main.h"

void I2C_Init(void)
{
	TWBR = 0x03; //1MGz CPU; 25kGz I2C
}

void I2C_Start(void) 
{ 
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); 
	while(!(TWCR & (1<<TWINT))); 
} 
 
void I2C_Transmit(unsigned char data) 
{ 
	TWDR = data; 
	TWCR = (1<<TWINT) | (1<<TWEN); 
	while(!(TWCR & (1<<TWINT))); 
} 
 
void I2C_TransmitByAddr(unsigned char data, unsigned char addr)
{ 
	I2C_Start(); 
	I2C_Transmit(addr); 
	I2C_Transmit(data); 
	I2C_Stop(); 
} 

char* I2C_Read()
{
	I2C_Start();
	I2C_Stop();
	return TWDR;
}
 
void I2C_Stop(void) 
{ 
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); 
}