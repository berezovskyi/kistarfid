/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
	#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
	#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>
#include <pic12f1612.h>       /* For true/false definition */

// from system.h
// TODO remove
#define SYS_FREQ        500000L
// TODO remove
#define FCY             SYS_FREQ/4

void init_oscillator() {
	OSCCONbits.SCS = 0x00;
	OSCCONbits.IRCF = 0x0D;

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
	CM1CON1bits.C1INTN = true;
	CM1CON1bits.C1INTP = true;
}

void main(void)
{
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

//	test_dac();

	TRISA = 0xFE;
	while(1)
	{
	// BUG: 'intr' will get cleared before the falling edge will be detected
	unsigned char intr = PIR2bits.C1IF;
	PORTAbits.RA0 = intr;
		if(intr) {
			// need to clear the interrupt fla
			PIR2bits.C1IF = false;
		}
	}
}
