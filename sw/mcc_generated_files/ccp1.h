/**
  CCP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp1.h

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

#ifndef _CCP1_H
#define _CCP1_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/** 
  Section: Data type definitions
*/
        
/**
 @Summary
   Defines the values to convert from 16bit to two 8 bit and vice versa

 @Description
   This routine used to get two 8 bit values from 16bit also
   two 8 bit value are combine to get 16bit.

 Remarks:
   None
 */

typedef union CCPR1Reg_tag
{
   struct
   {
      uint8_t ccpr1l;
      uint8_t ccpr1h;
   };
   struct
   {
      uint16_t ccpr1_16Bit;
   };
} CCP_PERIOD_REG_T ;

/**
  Section: COMPARE Module APIs
*/

/**
  @Summary
    Initializes the CCP1

  @Description
    This routine initializes the CCP1_Initialize
    This routine must be called before any other CCP1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    uint16_t compare;

    CCP1_Initialize();
    CCP1_CompareCountSet(compare);
    </code>
 */
void CCP1_Initialize(void);

/**
  @Summary
    Loads 16-bit compare value.

  @Description
    This routine loads the 16 bit compare value.

  @Preconditions
    CCP1_Initialize() function should have been
    called before calling this function.

  @Param
    compareCount: 16-bit unsigned value

  @Returns
    None

  @Example
    <code>
    uint16_t compare;

    CCP1_Initialize();
    CCP1_CompareCountSet(compare);
    </code>
*/
void CCP1_CompareCountSet(uint16_t compareCount);

/**
  @Summary
    Read compare output status.

  @Description
    This routine returns the compare output status.

  @Preconditions
    CCP1_Initialize() function should have been
    called before calling this function.

  @Param
    None

  @Returns
    true : output high
    false: output low

  @Example
    <code>
    uint16_t compare;
    bool status;
    CCP1_Initialize();
    CCP1_CompareCountSet(compare);
    while(1)
    {
        status = CCP1_OutputStatusGet();
    }
    </code>
*/
bool CCP1_OutputStatusGet(void);

/**
  @Summary
    Determines the completion of the data compare.

  @Description
    This routine is used to determine if data comparison is completed.
    When data comparison is complete routine returns 1. It returns 0 otherwise.

  @Preconditions
    CCP1_Initialize()function should have been called before calling this function.

  @Returns
   true - Indicates compare is complete
   false - Indicates compare is not complete

  @Param
    None

  @Example
    <code>
    uint16_t capture;

    CCP1_Initialize();
    CCP1_CompareCountSet(compare);
    while(!CCP1_IsCompareComplete());
    </code>
*/
bool CCP1_IsCompareComplete(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //_CCP1_H
/**
 End of File
*/
