#include "view.h"
#include "command.h"

using namespace draw;

static bsreq gui_type[] = {
	BSREQ(gui_info, opacity, number_type),
	BSREQ(gui_info, opacity_disabled, number_type),
	BSREQ(gui_info, border, number_type),
	BSREQ(gui_info, window_width, number_type),
	BSREQ(gui_info, padding, number_type),
};
gui_info gui; BSGLOB(gui);

static rect tooltips_rect;
static char tooltips_text[4096];

void draw::menu() {
	draw::linw = 5.0;
	while(ismodal()) {
		rectf({0, 0, draw::getwidth(), draw::getheight()}, colors::gray);
		window({20, 20, 100, 80});
		auto id = input();
	}
}

areas draw::window(rect rc, bool disabled) {
	rc.offset(-gui.border, -gui.border);
	color c = colors::form;
	draw::rectf(rc, c, disabled ? gui.opacity / 2 : gui.opacity);
	draw::rectb(rc, c);
	return draw::area(rc);
}

int draw::window(int x, int y, int width, const char* string) {
	rect rc = {x, y, x + width, y};
	draw::state push;
	draw::font = metrics::font;
	int height = draw::textf(rc, string);
	window(rc, false);
	link[0] = 0; draw::textf(x, y, rc.width(), string);
	if(link[0])
		tooltips(x, y, rc.width(), AlignRight, link);
	return height + gui.border * 2 + gui.padding;
}

void draw::tooltips(int x1, int y1, int width, iflags align, const char* format, ...) {
	if(hot::key != InputIdle)
		return;
	tooltips_rect.x1 = x1 + width;
	tooltips_rect.y1 = y1;
	tooltips_rect.x2 = x1;
	tooltips_rect.y2 = y1;
	szprintv(tooltips_text, format, xva_start(format));
}

COMMAND(after_render) {
	if(!tooltips_text[0] || !tooltips_rect)
		return;
	draw::state push;
	draw::font = metrics::font;
	if(draw::font) {
		rect rc = tooltips_rect;
		if(tooltips_rect.y1 == tooltips_rect.y2) {
			draw::textf(rc, tooltips_text);
			rc.offset(-gui.padding, -gui.padding);
		}
		// Correct border
		int height = draw::getheight();
		int width = draw::getwidth();
		if(rc.y2 >= height)
			rc.move(0, height - 2 - rc.y2);
		if(rc.x2 >= width)
			rc.move(width - 2 - rc.x2, 0);
		// Show background
		draw::rectf(rc, colors::tips::back);
		draw::rectb(rc, colors::border);
		rc.offset(gui.padding);
		// Show text
		draw::fore = colors::tips::text;
		draw::textf(rc.x1, rc.y1, rc.width(), tooltips_text);
	}
	tooltips_rect.clear();
	tooltips_text[0] = 0;
}