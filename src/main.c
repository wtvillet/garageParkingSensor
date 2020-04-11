//Intelectual property of wtvillet

#include "commonIncludes.h"


uint32_t tempVar = 0;
bool display = false;
ISR( INT0_vect )
{
    if(PIND & (1 << 2)) 
    {
        tempVar = TCNT1;    
        PORTB |= _BV(PORTB5);
    }/* Clear Timer counter */
    else
    {
        tempVar = TCNT1 - tempVar;
        TCNT1 = 0;
        display = true;
        PORTB &= ~_BV(PORTB5);
    }
}

static void hc_sr04_meas( void )
{   
    //transmit at least 10 us trigger pulse to the HC-SR04 Trig Pin.
    PORTD |=  (1 << 3);
    _delay_us( 10 );
    PORTD &= ~(1 << 3);    
}

int main()
{
    //Setup the UART comms
    USART_init();
    HARDWARE_init();

    //Set up the interrupt vector table
    sei();

    printf("ATMEL Started up.\n");
    uint32_t counter = 0;
    PORTB &= ~_BV(PORTB5);
    while(1)
    {
        counter++;
        if (counter >= 5000000)
        {
            printf("Fire\n");
            hc_sr04_meas();
            counter = 0;
            //TCNT1 = 0;
            PORTB &= ~_BV(PORTB5);
        }
        if(display)
        {
            float elapsedTime_us_float = (float)(tempVar+1)*TIMER_TO_U_SECONDS; //us
            float distance = ((float) SPEED_OF_SOUND_IN_CM_S * (float) elapsedTime_us_float)
                    / (float) 2000;
            printf("%u counts\n",tempVar);
            printf("%f us\n",elapsedTime_us_float);
            printf("%0.2f cm\n",distance);
            display = false;
        }
    }
}
