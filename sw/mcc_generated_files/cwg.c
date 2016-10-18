/**
  CWG Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    cwg.c

  @Summary
    This is the generated driver implementation file for the CWG driver using MPLAB(c) Code Configurator

  @Description
    This header file provides implementations for driver APIs for CWG.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC12LF1612
        Driver Version    :  1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "cwg.h"

/**
  Section: CWG APIs
*/

void CWG_Initialize(void)
{
    // Set the CWG to the options selected in MPLAB(c) Code Configurator

    // Writing to CWGxCON0, CWGxCON1, CWGxCON2, CWGxDBR & CWGxDBF registers
	// CWG1POLA non inverted; CWG1POLB non inverted; 
	CWG1CON1 = 0x00;
	// CWG1DBR 0; 
	CWG1DBR = 0x00;
	// CWG1DBF 0; 
	CWG1DBF = 0x00;
	// CWG1SHUTDOWN No Auto-shutdown; CWG1REN enabled; CWG1LSBD logic 1; CWG1LSAC inactive; 
	CWG1AS0 = 0x70;
	// CWG1C1AS disabled; CWG1TMR6AS disabled; CWG1INAS disabled; CWG1TMR4AS disabled; CWG1TMR2AS disabled; 
	CWG1AS1 = 0x00;
	// CWG1STRB enabled; CWG1STRA disabled; CWG1OVRA low; CWG1OVRB low; 
	CWG1OCON0 = 0x02;
	// CWG1OEA disabled; CWG1OEB enabled; 
	CWG1OCON1 = 0x02;
	// CWG1CS FOSC; 
	CWG1CLKCON = 0x00;
	// CWG1IS CCP1_OUT; 
	CWG1ISM = 0x03;
    
    // CWG1LD Buffer_not_loaded; CWG1EN enabled; CWG1MODE Steering mode; 
    CWG1CON0 = 0x80;
}


void CWG_AutoShutdownEventSet()
{
    // Setting the SHUTDOWN bit of CWGxAS0 register
    CWG1AS0bits.CWG1SHUTDOWN = 1;
}

void CWG_AutoShutdownEventClear()
{
    // Clearing the SHUTDOWN bit of CWGxAS0 register
    CWG1AS0bits.CWG1SHUTDOWN = 0;
}

/**
 End of File
*/
