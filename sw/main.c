#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

#define MOD_BIT() do { \
		if(byte & 0x1) \
			mod_1(); \
		else \
			mod_0(); \
		byte >>= 1; \
	} while(false)

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

void mod_start() {
	OSCTUNE = -32;
	
	TMR4 = 0;
	CCPR2L = 7;
	CCP2CONbits.EN = true;
	T1CONbits.TMR1ON = true;
	
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	
	CCPR2L = 8;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	
	T1CONbits.TMR1ON = false;
	TMR0 = 0;
	T1CONbits.TMR1ON = true;
	
	CCPR2L = 7;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	
	CCPR2L = 8;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	
	CCP2CONbits.EN = false;
	T1CONbits.TMR1ON = false;
	TMR1 = 0;
}

void mod_end() {
	TMR4 = 0;
	CCP2CONbits.EN = true;
	T1CONbits.TMR1ON = true;
	
	CCPR2L = 8;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	
	CCPR2L = 7;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	
	CCPR2L = 8;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	
	CCPR2L = 7;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	
	CCP2CONbits.EN = false;
	T1CONbits.TMR1ON = false;
	TMR1 = 0;
	
	OSCTUNE = 0;
}

void mod_1() {
	TMR4 = 0;
	CCPR2L = 7;
	CCP2CONbits.EN = true;
	T1CONbits.TMR1ON = true;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	CCPR2L = 8;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	CCP2CONbits.EN = false;
	T1CONbits.TMR1ON = false;
	TMR1 = 0;
}

void mod_0() {
	TMR4 = 0;
	CCPR2L = 8;
	CCP2CONbits.EN = true;
	T1CONbits.TMR1ON = true;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	CCPR2L = 7;
	T4CONbits.ON = true;
	while(T4CONbits.ON);
	CCP2CONbits.EN = false;
	T1CONbits.TMR1ON = false;
	TMR1 = 0;
}

void mod_byte(uint8_t byte) {
	MOD_BIT();
	MOD_BIT();
	MOD_BIT();
	MOD_BIT();
	
	MOD_BIT();
	MOD_BIT();
	MOD_BIT();
	MOD_BIT();
}

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
	init_timer4();
	init_ccp();
	
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
				
				mod_start();
				mod_byte(0x0); //flags
				mod_byte(0x0); //dfsid
				mod_byte(0x0);
				mod_byte(0xAD);
				mod_byte(0xBE);
				mod_byte(0xEF);
				mod_byte(0xCA);
				mod_byte(0xFE);
				mod_byte(0xBA);
				mod_byte(0xE0);
				mod_byte(0x2B); //crc
				mod_byte(0x49); //crc
				mod_end();
				
				state = STATE_IDLE;
				TMR2 = 0x0;
				break;
		}
	}
}
