#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

#include "crc_pic.h"

void crc_init()
{
	CRCCON0bits.EN = false;
	CRCCON0bits.EN = true;

	CRCACCH = 0xFF;
	CRCACCL = 0xFF; // seed value

	CRCXORH = 0x10; // ISO 13239 poly
	CRCXORL = 0x21;

	CRCCON1bits.DLEN = 0x7; // data len
	CRCCON1bits.PLEN = 0xF; // poly len

	CRCCON0bits.ACCM = true;

	CRCCON0bits.SHIFTM = true; // LSB first

	CRCCON0bits.CRCGO = true;
}

uint16_t reverse_bits(uint16_t word)
{
	scratch = word;
	word = 0;
	while (scratch != 0) {
		word <<= 1;
		word |= (scratch & 1);
		scratch >>= 1;
	}

	return word;
}

inline uint8_t reverse_8b(uint8_t b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

inline void reverse_crc()
{
	scratch = crc_lo;
	crc_lo = crc_hi;
	crc_hi = scratch;
	crc_lo = reverse_8b(crc_lo);
	crc_hi = reverse_8b(crc_hi);
}

inline void crc_compute(uint8_t* bytes, uint8_t len)
{
	crc_init();
	crc_lo = 0x0;
	crc_hi = 0x0;
	scratch = 0x0;
	for (uint8_t pos = 0; pos < len; pos++) {
		while (CRCCON0bits.FULL);
		CRCDATL = bytes[pos];
	}

	while (CRCCON0bits.BUSY);
	crc_lo = ~CRCACCL;
	crc_hi = ~CRCACCH;
	reverse_crc();
	return;
}

void crc_eq_pin()
{
	PORTAbits.RA0 = (0xB3 == crc_hi && 0x74 == crc_lo);
}

void crc_manchester()
{
	uint8_t packet2[2];
	packet2[0] = crc_hi;
	packet2[1] = crc_lo;

	PORTAbits.RA0 = true;
	PORTAbits.RA0 = false;
	for (uint8_t j = 0; j <= 1; j++) {
		uint8_t k, l;
		for (k = 0; k < 8; k++) {
			PORTAbits.RA0 = (packet2[j] >> (7 - k)) ^ 0x1;
			for (l = 0; l < 2; l++);
			PORTAbits.RA0 = (packet2[j] >> (7 - k)) ^ 0x0;
			for (l = 0; l < 2; l++);
		}
		PORTAbits.RA0 = false;
		for (k = 0; k < 20; k++);
	}
}

void crc_test()
{
	for (;;) {
		PORTAbits.RA0 = true;
		PORTAbits.RA0 = false;

		crc_compute(bytes, sizeof (bytes) / sizeof (bytes[0]));
		crc_eq_pin();
		//        crc_manchester();

		for (volatile uint8_t i = 0; i < 100; i++);
	}
}
