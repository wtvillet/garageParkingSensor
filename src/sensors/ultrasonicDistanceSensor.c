#include "ultrasonicDistanceSensor.h"

static uint16_t interruptTimePushed = 0;

static bool display = false;
void UDS_addInterruptTime(bool risingEdge)
{
	if(risingEdge)
	{
		//Grab the time. Use function instead of global variable to make code portable
		interruptTimePushed = getTimer1Value();
	}
	else
	{
		//Grab the time. Use function instead of global variable to make code portable
		interruptTimePushed = getTimer1Value() - interruptTimePushed;
		display = true;
	}
}

bool UDS_dataReady(void)
{
	return display;
}

void UDS_getObjectDistance(void)
{
	float elapsedTime_us_float = (float)(interruptTimePushed+1)*TIMER_TO_U_SECONDS; //us
    float distance = ((float) SPEED_OF_SOUND_IN_CM_S * (float) elapsedTime_us_float)
                    / (float) 2000;
    printf("%u counts\n",interruptTimePushed);
    printf("%f us\n",elapsedTime_us_float);
    printf("%0.2f cm\n",distance);
    display = false;
}


void UDS_triggerSensor(void)
{
    //transmit at least 10 us trigger pulse to the HC-SR04 Trig Pin.
    PORTD |=  (1 << 3);
    _delay_us( 10 );
    PORTD &= ~(1 << 3);
}
