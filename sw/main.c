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

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

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

void test_dac() {
    // outputs DAC voltage to RA0
    DAC1CON0bits.DAC1OE = true;
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/


//void interrupt isr_comp(void) // interrupt function 
//{
//if(INTCONbits.T0IF && INTCONbits.T0IE) 
//{// if timer flag is set & interrupt enabled
//TMR0 -= 250;// reload the timer - 250uS per interrupt
//INTCONbits.T0IF = 0;// clear the interrupt flag 
//PORTB = 0x40;// toggle a bit to say we're alive
//}


void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    OSCCONbits.SCS = 0x00;
    OSCCONbits.IRCF = 0x0D;
    
    while(!OSCSTATbits.HFIOFR);
    
    FVRCONbits.FVREN = true;
    FVRCONbits.CDAFVR = 0x2; // 2x gain
    
    while(!FVRCONbits.FVRRDY);
    
    DAC1CON0bits.DAC1EN = true;
    DAC1CON0bits.DAC1PSS = 0x2; // FVR
    DAC1CON1 = 230; // FVR
    DAC1CON0bits.DAC1OE = false;
    
    init_comparator();

    CM1CON1bits.C1INTN = true;
    CM1CON1bits.C1INTP = true;
    
//    test_dac();

    
    TRISA = 0xFE;
    unsigned char x = 1;
    while(1)
    {
        unsigned char intr = PIR2bits.C1IF;
        PORTAbits.RA0 = intr;
        if(intr) {
            PIR2bits.C1IF = false;
        }
    }

}

