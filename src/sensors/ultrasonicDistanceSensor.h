#ifndef ultrasonicdistancesensor_h
#define ultrasonicdistancesensor_h

#include "../commonIncludes.h"

void UDS_interruptFired(bool risingEdge);
void UDS_getObjectDistance(void);
bool UDS_dataReady(void);
void UDS_triggerSensor(void);
void UDS_initSensor(void);
void UDS_serviceInterrupt(void);
bool UDS_getServiceStatus(void);

#endif
