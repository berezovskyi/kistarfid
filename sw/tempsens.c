#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>


void tempsens_init() {
		FVRCONbits.TSEN = 1;
		FVRCONbits.TSRNG = 1;
		ADCON0bits.ADON = 1;
		//ADCON0bits.CHS = 0x1E;
		ADCON0bits.CHS = 2;
		ADCON1bits.ADCS = 0x6; // Clock source = Fosc/64
		ADCON1bits.ADPREF = 0x0; // Temp sensor is connected to Vdd
		ADCON1bits.ADFM = 0;
}


void tempsens_prepare() {
		ADCON0bits.GO = 1;
}


inline uint8_t tempsens_get_high() {
		return ADRESH;
}

inline uint8_t tempsens_get_low() {
		return ADRESL;
}