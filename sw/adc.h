/* 
 * File:   adc.h
 * Author: steven
 *
 * Created on October 26, 2016, 6:09 PM
 */

#include <stdint.h>

#ifndef ADC_H
#define	ADC_H

void adc_init();
void adc_sample(uint8_t ch);
inline uint8_t adc_get_low();
inline uint8_t adc_get_high();

#endif	/* TEMPSENS_H */

