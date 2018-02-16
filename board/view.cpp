#include "view.h"

static bsreq gui_type[] = {
	BSREQ(gui_info, opacity, number_type),
	BSREQ(gui_info, opacity_disabled, number_type),
	BSREQ(gui_info, border, number_type),
};
gui_info gui; BSGLOB(gui);
using namespace draw;

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