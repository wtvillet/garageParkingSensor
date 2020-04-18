#ifndef uart_h
#define uart_h

#include "../commonIncludes.h"

int USART_sendBytePrintf(char u8Data, FILE *stream);
void USART_init(void);
void USART_sendByte( unsigned char data );
void USART_sendString(char *StringPtr);
bool USART_rxDataAvailable(void);
void USART_fillRxBuffer(char newPackage);
void USART_sendByteArray( unsigned char *data, uint32_t length);
void USART_sendByteArraySigned(char *data, uint32_t length );

#endif
