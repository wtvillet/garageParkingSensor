#ifndef timers_h
#define timers_h

#include "../commonIncludes.h"

#define TIMER_TO_U_SECONDS         (float)1000000*64/F_CPU

void TIMERS_initTimers(void);
uint16_t getTimer1Value(void);

#endif
