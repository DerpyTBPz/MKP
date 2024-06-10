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
	/*
	st_start = 0x08,
	st_restart = 0x10,
	st_sla_w_ack = 0x18,
	st_sla_w_noack = 0x20,
	st_data_w_ack = 0x28,
	st_data_w_noack = 0x30,
	st_arb_lost = 0x38,
	st_sla_r_ack = 0x40,
	st_sla_r_noack = 0x48,
	st_data_r_ack = 0x50,
	st_data_r_noack = 0x58
	*/

void I2C_Read(char *data)
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	*data = TWDR;
	while(!(TWCR & (1<<TWINT))); 	
}
 
void I2C_Stop(void) 
{ 
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); 
}