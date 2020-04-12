#include "ultrasonicDistanceSensor.h"

static uint16_t interruptTimePushed = 0;
static bool dataReady = false;

// Event is pushed from the ISR
// true = rising edge trigger
// false = falling edge trigger
void UDS_interruptFired(bool risingEdge)
{
	if(risingEdge)
	{
		// Grab the rising edge time. Use function instead of global variable to make code portable
		interruptTimePushed = getTimer1Value();
	}
	else
	{
		// Grab the falling edge time. Use function instead of global variable to make code portable
		interruptTimePushed = getTimer1Value() - interruptTimePushed;
		// Data is ready to be processed
		dataReady = true;
	}
}

// Return the status of the data to be pulled
bool UDS_dataReady(void)
{
	return dataReady;
}

// Get the objet distance
void UDS_getObjectDistance(void)
{
	float elapsedTime_us_float = (float)(interruptTimePushed+1)*TIMER_TO_U_SECONDS; //us
	float distance = ((float) SPEED_OF_SOUND_IN_CM_S * (float) elapsedTime_us_float)
                    / (float) 2000;
	printf("%u counts\n",interruptTimePushed);
	printf("%f us\n",elapsedTime_us_float);
	printf("%0.2f cm\n",distance);
	dataReady = false;
}

// Trigger the Trig pin of the sensor
void UDS_triggerSensor(void)
{
	// Set the trigger pin high
	HARDWARE_toggleTriggerPin(true);
	// Transmit at least 10 us trigger pulse to the HC-SR04 Trig Pin.
	_delay_us( 10 );
	// Set the trigger pin low
	HARDWARE_toggleTriggerPin(false);
}

// Init the sensor and reset the internal variables
void UDS_initSensor(void)
{
	interruptTimePushed = 0;
	dataReady = false;
}
