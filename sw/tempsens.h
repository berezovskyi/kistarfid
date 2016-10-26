/* 
 * File:   tempsens.h
 * Author: steven
 *
 * Created on October 26, 2016, 6:09 PM
 */

#include <stdint.h>

#ifndef TEMPSENS_H
#define	TEMPSENS_H

void tempsens_init();
void tempsens_prepare();
inline uint8_t tempsens_get_low();
inline uint8_t tempsens_get_high();

#endif	/* TEMPSENS_H */

