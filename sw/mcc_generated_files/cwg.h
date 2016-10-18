/**
  CWG Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    cwg.h

  @Summary
    This is the generated header file for the CWG driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for CWG.
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

#ifndef _CWG_H
#define _CWG_H

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
  Section: CWG APIs
*/

/**
  @Summary
    Initializes the CWG

  @Description
    This routine configures the CWG specific control registers

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment
    

  @Example
    <code>
    CWG_Initialize();
    </code>
*/
void CWG_Initialize(void);


/**
  @Summary
    Software generated Shutdown event

  @Description
    This function forces the CWG into Shutdown state.

  @Preconditions
    CWG_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    CWG_Initialize();
    
    // do something
    
    CWG_AutoShutdownEventSet();
    </code>
*/
void CWG_AutoShutdownEventSet();

/**
  @Summary
    This function makes the CWG to resume its operations from the software
    generated shutdown state.

  @Description
    When auto-restart is disabled, the shutdown state will persist as long as the
    CWGAS0<SHUTDOWN> bit is set and hence to resume operations, this function should be used.

    However when auto-restart is enabled, the CWGAS0<SHUTDOWN> bit will be cleared automatically
    and resume operation on the next rising edge event. In that case, there is no
    need to call this function.

  @Preconditions
    CWG_Initialize() and CWG_AutoShutdownEventSet() functions should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    CWG_Initialize();
    
    // Do something
    
    CWG_AutoShutdownEventSet();

    // Do something
    
    CWG_AutoShutdownEventClear();
    </code>
*/
void CWG_AutoShutdownEventClear();


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _CWG_H
/**
 End of File
*/