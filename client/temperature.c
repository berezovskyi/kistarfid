#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <limits.h>

#include "tag.h"

int main(int argc, char **argv) {
	Tag *tag;
	double temperature;
	
	if(argc < 2) {
		fprintf(stderr, "Usage: temperature.elf /dev/ttySerialDevice\n");
		return 1;
	}
	
	tag = tag_init(argv[1], 0xe0deadbeefcafe00, 15);
	for(;;) {
		temperature = tag_get_temperature(tag);
		if(temperature == HUGE_VAL)
			continue;
		printf("Temperature: %lf\n", temperature);
	}
	
	return 0;
}
