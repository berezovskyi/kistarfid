/* 
 * File:   crc_pic.h
 * Author: andrew
 *
 * Created on October 25, 2016, 6:51 PM
 */

#ifndef CRC_PIC_H
#define	CRC_PIC_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

extern uint8_t bytes[10];
extern uint8_t crc_lo;
extern uint8_t crc_hi;
extern uint16_t scratch;

void crc_init();

uint16_t reverse_bits(uint16_t word);

inline uint8_t reverse_8b(uint8_t b);

inline void reverse_crc();

inline void crc_compute(const uint8_t *bytes, uint8_t len);

void crc_eq_pin();

void crc_manchester();

void crc_test();


#ifdef	__cplusplus
}
#endif

#endif	/* CRC_PIC_H */

