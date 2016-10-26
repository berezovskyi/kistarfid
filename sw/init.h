/* 
 * File:   init.h
 * Author: axel
 *
 * Created on October 26, 2016, 5:06 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

void init_oscillator();
void init_vref();
void init_dac();
void init_comparator();
void enable_comparator_int();
void init_timer2();
void init_ccp();
void init_timer4();


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

