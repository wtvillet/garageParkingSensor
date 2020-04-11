//Intelectual property of wtvillet

#include "commonIncludes.h"


static void sensorSetup(void)
{
    //https://sites.google.com/site/qeewiki/books/avr-guide/external-interrupts-on-the-atmega328
    EICRA |= (1 << ISC00);      // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);       // Turns on INT0

    //Config and enable Timer1
    TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10); 

    DDRD &= ~(1 << 2);          //Make PD2 input
    DDRD |=  (1 << 3);          //Make PD3 Output

    PORTD |= (1 << PORTD2);    // turn On the Pull-up
}
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
    sensorSetup();

    //Set up the interrupt vector table
    sei();


    USART_sendString("ATMEL Started up.\n");
    uint32_t counter = 0;
    PORTB &= ~_BV(PORTB5);
    while(1)
    {
        counter++;
        if (counter >= 5000000)
        {
            USART_sendString("Fire\n");
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
            sprintf(dbgString,"%u counts\n",tempVar);
            USART_sendString(dbgString);
            sprintf(dbgString,"%f us\n",elapsedTime_us_float);
            USART_sendString(dbgString);
            sprintf(dbgString,"%0.2f cm\n",distance);
            USART_sendString(dbgString);
            display = false;
        }
    }
}
