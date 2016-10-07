#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

enum State {
	STATE_IDLE,
	STATE_SOF0,
	STATE_SOF1,
	STATE_BYTE0,
	STATE_BYTE1,
	STATE_BYTE2,
	STATE_BYTE3,
	STATE_DONE,
};
typedef enum State State;

void main(void) {
	State state = STATE_IDLE, state_next;
	uint8_t val = 0;
	
	// set the frequency to 4MHz
	init_oscillator();

	// set 2V fixed Vref
	init_vref();

	// set 90% scale DAC for the comparator
	init_dac();

	// enable comparator from Vref via DAC (-) to RA1
	init_comparator();
	
	// enable comparator interrupts
	enable_comparator_int();
	
	init_timer2();
	
	TRISA = 0xFE;
	
	T2CONbits.ON = false;
	TMR2 = 0x0;
	PIR1bits.TMR2IF = false;
	PIR2bits.C1IF = false;
	for(;;) {
		switch(state) {
			case STATE_IDLE:
				PORTAbits.RA0 = 0x0;
				T2CONbits.ON = false;
				if(PIR2bits.C1IF) {
					PORTAbits.RA0 = 0x1;
					TMR2 = 0x0;
					T2CONbits.ON = true;
					state = STATE_SOF0;
					PIR2bits.C1IF = false;
					state_next = STATE_IDLE;
				}	
				break;
			case STATE_SOF0:
				if(PIR1bits.TMR2IF) {
					PIR1bits.TMR2IF = false;
					PIR2bits.C1IF = false;
					
					PORTAbits.RA0 = 0x0;
					PORTAbits.RA0 = 0x1;
					PORTAbits.RA0 = 0x0;
					PORTAbits.RA0 = 0x1;
					
					state = state_next;
					state_next = STATE_IDLE;
				}
				if(PIR2bits.C1IF) {
					if(TMR2 > 80 && TMR2 < 108) {
						state_next = STATE_BYTE0;
						PORTAbits.RA0 = 0x0;
						PORTAbits.RA0 = 0x1;
						val = 0;
					} else {
						state_next = STATE_IDLE;
					}
				}
				break;
			
			case STATE_BYTE0:
			case STATE_BYTE1:
			case STATE_BYTE2:
			case STATE_BYTE3:
				if(PIR1bits.TMR2IF) {
					PIR1bits.TMR2IF = false;
					PIR2bits.C1IF = false;
					state = state_next;
					state_next = STATE_IDLE;
					PORTAbits.RA0 = 0x0;
					PORTAbits.RA0 = 0x1;
				}
				if(PIR2bits.C1IF) {
					state_next = state + 1;
					
					val >>= 2;
					
					if(TMR2 < 30) {
						val |= 0x00;
					} else if(TMR2 < 67) {
						val |= 0x40;
					} else if(TMR2 < 105) {
						val |= 0x80;
					} else {
						val |= 0xC0;
					}
				}
				break;
			
			case STATE_DONE:
				PORTAbits.RA0 = 0x1;
				PORTAbits.RA0 = 0x0;
				PORTAbits.RA0 = 0x1;
				PORTAbits.RA0 = 0x0;
				PORTAbits.RA0 = 0x1;
				PORTAbits.RA0 = 0x0;
				PORTAbits.RA0 = 0x1;
				
				state = STATE_IDLE;
				break;
		}
	}
}
