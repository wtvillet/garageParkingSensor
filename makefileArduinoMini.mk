MCU=atmega328p
F_CPU=16000000UL
CC=avr-gcc
OBJCOPY=avr-objcopy

CFLAGS = -std=c99 -Wall -g -O1 -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
#Enable floating point support on stdio which is not supported by avr-gcc
CFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm

TARGET=main

SRCS  = src/main.c
SRCS += src/comms/uart.c
SRCS += src/hardware/io.c


DEPS =  src/commonIncludes.h
DEPS += src/comms/uart.h
DEPS += src/hardware/io.h

PORT=/dev/ttyUSB0

all:
		${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS} ${DEPS}
		${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
		avrdude -v -c arduino -p ${MCU} -P ${PORT} -b 57600 -U flash:w:${TARGET}.hex:i
		avr-size -C --mcu=$(MCU) $(TARGET).bin

clean:
		rm -f *.bin *.elf *.o
