#include "../commonIncludes.h"


ISR(USART_RX_vect)
{
	//USART Interrupt Received
}


ISR( INT0_vect )
{
    if(PIND & (1 << 2))
    {
        PORTB |= _BV(PORTB5);
        UDS_addInterruptTime(true);
    }/* Clear Timer counter */
    else
    {

        PORTB &= ~_BV(PORTB5);
        UDS_addInterruptTime(false);
    }
}