#include <stdbool.h>
#include <stdint.h>
#include <darnit/darnit.h>
#include <math.h>

#include "tag.h"


int main(int argc, char **argv) {
	Tag *tag;

	tag = tag_init(argv[1], 0x0, 1);
	fprintf(stdout, "%llu\n", tag_get_id(tag));
	
	return 0;
}
