#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

#include "mod.h"
#include "crc_pic.h"
#include "cmd.h"
#include "init.h"
#include "adc.h"

enum State {
	STATE_IDLE,
	STATE_BYTE0,
	STATE_BYTE1,
	STATE_BYTE2,
	STATE_BYTE3,
	STATE_NEXT_BYTE,
	STATE_DONE,
};
typedef enum State State;

uint8_t edge_time = 0xFF;
uint8_t packet[24];
uint8_t crc_lo;
uint8_t crc_hi;
uint16_t scratch;

void main(void)
{
	static State state = STATE_IDLE;
	static uint8_t val = 0;
	static uint8_t i = 0;

	// set the frequency to 4MHz
	init_oscillator();

	TRISA = 0xDF;

	// crc_test();

	// set 2V fixed Vref
	init_vref();

	// set 90% scale DAC for the comparator
	init_dac();

	// enable comparator from Vref via DAC (-) to RA1
	init_comparator();

	// enable comparator interrupts
	enable_comparator_int();

	init_timer2();
	init_timer4();
	init_ccp();

	T2CONbits.ON = false;
	TMR2 = 0x0;
	PIR1bits.TMR2IF = false;
	PIR2bits.C1IF = false;

	PIE2bits.C1IE = true;

	INTCONbits.PEIE = true;
	INTCONbits.GIE = true;
	adc_init();


	for (;;) {
		switch (state) {
		case STATE_IDLE:
			if (PIR1bits.TMR2IF) {
				PIR1bits.TMR2IF = false;

				if (edge_time > 80 && edge_time < 108) {
					state = STATE_BYTE0;
					val = 0;
					i = 0;
				} else {
					state = STATE_IDLE;
					T2CONbits.ON = false;
					TMR2 = 0x0;
				}

				edge_time = 0xFF;
			}
			break;

		case STATE_BYTE0:
		case STATE_BYTE1:
		case STATE_BYTE2:
		case STATE_BYTE3:
			if (PIR1bits.TMR2IF) {
				PIR1bits.TMR2IF = false;
				state = state + 1;

				val >>= 2;

				if (edge_time == 0xFF) {
					state = STATE_DONE;
				}
				if (edge_time < 40) {
					val |= 0x00;
				} else if (edge_time < 80) {
					val |= 0x40;
				} else if (edge_time < 116) {
					val |= 0x80;
				} else {
					val |= 0xC0;
				}


				edge_time = 0xFF;
			}
			break;

		case STATE_NEXT_BYTE:
			packet[i++] = val;
			val = 0x0;
			state = STATE_BYTE0;
			break;

		case STATE_DONE:
			T2CONbits.ON = false;
		
			switch (packet[1]) {
				case 0x1:
					cmd_inventory();
					break;
				case 0x20:
					adc_sample(packet[10]);
					cmd_read();
					break;
				default:
					/* lol */
					break;
			}
			

			state = STATE_IDLE;
			TMR2 = 0x0;
			break;
		}
	}
}
