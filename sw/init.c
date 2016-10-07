#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

void init_oscillator() {
	OSCCONbits.SCS = 0x00;
	OSCCONbits.IRCF = 0x0E;

	// wait until the ready state is reached
	while(!OSCSTATbits.HFIOFR);
}

void init_vref() {
	FVRCONbits.FVREN = true;
	FVRCONbits.CDAFVR = 0x2; // 2x gain

	// wait until the ready state is reached
	while(!FVRCONbits.FVRRDY);
}

void init_dac() {
	DAC1CON0bits.DAC1EN = true;
	DAC1CON0bits.DAC1PSS = 0x2; // FVR
	DAC1CON1 = 230; // FVR
	DAC1CON0bits.DAC1OE = false;
}

void test_dac() {
	// outputs DAC voltage to RA0
	DAC1CON0bits.DAC1OE = true;
}

void init_comparator() {
	CM1CON0bits.C1ON = true;
	CM1CON0bits.C1POL = false;
	CM1CON0bits.C1OUT = false;
	CM1CON0bits.C1SP = true;
	CM1CON0bits.C1HYS = false;
	CM1CON0bits.C1SYNC = false;

	CM1CON1bits.C1PCH = 0x01; // V_DAC

	ANSELAbits.ANSA1 = true;
	TRISAbits.TRISA1 = true;
	CM1CON1bits.C1NCH = 0x00; // C1IN0 -> RA1
}

void enable_comparator_int() {
	CM1CON1bits.C1INTN = false;
	CM1CON1bits.C1INTP = true;
}

void init_timer2() {
	T2CLKCONbits.T2CS = 0x2; //HFINTOSC
	T2CONbits.CKPS = 0x3;
	T2CONbits.OUTPS = 0x0;
	T2HLTbits.MODE = 0x0;
	PR2 = 150;
	
}
