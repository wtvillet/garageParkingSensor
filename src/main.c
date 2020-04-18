// Intelectual property of wtvillet
// Contact at wtvillet@gmail.com

#include "commonIncludes.h"

int main()
{
    // Setup the UART comms
    USART_init();
    // Set up the hardware pins
    HARDWARE_init();
    // Set up the timers
    TIMERS_initTimers();
    // Set up the ultrasonice distance sensor (UDS)
    UDS_initSensor();

    // Set up the interrupt vector table
    sei();

    printf("ATMEL Started up.\n");
    uint32_t counter = 0;

    while(1)
    {
        counter++;
        if(UDS_getServiceStatus())
        {
            //printf("Fire\n");
            UDS_triggerSensor();
            counter = 0;
        }

        // Check if interrupts fired in ISR
        if(UDS_dataReady())
        {
            // Process interrupt data and get object distance
            UDS_getObjectDistance();
        }
    }
}
