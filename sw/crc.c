#define	DATA_LEN		10
#define	POLYNOMIAL		0x8408

#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv) {
	uint8_t data[DATA_LEN + 2] = { 0, 0, 0x0, 0xFE, 0xCA, 0xEF, 0xBE, 0xAD, 0xDE, 0xE0 };
	uint16_t cur_crc;
	int i, j;
	int cnt;

	cnt = DATA_LEN;
	cur_crc = 0xFFFF;
	for (i = 0; i < cnt; i++) {
		cur_crc ^= (uint16_t) data[i];
		for (j = 0; j < 8; j++) {
			if (cur_crc & 0x0001)
				cur_crc = (cur_crc >> 1) ^ POLYNOMIAL;
			else
				cur_crc >>= 1;
		}
	}

	cur_crc = ~cur_crc;
	fprintf(stderr, "Generated CRC: %X\n", cur_crc);
	return 0;
}
