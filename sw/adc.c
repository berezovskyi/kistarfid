#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>


void adc_init() {
		FVRCONbits.TSEN = 1;
		FVRCONbits.TSRNG = 1;
		ADCON0bits.ADON = 1;
		ADCON0bits.CHS = 2;
		ADCON1bits.ADCS = 0x2; // Clock source = Fosc/32
		ADCON1bits.ADPREF = 0x0; // Temp sensor is connected to Vdd
		ADCON1bits.ADFM = 0;
}


void adc_sample(uint8_t ch) {
		ADCON0bits.CHS = ch;
		ADCON0bits.GO = 1;
		while(ADCON0bits.GO);
}


inline uint8_t adc_get_high() {
		return ADRESH;
}

inline uint8_t adc_get_low() {
		return ADRESL;
}