#include "view.h"
#include "command.h"

using namespace draw;

static bsreq gui_type[] = {
	BSREQ(gui_info, opacity, number_type),
	BSREQ(gui_info, opacity_disabled, number_type),
	BSREQ(gui_info, border, number_type),
	BSREQ(gui_info, window_width, number_type),
	BSREQ(gui_info, tips_width, number_type),
	BSREQ(gui_info, padding, number_type),
};
gui_info gui; BSGLOB(gui);

static point camera;
static rect last_board;
static rect tooltips_rect;
static char tooltips_text[4096];
static surface map;

static void render_frame(rect rc) {
	draw::state push;
	draw::area(rc);
	last_board = rc;
	int w = rc.width();
	int h = rc.height();
	int x1 = camera.x;
	int y1 = camera.y;
	int x2 = x1 + w;
	int y2 = y1 + h;
	if(x1 < 0) {
		rc.x1 -= x1;
		x1 = 0;
	}
	if(x2 > map.width) {
		rc.x2 -= x2 - map.width;
		x2 = map.width;
	}
	if(y1 < 0) {
		rc.y1 -= y1;
		y1 = 0;
	}
	if(y2 > map.height) {
		rc.y2 -= y2 - map.height;
		y2 = map.height;
	}
	if(rc.x1 != last_board.x1 || rc.y1 != last_board.y1 || rc.y2 != last_board.y2 || rc.x2 != last_board.x2)
		draw::rectf(last_board, colors::gray);
	if(rc.width() > 0 && rc.height() > 0)
		blit(*draw::canvas, rc.x1, rc.y1, rc.width(), rc.height(), 0, map, x1, y1);
#ifdef _DEBUG
	//debug_mouse();
#endif
}

static bool control_board(int id) {
	const int step = 32;
	switch(id) {
		//case MouseWheelUp: scale += 0.005; break;
		//case MouseWheelDown: scale -= 0.005; break;
	case KeyLeft:
		camera.x -= step;
		break;
	case KeyRight:
		camera.x += step;
		break;
	case KeyUp:
		camera.y -= step;
		break;
	case KeyDown:
		camera.y += step;
		break;
	case MouseLeft:
		//if(hot::pressed) {
		//	if(last_board == draw::lastarea) {
		//		draw::drag::begin("board");
		//		camera_drag = camera;
		//	}
		//}
		break;
	default:
		//if(draw::drag::active("board")) {
		//	hot::cursor = CursorAll;
		//	if(hot::mouse.x >= 0 && hot::mouse.y >= 0)
		//		camera = camera_drag + (draw::drag::mouse - hot::mouse);
		//	return true;
		//}
		return false;
	}
	return true;
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
	tooltips_rect.x1 = x1 + width + gui.border*2 + gui.padding;
	tooltips_rect.y1 = y1;
	tooltips_rect.x2 = tooltips_rect.x1;
	tooltips_rect.y2 = tooltips_rect.y1;
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
			rc.x2 = rc.x1 + gui.tips_width;
			draw::textf(rc, tooltips_text);
		}
		// Correct border
		int height = draw::getheight();
		int width = draw::getwidth();
		if(rc.y2 >= height)
			rc.move(0, height - 2 - rc.y2);
		if(rc.x2 >= width)
			rc.move(width - 2 - rc.x2, 0);
		draw::window(rc);
		draw::fore = colors::tips::text;
		draw::textf(rc.x1, rc.y1, rc.width(), tooltips_text);
	}
	tooltips_rect.clear();
	tooltips_text[0] = 0;
}

bool draw::initializemap() {
	if(!game.map || !game.map[0])
		return false;
	char temp[260];
	if(!map.read(szurl(temp, "maps", game.map)))
		return false;
	map.convert(-32, 0);
	return true;
}

void draw::report(const char* format) {
	while(ismodal()) {
		render_frame({0, 0, draw::getwidth(), draw::getheight()});
		draw::window(100, 100, gui.window_width, format);
		auto id = input();
		if(control_board(id))
			continue;
	}
}