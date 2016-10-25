/**
  CCP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp1.c

  @Summary
    This is the generated driver implementation file for the CCP1 driver using MPLAB(c) Code Configurator

  @Description
    This header file provides implementations for driver APIs for CCP1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC12LF1612
        Driver Version    :  2.00
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
#include "ccp1.h"

/**
  Section: COMPARE Module APIs
*/

void CCP1_Initialize(void)
{
    // Set the CCP1 to the options selected in the User Interface

    // MODE Pulseoutput; OE enabled; EN enabled; FMT right_aligned; 
    CCP1CON = 0xCA;    

    // RH 0; 
    CCPR1H = 0x00;    

    // RL 0; 
    CCPR1L = 0x00;    

}

void CCP1_CompareCountSet(uint16_t compareCount)
{
    CCP_PERIOD_REG_T module;
    
    // Write the 16-bit compare value
    module.ccpr1_16Bit = compareCount;
    
    CCPR1L = module.ccpr1l;
    CCPR1H = module.ccpr1h;
}

bool CCP1_OutputStatusGet(void)
{
    // Returns the output status
    return(CCP1CONbits.OUT);
}

bool CCP1_IsCompareComplete(void)
{
    // Check if compare is complete by reading "CCPIF" flag.
    bool status = PIR1bits.CCP1IF;
    if(status)
        PIR1bits.CCP1IF = 0;
    return (status);
}
/**
 End of File
*/