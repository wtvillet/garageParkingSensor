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
#include "hardware/io.h"
#include "hardware/timers.h"
#include "sensors/ultrasonicDistanceSensor.h"

#define SPEED_OF_SOUND_IN_CM_S		(float)(331/10.0f)
#define ROUND_U(x)      			(uint16_t)((x) + 0.5f)

#endif
