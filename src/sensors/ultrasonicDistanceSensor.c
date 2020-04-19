#include "ultrasonicDistanceSensor.h"


static uint16_t	interruptTimePushed = 0;
static uint16_t interruptTimeArray[UDS_AVERAGING_SIZE];
static uint8_t	averagingCounter = 0;
static bool 	dataReady = false;
static bool		serviceSensor = false;
static float 	distanceLpf = 0.0f;

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
		//dataReady = true;
		if(averagingCounter >= UDS_AVERAGING_SIZE)
		{
			printf("ERROR\n");
		}
		else
		{
			interruptTimeArray[averagingCounter] = interruptTimePushed;
			averagingCounter++;
		}
	}
}

// Return the status of the data to be pulled
bool UDS_dataReady(void)
{
	if(averagingCounter == UDS_AVERAGING_SIZE)
		return true;
	else
		return false;
	//return dataReady;
}

// Get the objet distance
void UDS_getObjectDistance(void)
{
	float interruptTimeAverage = 0.0f;
	for (int i = 0; i < UDS_AVERAGING_SIZE; ++i)
	{
		interruptTimeAverage = interruptTimeAverage + interruptTimeArray[i];
	}
	interruptTimeAverage = interruptTimeAverage/((float)(UDS_AVERAGING_SIZE));
	float elapsedTime_us_float = (float)(interruptTimeAverage+1)*TIMER_TO_U_SECONDS; //us
	float distance = ((float) SPEED_OF_SOUND_IN_CM_S * (float) elapsedTime_us_float)
                    / (float) 2000;
	//distanceLpf +=0.7f*(distance - distanceLpf);
	//printf("%u counts\n",interruptTimePushed);
	//printf("%f us\n",elapsedTime_us_float);
	printf("%0.2f cm\n",distance);
	// Clear the data ready flag
	//dataReady = false;
	averagingCounter = 0;
	memset(&interruptTimeArray[0],0,sizeof(uint16_t)*UDS_AVERAGING_SIZE);
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
	serviceSensor = false;
}

// Init the sensor and reset the internal variables
void UDS_initSensor(void)
{
	interruptTimePushed = 0;
	averagingCounter = 0;
	distanceLpf = 0.0f;
	serviceSensor = false;
	dataReady = false;
	memset(&interruptTimeArray[0],0,sizeof(uint16_t)*UDS_AVERAGING_SIZE);
}

// The service interval interrupt timer fired in the ISR
void UDS_serviceInterrupt(void)
{
	serviceSensor = true;
}

bool UDS_getServiceStatus(void)
{
	return serviceSensor;
}