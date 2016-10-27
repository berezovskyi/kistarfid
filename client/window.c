#include <stdbool.h>
#include <darnit/darnit.h>


int main(int argc, char **argv) {
	int32_t angle = 0;
	DARNIT_SPRITE *sprite;
	d_init_custom("TrollTag Demo", 1280, 720, false, "trolltag", NULL);

	d_render_blend_enable();
	d_render_clearcolor_set(0xff, 0xff, 0xff);
	sprite = d_sprite_load("tag.spr", 0, DARNIT_PFORMAT_RGBA8);
	d_sprite_move(sprite, 320, 40);

	for (;;) {
		if (d_keys_get().left)
			angle += 20;
		if (d_keys_get().right)
			angle -= 20;
		d_sprite_rotate(sprite, angle);	// ANGLE ANGLE GEIF ANGLE
		d_render_begin();
		d_sprite_draw(sprite);
		d_render_end();
		d_loop();
	}

}
