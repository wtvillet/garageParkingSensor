// Intelectual property of wtvillet
// Contact at wtvillet@gmail.com

#include "commonIncludes.h"

int main()
{
    //Setup the UART comms
    USART_init();
    HARDWARE_init();
    TIMERS_initTimers();

    //Set up the interrupt vector table
    sei();

    printf("ATMEL Started up.\n");
    uint32_t counter = 0;

    while(1)
    {
        counter++;
        if (counter >= 5000000)
        {
            printf("Fire\n");
            UDS_triggerSensor();
            counter = 0;
        }

        if(UDS_dataReady())
        {
            UDS_getObjectDistance();
        }
    }
}
