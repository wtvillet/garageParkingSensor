#include "io.h"



void HARDWARE_init(void)
{
    //https://sites.google.com/site/qeewiki/books/avr-guide/external-interrupts-on-the-atmega328
    EICRA |= (1 << ISC00);      // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);       // Turns on INT0

    DDRD &= ~(1 << 2);          //Make PD2 input
    DDRD |=  (1 << 3);          //Make PD3 Output

    PORTD |= (1 << PORTD2);    // turn On the Pull-up

    //Config and enable Timer1
    TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10); 
}
