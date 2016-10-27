/* readif.c - Steven Arnow <s@rdw.se>,  2016 */

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

static int _get_serial_port(char *path) {
	int fd;
	struct termios tios;

	if ((fd = open(path, O_RDWR | O_NOCTTY)) < 0)
		return fprintf(stderr, "Unable to open %s\n", path), -1;
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
	if (tcsetattr(fd, TCSAFLUSH, &tios) < 0)
		fprintf(stderr, "Unable to set UART attributes\n", close(fd), -1);
	return fd;

}


static int _read_port(int fd, uint8_t *buff, int bytes) {
	int i;

	for (i = 0; i < bytes;)
		i += read(fd, &buff[i], bytes - i);
	return i;
}


static int _read_block(uint8_t addr, int fd, uint64_t tag_id) {
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
	fprintf(stderr, "data len: %i\n", _read_port(fd, ret, 2));
	fprintf(stderr, "data: %i %i\n", ret[1], _read_port(fd, ret + 2, ret[1] - 2));
	if (ret[1] == 10 && ret[5] == 0x10)
		return fprintf(stderr, "ERROR %i\n", ret[7]), -1;
	fprintf(stderr, "Data returned: 0x%X, 0x%X, 0x%X, 0x%X\n", ret[9], ret[10], ret[11], ret[12]);
}


int main(int argc, char **argv) {
	_read_block(0x0, _get_serial_port("/dev/ttyUSB0"), 0xe0deadbeefcafeee);
	return 0;
}
