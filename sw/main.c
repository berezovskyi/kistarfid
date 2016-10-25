#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

//static const uint8_t const font[] = {
//	0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 94, 0, 0, 0, 0,
//	0, 0, 4, 3, 4, 3, 0, 0,
//	0, 36, 126, 36, 36, 126, 36, 0,
//	0, 36, 74, 255, 82, 36, 0, 0,
//	0, 70, 38, 16, 8, 100, 98, 0,
//	0, 52, 74, 74, 52, 32, 80, 0,
//	0, 0, 0, 4, 3, 0, 0, 0,
//	0, 0, 0, 126, 129, 0, 0, 0,
//	0, 0, 0, 129, 126, 0, 0, 0,
//	0, 42, 28, 62, 28, 42, 0, 0,
//	0, 8, 8, 62, 8, 8, 0, 0,
//	0, 0, 0, 128, 96, 0, 0, 0,
//	0, 8, 8, 8, 8, 8, 0, 0,
//	0, 0, 0, 0, 96, 0, 0, 0,
//	0, 64, 32, 16, 8, 4, 2, 0,
//	0, 62, 65, 73, 65, 62, 0, 0,
//	0, 0, 66, 127, 64, 0, 0, 0,
//	0, 0, 98, 81, 73, 70, 0, 0,
//	0, 0, 34, 73, 73, 54, 0, 0,
//	0, 0, 14, 8, 127, 8, 0, 0,
//	0, 0, 35, 69, 69, 57, 0, 0,
//	0, 0, 62, 73, 73, 50, 0, 0,
//	0, 0, 1, 97, 25, 7, 0, 0,
//	0, 0, 54, 73, 73, 54, 0, 0,
//	0, 0, 6, 9, 9, 126, 0, 0,
//	0, 0, 0, 102, 0, 0, 0, 0,
//	0, 0, 128, 102, 0, 0, 0, 0,
//	0, 0, 8, 20, 34, 65, 0, 0,
//	0, 0, 20, 20, 20, 20, 0, 0,
//	0, 0, 65, 34, 20, 8, 0, 0,
//	0, 2, 1, 81, 9, 6, 0, 0,
//	0, 28, 34, 89, 89, 82, 12, 0,
//	0, 0, 126, 9, 9, 126, 0, 0,
//	0, 0, 127, 73, 73, 54, 0, 0,
//	0, 0, 62, 65, 65, 34, 0, 0,
//	0, 0, 127, 65, 65, 62, 0, 0,
//	0, 0, 127, 73, 73, 65, 0, 0,
//	0, 0, 127, 9, 9, 1, 0, 0,
//	0, 0, 62, 65, 81, 50, 0, 0,
//	0, 0, 127, 8, 8, 127, 0, 0,
//	0, 0, 65, 127, 65, 0, 0, 0,
//	0, 0, 32, 64, 64, 63, 0, 0,
//	0, 0, 127, 8, 20, 99, 0, 0,
//	0, 0, 127, 64, 64, 64, 0, 0,
//	0, 127, 2, 4, 2, 127, 0, 0,
//	0, 127, 6, 8, 48, 127, 0, 0,
//	0, 0, 62, 65, 65, 62, 0, 0,
//	0, 0, 127, 9, 9, 6, 0, 0,
//	0, 0, 62, 65, 97, 126, 64, 0,
//	0, 0, 127, 9, 9, 118, 0, 0,
//	0, 0, 38, 73, 73, 50, 0, 0,
//	0, 1, 1, 127, 1, 1, 0, 0,
//	0, 0, 63, 64, 64, 63, 0, 0,
//	0, 31, 32, 64, 32, 31, 0, 0,
//	0, 63, 64, 48, 64, 63, 0, 0,
//	0, 0, 119, 8, 8, 119, 0, 0,
//	0, 3, 4, 120, 4, 3, 0, 0,
//	0, 0, 113, 73, 73, 71, 0, 0,
//	0, 0, 127, 65, 65, 0, 0, 0,
//	0, 2, 4, 8, 16, 32, 64, 0,
//	0, 0, 0, 65, 65, 127, 0, 0,
//	0, 4, 2, 1, 2, 4, 0, 0,
//	0, 64, 64, 64, 64, 64, 64, 0,
//	0, 0, 1, 2, 4, 0, 0, 0,
//	0, 0, 48, 72, 40, 120, 0, 0,
//	0, 0, 127, 72, 72, 48, 0, 0,
//	0, 0, 48, 72, 72, 0, 0, 0,
//	0, 0, 48, 72, 72, 127, 0, 0,
//	0, 0, 48, 88, 88, 16, 0, 0,
//	0, 0, 126, 9, 1, 2, 0, 0,
//	0, 0, 80, 152, 152, 112, 0, 0,
//	0, 0, 127, 8, 8, 112, 0, 0,
//	0, 0, 0, 122, 0, 0, 0, 0,
//	0, 0, 64, 128, 128, 122, 0, 0,
//	0, 0, 127, 16, 40, 72, 0, 0,
//	0, 0, 0, 127, 0, 0, 0, 0,
//	0, 120, 8, 16, 8, 112, 0, 0,
//	0, 0, 120, 8, 8, 112, 0, 0,
//	0, 0, 48, 72, 72, 48, 0, 0,
//	0, 0, 248, 40, 40, 16, 0, 0,
//	0, 0, 16, 40, 40, 248, 0, 0,
//	0, 0, 112, 8, 8, 16, 0, 0,
//	0, 0, 72, 84, 84, 36, 0, 0,
//	0, 0, 8, 60, 72, 32, 0, 0,
//	0, 0, 56, 64, 32, 120, 0, 0,
//	0, 0, 56, 64, 56, 0, 0, 0,
//	0, 56, 64, 32, 64, 56, 0, 0,
//	0, 0, 72, 48, 48, 72, 0, 0,
//	0, 0, 24, 160, 160, 120, 0, 0,
//	0, 0, 100, 84, 84, 76, 0, 0,
//	0, 0, 8, 28, 34, 65, 0, 0,
//	0, 0, 0, 126, 0, 0, 0, 0,
//	0, 0, 65, 34, 28, 8, 0, 0,
//	0, 0, 4, 2, 4, 2, 0, 0,
//	0, 120, 68, 66, 68, 120, 0, 0,
//};

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

void crc_init() {
    CRCCON0bits.EN = false;
    CRCCON0bits.EN = true;

    CRCACCH = 0xFF;
    CRCACCL = 0xFF; // seed value


    CRCXORH = 0x10; // ISO 13239 poly
    CRCXORL = 0x21;

    CRCCON1bits.DLEN = 0x7; // data len
    CRCCON1bits.PLEN = 0xF; // poly len

    CRCCON0bits.ACCM = true;

    CRCCON0bits.SHIFTM = true; // LSB first

    CRCCON0bits.CRCGO = true;
}

uint8_t crc_lo;
uint8_t crc_hi;
uint16_t scratch;

uint16_t reverse_bits(uint16_t* word) {
    scratch = *word;
    *word = 0;
    while (scratch!=0){
        (*word) <<= 1;
        (*word) |= (scratch & 1);
        scratch >>= 1;
    }
    
    return (*word);
}

inline uint8_t reverse_8b(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

inline void reverse_crc() {
    scratch = crc_lo;
    crc_lo = crc_hi;
    crc_hi = scratch;
    crc_lo = reverse_8b(crc_lo);
    crc_hi = reverse_8b(crc_hi);
}

inline void crc_compute(uint8_t* bytes, uint8_t len) {
    crc_init();
    for (uint8_t pos = 0; pos < len; pos++) {
        while(CRCCON0bits.FULL);
        CRCDATL = bytes[pos];
    }

    while(CRCCON0bits.BUSY);
//    crc_sum = ~(((uint16_t)CRCACCH << 8) | CRCACCL);
    crc_lo = ~CRCACCL;
    crc_hi = ~CRCACCH;
    return; //reverse_bits(&crc_sum);
}

//uint8_t bytes[10] = {
//    0x0, 0x0, 0x0, 0xFE,
//    0xCA,0xEF,0xBE,0xAD,
//    0xDE,0xE0
//};

uint8_t bytes[1] = {
    0x51
};

void crc_eq_pin() {
    PORTAbits.RA0 = (0xB3 == crc_hi && 0x74 == crc_lo);
}

void crc_manchester() {
    uint8_t packet2[2];
    packet2[0] = crc_hi;
    packet2[1] = crc_lo;

    PORTAbits.RA0 = true;
    PORTAbits.RA0 = false;
    for(uint8_t j = 0; j <= 1; j++) {
        uint8_t k, l;
        for(k = 0; k < 8; k++) {
            PORTAbits.RA0 = (packet2[j] >> (7 - k)) ^ 0x1;
            for(l = 0; l < 2; l++);
            PORTAbits.RA0 = (packet2[j] >> (7 - k)) ^ 0x0;
            for(l = 0; l < 2; l++);
        }
        PORTAbits.RA0 = false;
        for(k = 0; k < 20; k++);
    }
}

void crc_test() {
    for(;;) {
        PORTAbits.RA0 = true;
        PORTAbits.RA0 = false;
        
        crc_compute(bytes, sizeof(bytes)/sizeof(bytes[0]));
        reverse_crc();
        crc_eq_pin();
//        crc_manchester();

        for(volatile uint8_t i = 0; i < 100; i++);
    }
}

void main(void) {
	static State state = STATE_IDLE;
	static uint8_t val = 0;
	static uint8_t i = 0;

	// set the frequency to 4MHz
	init_oscillator();

    TRISA = 0xFE;

    crc_test();

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
				mod_byte(0xFE);
				mod_byte(0xCA);
				mod_byte(0xEF);
				mod_byte(0xBE);
				mod_byte(0xAD);
				mod_byte(0xDE);
				mod_byte(0xE0);
				mod_byte(0x3C); //crc
				mod_byte(0x00); //crc
				mod_end();

				state = STATE_IDLE;
				TMR2 = 0x0;
				break;
		}
	}
}
