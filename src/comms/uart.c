#include "uart.h"
#include "communicationProtocol.h"

/* UART SERIAL DEFINES */
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define TX_BUFFER_SIZE  20
#define RX_BUFFER_SIZE  20

//set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(USART_sendBytePrintf, NULL, _FDEV_SETUP_WRITE);

/****************************************************************************
    Bit and byte definitions
****************************************************************************/

/* SETUP UART */
static void USART_setup( unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	/*Enable receiver and transmitter enable interrupt on RX*/
	UCSR0B = (1<<RXEN0) | (1<<RXCIE0) | (1<<TXEN0);

	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


int USART_sendBytePrintf(char u8Data, FILE *stream)
{
	if(u8Data == '\n')
	{
		USART_sendBytePrintf('\r', stream);
	}

	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0))){};
	// Transmit data
	UDR0 = u8Data;
	return 0;
}

/* Simple methods to make UART read and transmit more readble*/
void USART_sendByte( unsigned char data )
{
	//Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void USART_sendByteArray( unsigned char *data, uint32_t length )
{
	for (uint32_t counter = 0 ;counter < length; counter++)
	{
		//Wait for empty transmit buffer
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = data[counter];
	}
}

void USART_sendByteArraySigned(char *data, uint32_t length )
{
	for (uint32_t counter = 0 ;counter < length; counter++)
	{
		//Wait for empty transmit buffer
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = data[counter];
	}
}

void USART_sendString(char *StringPtr)
{
	uint32_t lengthCounter = 0;
	while(StringPtr[lengthCounter] != 0x00)
	{
		lengthCounter++;
	}
	USART_sendByteArraySigned(&StringPtr[0], lengthCounter);
}

void USART_init(void)
{
	USART_setup(MYUBRR);

	//assign our stream to standart I/O streams
	stdout=&usart0_str;
}