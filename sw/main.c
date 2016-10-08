#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

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

void main(void) {
	static State state = STATE_IDLE;
	static uint8_t val = 0;
	static uint8_t i = 0;
	
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
	
	PIE2bits.C1IE = true;
	
	INTCONbits.PEIE = true;
	INTCONbits.GIE = true;
	
	for(;;) {
		switch(state) {
			case STATE_IDLE:	
				if(PIR1bits.TMR2IF) {
					PIR1bits.TMR2IF = false;
					
					if(edge_time > 80 && edge_time < 108) {
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
				if(PIR1bits.TMR2IF) {
					PIR1bits.TMR2IF = false;
					state = state + 1;
					
					val >>= 2;
					
					if(edge_time == 0xFF) {
						state = STATE_DONE;
					} if(edge_time < 40) {
						val |= 0x00;
					} else if(edge_time < 80) {
						val |= 0x40;
					} else if(edge_time < 116) {
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
				for(uint8_t j = 0; j <= i; j++) {
					uint8_t k, l;
					for(k = 0; k < 8; k++) {
						PORTAbits.RA0 = (packet[j] >> (7 - k)) ^ 0x1;
						for(l = 0; l < 2; l++);
						PORTAbits.RA0 = (packet[j] >> (7 - k)) ^ 0x0;
						for(l = 0; l < 2; l++);
					}
					PORTAbits.RA0 = false;
					for(k = 0; k < 20; k++);
				}
				
				state = STATE_IDLE;
				TMR2 = 0x0;
				break;
		}
	}
}
