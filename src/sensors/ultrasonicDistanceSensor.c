#include "ultrasonicDistanceSensor.h"

static uint16_t interruptTimePushed = 0;

void UDS_addInterruptTime(uint16_t interruptTime)
{
	interruptTimePushed = interruptTime;
}

void UDS_getObjectDistance(void)
{
	float elapsedTime_us_float = (float)(interruptTimePushed+1)*TIMER_TO_U_SECONDS; //us
    float distance = ((float) SPEED_OF_SOUND_IN_CM_S * (float) elapsedTime_us_float)
                    / (float) 2000;
    printf("%u counts\n",interruptTimePushed);
    printf("%f us\n",elapsedTime_us_float);
    printf("%0.2f cm\n",distance);
}
