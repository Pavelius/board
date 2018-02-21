#include "amap.h"
#include "command.h"
#include "crt.h"
#include "draw.h"

static void draw_icon(int& x, int& y, int x0, int& w, const char* id) {
	static amap<const char*, draw::surface> source;
	auto p = source.find(id);
	if(!p) {
		char temp[260];
		p = source.add(id);
		memset(p, 0, sizeof(*p));
		p->read(szurl(temp, "art/icons", id, "png"), 0, -32);
	}
	draw::blit(*draw::canvas, x, y, p->width, p->height, ImageTransparent, *p, 0, 0);
}

COMMAND(app_initialize) {
	draw::set(draw_icon);
}