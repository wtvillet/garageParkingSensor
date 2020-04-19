#ifndef ultrasonicdistancesensor_h
#define ultrasonicdistancesensor_h

#include "../commonIncludes.h"

#define UDS_SAMPLING_INTERVAL_SECONDS   (float)0.1
#define UDS_ODR_SECONDS                 (float)0.5
#define UDS_AVERAGING_SIZE              (uint8_t) ROUND_U(UDS_ODR_SECONDS/UDS_SAMPLING_INTERVAL_SECONDS)

void UDS_interruptFired(bool risingEdge);
void UDS_getObjectDistance(void);
bool UDS_dataReady(void);
void UDS_triggerSensor(void);
void UDS_initSensor(void);
void UDS_serviceInterrupt(void);
bool UDS_getServiceStatus(void);

#endif
