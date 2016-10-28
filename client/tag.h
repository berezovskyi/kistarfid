#ifndef _TAG_H
#define _TAG_H

typedef struct IntVector2 IntVector2;
struct IntVector2 {
	int x;
	int y;
};

typedef struct Tag Tag;
struct Tag {
	int serial_fd;
	uint64_t id;
	size_t data_samples;
	IntVector2 *data;
};

Tag *tag_init(const char *serial, uint64_t id, size_t averaging_samples);
int tag_get_id(Tag *tag, uint64_t tag_id[16]);
double tag_get_angle(Tag *tag);

#endif
