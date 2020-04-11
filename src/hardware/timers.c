#include "timers.h"

#define UART_TIMER_TIMEOUT_SECONDS (uint8_t)2
#define TIMER_TO_U_SECONDS         (float)1000000*64/F_CPU

//https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
//OCRn =  [ (clock_speed / Prescaler_value) * Desired_time_in_Seconds ] - 1

// (16000000/1024)*1secong - 1 = 0x3D08
static void TIMERS_startOneSecondTimer(void)
{
    //Counter stop value
    OCR1A = 0x3D08;

    // Mode 4, CTC on OCR1A
    TCCR1B |= (1 << WGM12);

    //Set interrupt on compare match
    TIMSK1 |= (1 << OCIE1A);

    // set prescaler to 1024 and start the timer
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

void TIMERS_initTimers(void)
{
    //Config and enable Timer1
    TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10);
}
