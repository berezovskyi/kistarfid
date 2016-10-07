#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

extern uint8_t edge_time;

void interrupt isr(void) {
	T2CONbits.ON = true;
	edge_time = TMR2;
	PIR2bits.C1IF = false;
}

