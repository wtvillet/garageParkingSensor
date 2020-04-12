#ifndef io_h
#define io_h

#include "../commonIncludes.h"

#define UDS_ECHO_INTERRUPT_PIN	(uint8_t) 2
#define UDS_TRIGGER_PIN			(uint8_t) 3

void HARDWARE_init(void);
void HARDWARE_toggleOnBoardLED(bool ledOn);
void HARDWARE_toggleTriggerPin(bool pinHigh);

#endif
