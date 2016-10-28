#include <stdbool.h>
#include <stdint.h>
#include <darnit/darnit.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

#include "tag.h"


int main(int argc, char **argv) {
	Tag *tag;
	uint64_t tag_id[16];
	int i, tags;
	DARNIT_TEXT_SURFACE *surf;
	DARNIT_FONT *font;

	d_init_custom("0xDEADBEEF Inventory Demo", 1280, 720, false, "trolltag", NULL);
	font = d_font_load("font.ttf", 96, 512, 512);
	surf = d_text_surface_new(font, 500, 1280, 0, 0);
	tag = tag_init(argv[1], 0x0, 1);

	d_render_blend_enable();

	for (;;) {
		if ((tags = tag_get_id(tag, tag_id)) > 0) {
			d_text_surface_reset(surf);
			fprintf(stderr, "%i tags\n", tags);
			d_text_surface_string_append(surf, "Detected tags:\n");
			for (i = 0; i < tags; i++) {
				char buff[30];
				sprintf(buff, "0x%16"PRIX64"\n", tag_id[i]);
				d_text_surface_string_append(surf, buff);
			}
		}

		d_render_begin();
		d_text_surface_draw(surf);
		d_render_end();
		d_loop();
	}
	//fprintf(stdout, "%llu\n", tag_get_id(tag));
	
	return 0;
}
