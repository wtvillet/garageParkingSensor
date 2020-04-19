#ifndef timers_h
#define timers_h

#include "../commonIncludes.h"

#define TIMER_TO_U_SECONDS			(float)1000000*64/F_CPU
#define	TIMER1_INTERRUPT_CONFIG		(uint16_t)((UDS_SAMPLING_INTERVA_SECONDS*((float)F_CPU)/ (64.0f) )-1)

void TIMERS_initTimers(void);
uint16_t getTimer1Value(void);

#endif
