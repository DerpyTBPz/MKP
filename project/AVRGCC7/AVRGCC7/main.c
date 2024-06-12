/*
 * AVRGCC7.c
 *
 * Created: 06.06.2024 8:58:40
 *  Author: Administrator
 */ 

#include "main.h"
#include "i2clib.h"
#include "uartlib.h"
#include "TWI.h"

char sendData[2] = {0x2C, 0x06};	
char comm;
int temp;
int hum;
char data[6] = {0};
char str[8];

int main(void)
{
	//I2C_Init();
	twi_init(fast);
	_delay_ms(100);
	UARTInit();
	_delay_ms(100);
	
    while(1)
    {
		comm = UARTReceive();
		if (comm == 'c')
		{
			comm = UARTReceive();
			if (comm == '1') // INIT
			{
				twi_init(fast);
			}
			else if (comm == '2')
			{
				twi_master_tx_rx(0x44, sendData, 2, data, 6);				
				temp = (data[0] * 256 + data[1]);
				itoa(temp, str, 10);
 				SendString(str);
			}
			else if (comm == '4')
			{
				twi_master_tx_rx(0x44, sendData, 2, data, 6);
				hum = (data[3] * 256 + data[4]);
				itoa(hum, str, 10);
				SendString(str);
			}
			else if (comm == '3')
			{
				twi_shut();
			}
			comm = 0;
		}
    }
}

void ReadTemp(char MSB, char LSB, char addr, char* readData)
{
	I2C_Start(); 
	I2C_Transmit(addr); 
	I2C_Transmit(MSB); 
	I2C_Transmit(LSB); 
	I2C_Stop(); 	
	_delay_ms(1);	
	I2C_Start();
	I2C_Transmit(addr); 
	I2C_Read(readData);
	I2C_Stop();
} 