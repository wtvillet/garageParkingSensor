#include "timers.h"

#define UART_TIMER_TIMEOUT_SECONDS (uint8_t)2

//https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
//OCRn =  [ (clock_speed / Prescaler_value) * Desired_time_in_Seconds ] - 1

// (16000000/1024)*1secong - 1 = 0x3D08
void TIMERS_initTimers(void)
{
    //Counter stop value
    OCR1A = TIMER1_INTERRUPT_CONFIG;

    // Mode 4, CTC on OCR1A
    TCCR1B |= (1 << WGM12);

    //Set interrupt on compare match
    TIMSK1 |= (1 << OCIE1A);

    //Config and enable Timer1. Prescaler set to 64
    TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10);
}

// Return the timer 1 value.
// Yes this is a global value but this makes the code portable to other platforms
uint16_t getTimer1Value(void)
{
    return TCNT1;
}
