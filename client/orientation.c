#include <stdbool.h>
#include <stdint.h>
#include <darnit/darnit.h>
#include <math.h>
#include <signal.h>

#include "tag.h"

void sigint(int num) {
	d_quit();
}

int main(int argc, char **argv) {
	int32_t angle = 0;
	DARNIT_SPRITE *sprite;
	Tag *tag;
	
	if(argc < 2) {
		fprintf(stderr, "Usage: orientation.elf /dev/ttySerialDevice\n");
		return 1;
	}
	
	d_init_custom("0xDEADBEEF RFID Soft Tag Demo", 1280, 720, false, "0xdeadbeef", NULL);
	
	signal(SIGINT, sigint);
	
	tag = tag_init(argv[1], 0xe0deadbeefcafe00, 15);
	d_render_blend_enable();
	d_render_clearcolor_set(0xff, 0xff, 0xff);
	sprite = d_sprite_load("tag.spr", 0, DARNIT_PFORMAT_RGBA8);
	d_sprite_move(sprite, 320, 40);

	for (;;) {
		if (d_keys_get().left)
			angle += 20;
		if (d_keys_get().right)
			angle -= 20;
		d_sprite_rotate(sprite, tag_get_angle(tag) * 180./M_PI * 10 + 1800 + 900);
		d_render_begin();
		d_sprite_draw(sprite);
		d_render_end();
		d_loop();
	}

}
