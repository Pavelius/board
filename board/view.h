#include "draw_controls.h"
#include "main.h"

#pragma once

struct gui_info {
	unsigned char	border;
	unsigned char	opacity, opacity_disabled, opacity_hilighted, opacity_hilighted_province;
	short			button_width, window_width, tips_width, hero_width, hero_window_width, control_border;
	short			padding;
};
extern gui_info		gui_data;

namespace draw {
namespace controls {
struct grid : table {
	grid(collection& source, column* columns) : source(source), table(columns) {}
	collection&		source;
	virtual const char* getname(char* result, const char* result_max, int line, int column) const override;
};
}
namespace dialogs {
struct dialog : draw::controls::control {
	int				width;
	int				height;
	dialog() : width(700), height(400) {}
	virtual char*	getfooter(char* result, const char* result_maximum) { return result; }
	virtual char*	getheader(char* result, const char* result_maximum) { return result; }
	void			view(rect rc) override;
};
struct units : dialog {
	armyinfo		a1, a2;
	controls::grid	g1, g2;
	units(controls::column* c1, controls::column* c2);
	void			view(rect rc) override;
private:
	avec			d1, d2;
};
}
void				avatar(int x, int y, const char* id);
bool				initializemap();
void				makemove(gobject* player);
gobject*			getaction(gobject* player, gobject* hero);
gobject*			getprovince(gobject* player, gobject* hero, gobject* action);
areas				hilite(rect rc);
void				render(draw::controls::control& element, rect rc);
void				report(const char* format);
areas				window(rect rc, bool disabled = false, bool hilight = false, int border = 0);
int					window(int x, int y, int width, const char* string);
int					windowb(int x, int y, int width, const char* string, int id, int param, int border = 0);
}