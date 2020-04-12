#include "../commonIncludes.h"


ISR(USART_RX_vect)
{
	//USART Interrupt Received
}

ISR( INT0_vect )
{
	if(PIND & (1 << 2))
	{
		HARDWARE_toggleOnBoardLED(true);
		UDS_addInterruptTime(true);
	}
	else
	{
		HARDWARE_toggleOnBoardLED(false);
		UDS_addInterruptTime(false);
	}
}
