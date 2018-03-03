#include "view.h"
#include "command.h"

enum command_s {
	NoCommand,
	AcceptButton, YenButton, NoButton, CancelButton
};

using namespace draw;

static point camera;
static point camera_drag;
static rect last_board;
static point last_mouse;
static point tooltips_point;
static short tooltips_width;
static char tooltips_text[4096];
static surface map;
static gobject* current_player;
static gobject* current_province;
extern rect sys_static_area;

static bsreq gui_type[] = {
	BSREQ(gui_info, opacity, number_type),
	BSREQ(gui_info, opacity_disabled, number_type),
	BSREQ(gui_info, opacity_hilighted, number_type),
	BSREQ(gui_info, opacity_hilighted_province, number_type),
	BSREQ(gui_info, border, number_type),
	BSREQ(gui_info, control_border, number_type),
	BSREQ(gui_info, button_width, number_type),
	BSREQ(gui_info, window_width, number_type),
	BSREQ(gui_info, hero_window_width, number_type),
	BSREQ(gui_info, tips_width, number_type),
	BSREQ(gui_info, hero_width, number_type),
	BSREQ(gui_info, padding, number_type),
{}
};
gui_info gui; BSGLOB(gui);

static void debug_mouse() {
	char temp[128];
	draw::state state;
	draw::fore = colors::text;
	draw::font = metrics::font;
	szprints(temp, endofs(temp), "mouse %1i, %2i, map mouse %3i, %4i", hot::mouse.x, hot::mouse.y, last_mouse.x, last_mouse.y);
	draw::text(2, draw::getheight() - 20, temp);
}

static void render_power(int x, int y, const gobject* owner, const gobject* province) {
	draw::circlef(x, y, 4*4, colors::green, 128);
	draw::circle(x, y, 4*4, colors::green);
}

static void render_province(rect rc, point mouse, const gobject* owner, int id) {
	char temp[1024];
	draw::state push;
	draw::fore = colors::black;
	draw::fore_stroke = colors::white;
	if(!draw::font)
		return;
	gobject* objects[64];
	for(auto& e : gobject::getcol(province_type)) {
		if(!e.isvalid())
			continue;
		draw::font = metrics::h1;
		point real_pos = e.getposition();
		point pt = {(short)(real_pos.x - rc.x1 - camera.x), (short)(real_pos.y - rc.y1 - camera.y)};
		szprints(temp, endofs(temp), "%1", e.getname());
		auto text_width = draw::textw(temp);
		if(id) {
			rect rc = {pt.x - text_width / 2, pt.y - draw::texth() / 2, pt.x + text_width / 2, pt.y + draw::texth() / 2};
			auto a = hilite(rc);
			if(a == AreaHilitedPressed)
				draw::execute(id, (int)&e);
		}
		render_power(pt.x, pt.y, owner, &e);
		draw::text(pt.x - text_width / 2, pt.y - draw::texth() / 2, temp, -1, TextStroke);
		if(hot::key == MouseLeft && hot::pressed) {
			auto d = distance(mouse, real_pos);
			//if(d < 16)
			//	draw::execute(ChooseProvince, e.getid());
		}
		pt.y += draw::texth() / 2;
		draw::font = metrics::font;
		unsigned count;
		count = owner->getheroes(objects, 1, &e);
		if(count) {
			szprints(temp, endofs(temp), "%1", objects[0]->getname());
			rect rc = {0, 0, 200, 0}; draw::textw(rc, temp);
			pt.y += draw::text({pt.x - rc.width() / 2, pt.y, pt.x + rc.width() / 2, pt.y + rc.height()}, temp, AlignCenter);
		}
		count = owner->gettropps(objects, lenghtof(objects), &e);
		if(count) {
			gobject::getpresent(temp, sizeof(temp) / sizeof(temp[0]), objects, count);
			rect rc = {0, 0, 200, 0}; draw::textw(rc, temp);
			pt.y += draw::text({pt.x - rc.width() / 2, pt.y, pt.x + rc.width() / 2, pt.y + rc.height()}, temp, AlignCenter);
		}
	}
}

static void render_frame(rect rc, const gobject* province_owner, int choose_province) {
	draw::state push;
	draw::area(rc); // Drag and drop analize this result
	last_board = rc;
	last_mouse.x = (short)(hot::mouse.x - rc.x1 + camera.x);
	last_mouse.y = (short)(hot::mouse.y - rc.y1 + camera.y);
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
	if(province_owner)
		render_province(last_board, last_mouse, province_owner, choose_province);
#ifdef _DEBUG
	debug_mouse();
#endif
}

static int render_hero(int x, int y, int width, gobject* e, bool hilite, bool disabled, const char* disable_text) {
	char temp[2048]; temp[0] = 0;
	draw::state push;
	draw::font = metrics::font;
	auto pa = e->getavatar();
	int height = gui.hero_width;
	szprints(zend(temp), endofs(temp), "###%1\n", e->getname());
	for(auto p : e->getbonuses()) {
		zcat(temp, p->getname());
		zcat(temp, "\n:::");
	}
	auto owner = e->getowner();
	rect rc = {x, y, x + width, y + height};
	areas hittest = window(rc, disabled, hilite);
	//if(owner)
	//	draw::shield(x + drw.hero_width - 20, y + 18, owner->getimage());
	int x1 = x;
	if(pa) {
		int y1 = y;
		avatar(x, y1, pa);
		rectb({x, y1, x + gui.hero_width, y1 + gui.hero_width}, colors::border);
		x1 += gui.hero_width + gui.padding;
	}
	draw::textf(x1, y - 3, rc.x2 - x1, temp);
	if(hittest == AreaHilited || hittest == AreaHilitedPressed) {
		static const char* abilities[] = {"attack", "defence", "raid", "enemy_casualties", "friendly_casualties"};
		temp[0] = 0;
		// Ability block
		auto ps = zend(temp);
		for(auto text : abilities) {
			auto value = e->get(text);
			if(!value)
				continue;
			auto pf = msgcombat_type->find(text);
			if(!pf)
				continue;
			auto pn = (const char*)pf->get(pf->ptr(&msgcombat));
			if(!pn)
				continue;
			if(ps[0])
				zcat(temp, "\n:::");
			szprints(zend(temp), endofs(temp), "%+2i %1", pn, value);
		}
		tooltips(x, y, width, temp);
	}
	return height + gui.border * 2;
}

static int render_heroes(int x, int y, gobject* owner) {
	auto y0 = y;
	if(!owner)
		return 0;
	for(auto& e : gobject::getcol(hero_type)) {
		if(e.getowner() != owner)
			continue;
		y += render_hero(x, y, gui.hero_window_width, &e, true, !e.isready(), 0);
		y += gui.padding;
	}
	return y - y0;
}

static void render_board(const gobject* province_owner, gobject* hero_owner, int choose_province) {
	render_frame({0, 0, draw::getwidth(), draw::getheight()}, province_owner, choose_province);
	auto x = getwidth() - gui.hero_window_width - gui.border - gui.padding;
	auto y = gui.padding + gui.border;
	y += render_heroes(x, y, hero_owner);
}

static bool control_board(int id) {
	const int step = 32;
	switch(id) {
		//case MouseWheelUp: scale += 0.005; break;
		//case MouseWheelDown: scale -= 0.005; break;
	case KeyLeft: camera.x -= step; break;
	case KeyRight: camera.x += step; break;
	case KeyUp: camera.y -= step; break;
	case KeyDown: camera.y += step; break;
	case MouseLeft:
		if(hot::pressed) {
			if(last_board == hot::hilite) {
				draw::drag::begin("board");
				camera_drag = camera;
			}
		}
		break;
	default:
		if(draw::drag::active("board")) {
			hot::cursor = CursorAll;
			if(hot::mouse.x >= 0 && hot::mouse.y >= 0)
				camera = camera_drag + (draw::drag::mouse - hot::mouse);
			return true;
		}
		return false;
	}
	return true;
}

void gobject::setuiactive() {
	current_player = this;
}

areas draw::hilite(rect rc) {
	auto border = gui.border;
	rc.offset(-border, -border);
	color c = colors::form;
	auto rs = draw::area(rc);
	if(rs == AreaHilited) {
		auto op = gui.opacity_hilighted_province;
		draw::rectf(rc, c, op);
		draw::rectb(rc, c);
	}
	return rs;
}

areas draw::window(rect rc, bool disabled, bool hilight, int border) {
	if(border == 0)
		border = gui.border;
	rc.offset(-border, -border);
	color c = colors::form;
	auto rs = draw::area(rc);
	auto op = gui.opacity;
	if(disabled)
		op = op / 2;
	else if(hilight && !disabled && (rs == AreaHilited || rs == AreaHilitedPressed))
		op = gui.opacity_hilighted;
	draw::rectf(rc, c, op);
	draw::rectb(rc, c);
	return rs;
}

int draw::window(int x, int y, int width, const char* string) {
	rect rc = {x, y, x + width, y};
	draw::state push;
	draw::font = metrics::font;
	int height = draw::textf(rc, string);
	window(rc, false);
	link[0] = 0; draw::textf(x, y, rc.width(), string);
	if(link[0])
		tooltips(x, y, rc.width(), link);
	return height + gui.border * 2 + gui.padding;
}

int draw::windowb(int x, int y, int width, const char* string, int id, int param, int border) {
	draw::state push;
	draw::font = metrics::font;
	rect rc = {x, y, x + width, y + draw::texth()};
	auto ra = window(rc, false, id!=0, border);
	draw::text(rc, string, AlignCenterCenter);
	if(id && ra == AreaHilitedPressed && hot::key == MouseLeft)
		draw::execute(id, param);
	return rc.height() + gui.border * 2;
}

void draw::tooltips(int x1, int y1, int width, const char* format, ...) {
	tooltips_point.x = x1;
	tooltips_point.y = y1;
	tooltips_width = width;
	szprintv(tooltips_text, tooltips_text + sizeof(tooltips_text) - 1, format, xva_start(format));
}

COMMAND(after_render) {
	if(!tooltips_text[0])
		return;
	draw::state push;
	draw::font = metrics::font;
	if(draw::font) {
		rect rc;
		rc.x1 = tooltips_point.x + tooltips_width + gui.border * 2 + gui.padding;
		rc.y1 = tooltips_point.y;
		rc.x2 = rc.x1 + gui.tips_width;
		rc.y2 = rc.y1;
		draw::textf(rc, tooltips_text);
		if(rc.x2 > getwidth() - gui.border - gui.padding) {
			auto w = rc.width();
			rc.x1 = tooltips_point.x - gui.border * 2 - gui.padding - w;
			rc.x2 = rc.x1 + w;
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
		render_board(current_player, current_player, 0);
		draw::window(gui.border * 2, gui.border * 2, gui.window_width, format);
		auto id = input();
		if(control_board(id))
			continue;
	}
}

gobject* draw::getaction(gobject* player, gobject* hero) {
	while(ismodal()) {
		render_frame({0, 0, draw::getwidth(), draw::getheight()}, player, 0);
		auto x = getwidth() - gui.hero_window_width - gui.border - gui.padding;
		auto y = gui.padding + gui.border;
		y += render_hero(x, y, gui.hero_window_width, hero, false, hero->isready(), 0) + 1;
		for(auto& e : gobject::getcol(action_type))
			y += windowb(x, y, gui.hero_window_width, e.getname(), AcceptButton, (int)&e, gui.border) + 1;
		y += windowb(x, y, gui.hero_window_width, msgmenu.cancel, CancelButton, 0) + 1;
		auto id = input();
		if(control_board(id))
			continue;
		switch(id) {
		case KeyEscape:
		case CancelButton:
			return 0;
		case AcceptButton:
			return (gobject*)hot::param;
		}
	}
	return 0;
}

gobject* draw::getprovince(gobject* player, gobject* hero, gobject* action) {
	while(ismodal()) {
		render_frame({0, 0, draw::getwidth(), draw::getheight()}, player, AcceptButton);
		auto x = getwidth() - gui.hero_window_width - gui.border - gui.padding;
		auto y = gui.padding + gui.border;
		y += render_hero(x, y, gui.hero_window_width, hero, false, hero->isready(), 0) + 1;
		y += windowb(x, y, gui.hero_window_width, action->getname(), 0, 0, gui.border) + 1;
		y += windowb(x, y, gui.hero_window_width, msgmenu.cancel, CancelButton, 0) + 1;
		auto id = input();
		if(control_board(id))
			continue;
		switch(id) {
		case KeyEscape:
		case CancelButton:
			return 0;
		case AcceptButton:
			return (gobject*)hot::param;
		}
	}
	return 0;
}

void draw::avatar(int x, int y, const char* id) {
	static amap<const char*, surface> avatars;
	auto p = avatars.find(id);
	if(!p) {
		p = avatars.add(id);
		memset(p, 0, sizeof(*p));
		p->resize(gui.hero_width, gui.hero_width, 32, true);
		surface e(id, 0);
		if(e) {
			e.convert(-32, 0);
			blit(*p, 0, 0, p->width, p->height, 0, e, 0, 0, e.width, e.height);
		}
	}
	blit(*draw::canvas, x, y, gui.hero_width, gui.hero_width, 0, *p, 0, 0);
}

int	draw::button(int x, int y, int width, int id, unsigned flags, const char* label, const char* tips, void(*callback)()) {
	rect rc = {x, y, x + width, y + 4 * 2 + draw::texth()}; rc.offset(gui.control_border, gui.control_border);
	if(buttonh(rc, ischecked(flags), isfocused(flags), isdisabled(flags), true,
		label, 0, false, tips)
		|| (isfocused(flags) && hot::key == KeyEnter)) {
		if(callback)
			execute(callback);
		else
			execute(id);
	}
	return rc.height() + gui.padding * 2;
}

static void choose_accept() {
	draw::breakmodal(AcceptButton);
}

static void choose_no() {
	draw::breakmodal(0);
}

TEXTPLUGIN(accept) {
	if(hot::key == KeyEnter)
		execute(choose_accept);
	return button(x + width - gui.button_width, y, gui.button_width, AcceptButton, 0, msgmenu.accept, tips, choose_accept);
}

TEXTPLUGIN(yesno) {
	if(hot::key == Alpha + 'Y')
		execute(choose_accept);
	else if(hot::key == Alpha + 'N')
		execute(choose_no);
	auto height = button(x + width - gui.button_width, y, gui.button_width, AcceptButton, 0, msgmenu.yes, tips, choose_accept);
	width -= gui.button_width + gui.padding;
	button(x + width - gui.button_width, y, gui.button_width, AcceptButton, 0, msgmenu.no, tips, choose_no);
	return height;
}