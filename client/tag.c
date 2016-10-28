/* readif.c - Steven Arnow <s@rdw.se>,  2016 */
/* Modified by Axel Isaksson <isaksson.axel@telia.com>, 2016*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/types.h>
#include <math.h>
#include <limits.h>

#include "tag.h"
#include "trigonometry.h"

#define ADDR_X 0x0
#define ADDR_Y 0x2
#define ADDR_Z 0x3
#define ADDR_TEMP 0x1E

#define TEMP_SCALE 2.42
#define TEMP_OFFSET 646.

static int _get_serial_port(const char *path) {
	int fd, flags;
	struct termios tios;

	if ((fd = open(path, O_RDWR | O_NOCTTY)) < 0) {
		fprintf(stderr, "Unable to open %s\n", path);
		return -1;
	}
	tcgetattr(fd, &tios);

	tios.c_cflag &= ~(CSIZE | PARENB);
	tios.c_cflag |= CS8;
	tios.c_cc[VMIN] = 1;
	tios.c_cc[VTIME] = 2;
	tios.c_iflag = 0;
	tios.c_oflag = 0;
	tios.c_lflag = 0;
	//cfmakeraw(&tios);
	cfsetospeed(&tios, B57600);
	cfsetispeed(&tios, B57600);
	if (tcsetattr(fd, TCSAFLUSH, &tios) < 0) {
		fprintf(stderr, "Unable to set UART attributes\n");
		close(fd);
		return -1;
	}

	if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
		flags = 0;
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	return fd;

}


static int _read_port(int fd, uint8_t *buff, int bytes) {
	int i, iter = 0, t;

	for (i = 0; i < bytes && iter < 120; iter++) {
		i += ((t = read(fd, &buff[i], bytes - i)) >= 0) ? t : 0;
		//fprintf(stderr, "arne2 %i\n", i);
		usleep(1000);
	}

	return i;
}


static void _do_transaction(Tag *tag, uint8_t *cmd, uint8_t *ret, uint8_t *ret_size) {
	write(tag->serial_fd, cmd, cmd[1]);
	memset(ret, 0, 258);
	_read_port(tag->serial_fd, ret, 2);
	_read_port(tag->serial_fd, ret + 2, ret[1] - 2);
	*ret_size = ret[1];
}


struct StackThing {
	uint8_t		*data;
	int		max;
	int		pos;
};

struct StackThing64 {
	uint64_t	*data;
	int		max;
	int		pos;
};


static struct StackThing *_alloc_stack_thing(int max_size) {
	struct StackThing *st;

	st = malloc(sizeof(*st));
	st->data = malloc(max_size);
	st->pos = 0;
	st->max = max_size;
	return st;
}

static struct StackThing64 *_alloc_stack_thing64(int max_size) {
	struct StackThing64 *st;

	st = malloc(sizeof(*st) * sizeof(uint64_t));
	st->data = malloc(max_size);
	st->pos = 0;
	st->max = max_size;
	return st;
}


static void _calc_checksum(struct StackThing *st) {
	int i;
	uint8_t sum = 0;

	st->data[1] = st->pos + 2;

	for (i = 0; i < st->pos; i++)
		sum ^= st->data[i];
	st->data[st->pos++] = sum;
	st->data[st->pos++] = ~sum;
}


static void _push_array(struct StackThing *st, uint8_t *arr, int size) {
	int i;
	for (i = 0; i < size; i++)
		st->data[st->pos++] = arr[i];
}


int tag_get_id(Tag *tag, uint64_t tag_id[16]) {
	int i, z, q = 0;
	struct StackThing *cmd_st;
	struct StackThing64 *mask_st;
	uint8_t ret_size;
	bool more_to_do = true;

	uint8_t cmd_inventory[] = { 1, 0, 0, 0, 0, 0, 0x60, 0x11, 0x7, 0x1, 0 };
	uint8_t cmd[] = { 1, 0, 0, 0, 0, 0, 0x60, 0x11, 0x7, 0x1, 0, /* ISO Inventory, no mask */
			0, 0 };
	
	uint64_t id;
	uint8_t chksm = 0, ret[258];
	cmd_st = _alloc_stack_thing(256);
	mask_st = _alloc_stack_thing64(256);
	_push_array(cmd_st, cmd_inventory, sizeof(cmd_inventory));
	_calc_checksum(cmd_st);
	_do_transaction(tag, cmd_st->data, ret, &ret_size);
	int mask_bytes = 0;
	int tag_count = 0;
	while (more_to_do) {
		//fprintf(stderr, "arne\n");
		if (ret[1] == 10 && ret[5] == 0x10) {
			fprintf(stderr, "ERROR %i\n", ret[7]);
			break;
		}

		if (ret[7] || ret[8]) {	// Data
			for (z = 0; z < 8; z++) {
				if (ret[7] & (0x1 << z))
					tag_count++;
				if (ret[8] & (0x1 << z))
					tag_count++;
			}

			for (z = 0; z < tag_count; z++, q++) {
				id = 0;
				for (i = 0; i < 8; i++)
					id |= (uint64_t) ret[13 + i + z*10] << (i * 8);
				fprintf(stderr, "Tag %i: 0x%"PRIX64"\n", q, id);
				tag_id[q] = id;
			}
		}


		if (ret[9] || ret[10]) {
			uint64_t time_slot;
			for (z = 0; z < 8; z++) {
				if (ret[9] & (1 << z)) {
					mask_bytes = cmd_st->data[10] / 8;
					for (i = 0; i < mask_bytes; i++)
						mask_st->data[mask_st->pos++] = cmd_st->data[11 + i];
					if (cmd_st->data[10] % 7) {
						time_slot = z << 4;
						time_slot |= cmd_st->data[11 + i];
						mask_st->data[mask_st->pos++] = time_slot;
					} else {
						time_slot = z;
						mask_st->data[mask_st->pos++] = time_slot;
					}

					mask_st->data[mask_st->pos++] = cmd_st->data[10] + 4;
				}
			}

			if (cmd_st->data[10] & (1 << z)) {
				mask_bytes = cmd_st->data[10] >> 3;
				for (i = 0; i < mask_bytes; i++)
					mask_st->data[mask_st->pos++] = cmd_st->data[11 + i];
				if (cmd_st->data[10] & 7) {
					time_slot = (z + 8) << 4;
					time_slot |= cmd_st->data[11 + i];
					mask_st->data[mask_st->pos++] = time_slot;
				} else {
					time_slot = z + 8;
					mask_st->data[mask_st->pos++] = time_slot;
				}
				mask_st->data[mask_st->pos++] = cmd_st->data[10] + 4;
			}
		}

		if (mask_st->pos) {
			int mask_bits;
			more_to_do = true;
			cmd_st->pos = 0;
			_push_array(cmd_st, cmd_inventory, sizeof(cmd_inventory) - 1);
			cmd_st->data[cmd_st->pos++] = mask_st->data[--mask_st->pos];
			mask_bits = mask_st->data[mask_st->pos];
			
			if (mask_bits == 64) {
				fprintf(stderr, "Unresolved tag collisions (bad signal?\n");
				return 0x0;
			}

			mask_bytes = mask_bits >> 3;
			if (mask_bits & 0x7)
				mask_bytes++;
			for (i = -1 * mask_bytes; i < 0; i++)
				cmd_st->data[cmd_st->pos++] = mask_st->data[--mask_st->pos];

			_do_transaction(tag, cmd_st->data, ret, &ret_size);
			_calc_checksum(cmd_st);
		} else
			more_to_do = false;
	}

	//if (ret[9] || ret[10])
	//	return fprintf(stderr, "Collision!\n"), 0;
	
	return q;
}


static uint16_t _read_block(uint8_t addr, int fd, uint64_t tag_id) {
	uint8_t cmd[] = { 1, 0, 0, 0, 0, 0, 0x60, 0x11, 0x63, 0x20, /* <- Reader crap */
		0, 0, 0, 0, 0, 0, 0, 0, /* Tag addr */
		0, 0, 0 };
	uint8_t ret[258];
	int i;
	uint8_t chksm = 0;
	cmd[1] = sizeof(cmd);
	for (i = 0; i < 8; i++)
		cmd[10 + i] = (i >> (8 * i)) & 0xFF;
	cmd[18] = addr;
	for (i = 0; i < sizeof(cmd) - 2; i++)
		chksm ^= cmd[i];
	cmd[19] = chksm;
	cmd[20] = ~chksm;
	
	write(fd, cmd, sizeof(cmd));
//	fprintf(stderr, "data len: %i\n", _read_port(fd, ret, 2));
	_read_port(fd, ret, 2);
//	fprintf(stderr, "data: %i %i\n", ret[1], _read_port(fd, ret + 2, ret[1] - 2));
	_read_port(fd, ret + 2, ret[1] - 2);
	if (ret[1] == 10 && ret[5] == 0x10)
		return fprintf(stderr, "ERROR %i\n", ret[7]), 1;
	//fprintf(stderr, "Data returned: 0x%X, 0x%X, 0x%X, 0x%X\n", ret[9], ret[10], ret[11], ret[12]);
	
	return (((uint16_t) ret[10]) << 8) | ret[9];
}


double tag_get_angle(Tag *tag) {
	int16_t xacc, yacc;
	uint16_t tmp;
	int i;
	double xavg, yavg;
	
	tmp = _read_block(ADDR_X, tag->serial_fd, tag->id);
	if (tmp != 1) {
		tmp >>= 6;
		xacc = tmp;
		xacc -= 512;
	} else {
		xacc = tag->data[tag->data_samples - 1].x;
	}
	
	tmp = _read_block(ADDR_Y, tag->serial_fd, tag->id);
	if (tmp != 1) {
		tmp >>= 6;
		yacc = tmp;
		yacc -= 512;
	} else {
		yacc = tag->data[tag->data_samples - 1].y;
	}
	
	xavg = xacc;
	yavg = yacc;
	
	for(i = 0; i < tag->data_samples - 1; i++) {
		xavg += (tag->data[i].x = tag->data[i + 1].x);
		yavg += (tag->data[i].y = tag->data[i + 1].y);
	}
	
	tag->data[tag->data_samples - 1].x = xacc;
	tag->data[tag->data_samples - 1].y = yacc;
	
	xavg /= tag->data_samples;
	yavg /= tag->data_samples;

	fprintf(stderr, "xacc: %f, xavg: %f, yacc: %f, yavg: %f\n", ((float) xacc) / 512, ((float) xavg) / 512, ((float) yacc) / 512, ((float) yavg) / 512);
	
	//return atan2(xavg, yavg);
	return trig_delta_to_angle_d(yavg, xavg);
	//return atan2(xacc, yacc);
}

double tag_get_temperature(Tag *tag) {
	uint16_t tmp;
	double temperature;
	if((tmp = _read_block(ADDR_TEMP, tag->serial_fd, tag->id)) == 1)
		return HUGE_VAL;
	tmp >>= 6;
	
	printf("Raw: %hu\n", tmp);
	temperature = tmp;
	temperature = (TEMP_OFFSET - temperature)/TEMP_SCALE;
	
	return temperature;
}

Tag *tag_init(const char *serial, uint64_t id, size_t averaging_samples) {
	int fd;
	Tag *tag;
	
	if(!(tag = malloc(sizeof(Tag))))
		return NULL;
	
	if(!(tag->data = malloc(averaging_samples*sizeof(IntVector2)))) {
		free(tag);
		return NULL;
	}
	
	if((fd = _get_serial_port(serial)) < 0) {
		free(tag->data);
		free(tag);
		return NULL;
	}
	
	memset(tag->data, 0, averaging_samples*sizeof(IntVector2));
	tag->serial_fd = fd;
	tag->data_samples = averaging_samples;
	tag->id = id;
	
	return tag;
}

