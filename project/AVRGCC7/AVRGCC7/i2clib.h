/*
 * i2clib.h
 *
 * Created: 25.05.2024 12:33:19
 *  Author: Administrator
 */ 


#ifndef I2CLIB_H_
#define I2CLIB_H_

void I2C_Init(void);
void I2C_Start(void);
void I2C_Transmit(unsigned char data);
void I2C_TransmitByAddr(unsigned char data, unsigned char addr);
void I2C_Read(char *data);
void I2C_Stop(void);

#endif /* I2CLIB_H_ */