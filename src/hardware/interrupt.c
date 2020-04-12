#include "../commonIncludes.h"

// USART interrupt
ISR(USART_RX_vect)
{
	//USART Interrupt Received
}

// Interrupt 0
ISR( INT0_vect )
{
	// Check if interrupt triggered is high
	if(PIND & (1 << 2))
	{
		// Polarity is high
		// Toggle LED
		HARDWARE_toggleOnBoardLED(true);
		// Push edge polarity to the UDS
		UDS_interruptFired(true);
	}
	else
	{	//Polarity is low
		// Toggle LED
		HARDWARE_toggleOnBoardLED(false);
		// Push edge polarity to the UDS
		UDS_interruptFired(false);
	}
}
