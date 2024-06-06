/*
 * AVRGCC7.c
 *
 * Created: 06.06.2024 8:58:40
 *  Author: Administrator
 */ 

#include "main.h"
#include "i2clib.h"
#include "uartlib.h"

int main(void)
{
	I2C_Init();
	_delay_ms(100);
	UARTInit();
	
    while(1)
    {
		char config[2] = {0};
        config[0] = 0x2C;
		config[1] = 0x06;
		
		I2C_Transmit(config[0]);
		I2C_Transmit(config[1]);
		_delay_ms(100);
		
		char data;
		
		data = I2C_Read();
		
		UARTSend(data);
		UARTReceive();
    }
}