//uartlib.h

#ifndef UARTLIB_H_
#define UARTLIB_H_

void UARTInit();
void UARTSend(char Value);
char UARTReceive();
void SendString(char* str);

#endif /* UARTLIB_H_ */