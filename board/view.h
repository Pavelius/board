#include "draw.h"
#include "main.h"

#pragma once

struct gui_info {
	unsigned char border;
	unsigned char opacity, opacity_disabled;
	short window_width, tips_width, hero_width;
	short padding;
};
extern gui_info gui;

namespace draw {
void			avatar(int x, int y, const char* id);
bool			initializemap();
void			menu();
void			report(const char* format);
void			tooltips(int x, int y, int width, iflags align, const char* format, ...);
areas			window(rect rc, bool disabled = false);
int				window(int x, int y, int width, const char* string);
}