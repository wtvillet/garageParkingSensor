#ifndef ultrasonicdistancesensor_h
#define ultrasonicdistancesensor_h

#include "../commonIncludes.h"

void UDS_addInterruptTime(bool risingEdge);
void UDS_getObjectDistance(void);
bool UDS_dataReady(void);
void UDS_triggerSensor(void);

#endif
