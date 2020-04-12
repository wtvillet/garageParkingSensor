#include "io.h"

void HARDWARE_init(void)
{
	//https://sites.google.com/site/qeewiki/books/avr-guide/external-interrupts-on-the-atmega328
	EICRA |= (1 << ISC00);      				// Set INT0 to trigger on ANY logic change
	EIMSK |= (1 << INT0);       				// Turns on INT0

	DDRD &= ~(1 << UDS_ECHO_INTERRUPT_PIN);		// Make PD2 input
	DDRD |=  (1 << 3);          				// Make PD3 Output

	PORTD |= (1 << PORTD2);    					// Turn On the Pull-up

	PORTB &= ~_BV(PORTB5);     					// Clear the on board LED
}

// Toggle the on board led. Makes code more portable to do it this way
void HARDWARE_toggleOnBoardLED(bool ledOn)
{
	if(ledOn)
	{
		PORTB |= _BV(PORTB5);	// Set the on board LED
	}
	else
	{
		PORTB &= ~_BV(PORTB5);	// Clear the on board LED
	}
}

// Toggle the trigger pin. Makes code more portable to do it this way
void HARDWARE_toggleTriggerPin(bool pinHigh)
{
	if(pinHigh)
	{
		// Set the pin high
		PORTD |=  (1 << 3);
	}
	else
	{
		// Set the pin low
		PORTD &= ~(1 << 3);
	}
}