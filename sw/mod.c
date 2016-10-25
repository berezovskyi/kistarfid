#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

#include "mod.h"

#define MOD_BIT() do { \
		if(byte & 0x1) \
			mod_1(); \
		else \
			mod_0(); \
		byte >>= 1; \
	} while(false)


void mod_start()
{
	OSCTUNE = -32;

	TMR4 = 0;
	CCPR2L = 7;
	CCP2CONbits.EN = true;
	T1CONbits.TMR1ON = true;

	T4CONbits.ON = true;
	while (T4CONbits.ON);
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	T4CONbits.ON = true;
	while (T4CONbits.ON);

	CCPR2L = 8;
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	T4CONbits.ON = true;
	while (T4CONbits.ON);

	T1CONbits.TMR1ON = false;
	TMR0 = 0;
	T1CONbits.TMR1ON = true;

	CCPR2L = 7;
	T4CONbits.ON = true;
	while (T4CONbits.ON);

	CCPR2L = 8;
	T4CONbits.ON = true;
	while (T4CONbits.ON);

	CCP2CONbits.EN = false;
	T1CONbits.TMR1ON = false;
	TMR1 = 0;
}

void mod_end()
{
	TMR4 = 0;
	CCP2CONbits.EN = true;
	T1CONbits.TMR1ON = true;

	CCPR2L = 8;
	T4CONbits.ON = true;
	while (T4CONbits.ON);

	CCPR2L = 7;
	T4CONbits.ON = true;
	while (T4CONbits.ON);

	CCPR2L = 8;
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	T4CONbits.ON = true;
	while (T4CONbits.ON);

	CCPR2L = 7;
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	T4CONbits.ON = true;
	while (T4CONbits.ON);

	CCP2CONbits.EN = false;
	T1CONbits.TMR1ON = false;
	TMR1 = 0;

	OSCTUNE = 0;
}

void mod_1()
{
	TMR4 = 0;
	CCPR2L = 7;
	CCP2CONbits.EN = true;
	T1CONbits.TMR1ON = true;
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	CCPR2L = 8;
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	CCP2CONbits.EN = false;
	T1CONbits.TMR1ON = false;
	TMR1 = 0;
}

void mod_0()
{
	TMR4 = 0;
	CCPR2L = 8;
	CCP2CONbits.EN = true;
	T1CONbits.TMR1ON = true;
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	CCPR2L = 7;
	T4CONbits.ON = true;
	while (T4CONbits.ON);
	CCP2CONbits.EN = false;
	T1CONbits.TMR1ON = false;
	TMR1 = 0;
}

void mod_byte(uint8_t byte)
{
	MOD_BIT();
	MOD_BIT();
	MOD_BIT();
	MOD_BIT();

	MOD_BIT();
	MOD_BIT();
	MOD_BIT();
	MOD_BIT();
}
