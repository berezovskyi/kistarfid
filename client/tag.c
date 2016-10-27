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
#include <stdbool.h>
#include <termios.h>
#include <sys/types.h>
#include <math.h>

#include "tag.h"
#include "trigonometry.h"

#define ADDR_X 0x0
#define ADDR_Y 0x2
#define ADDR_Z 0x3
#define ADDR_TEMP 0x1E

static int _get_serial_port(const char *path) {
	int fd;
	struct termios tios;

	if ((fd = open(path, O_RDWR | O_NOCTTY)) < 0) {
		fprintf(stderr, "Unable to open %s\n", path);
		return -1;
	}
	tcgetattr(fd, &tios);

	tios.c_cflag &= ~(CSIZE | PARENB);
	tios.c_cflag |= CS8;
	tios.c_cc[VMIN] = 1;
	tios.c_cc[VTIME] = 0;
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
	return fd;

}


static int _read_port(int fd, uint8_t *buff, int bytes) {
	int i;

	for (i = 0; i < bytes;)
		i += read(fd, &buff[i], bytes - i);
	return i;
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

Tag *tag_init(const char *serial, uint64_t id, size_t averaging_samples) {
	int fd;
	Tag *tag;
	
	if(!(tag = malloc(sizeof(Tag))))
		return NULL;
	
	if(!(tag->data = malloc(sizeof(Tag)))) {
		free(tag);
		return NULL;
	}
	
	if((fd = _get_serial_port(serial)) < 0) {
		free(tag->data);
		free(tag);
		return NULL;
	}
	
	memset(tag->data, 0, averaging_samples);
	tag->serial_fd = fd;
	tag->data_samples = averaging_samples;
	tag->id = id;
	
	return tag;
}

