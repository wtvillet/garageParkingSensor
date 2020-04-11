#ifndef commonincludes_h
#define commonincludes_h

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


#include "comms/uart.h"

char dbgString[50];

#define SPEED_OF_SOUND_IN_CM_S (331/10)
#define TIMER_TO_U_SECONDS         (float)1000000*64/F_CPU

#endif
