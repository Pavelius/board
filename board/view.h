#include "draw.h"
#include "main.h"

#pragma once

struct gui_info {
	unsigned char border;
	unsigned char opacity, opacity_disabled;
	short window_width;
	short padding;
};
extern gui_info gui;

namespace draw {
void			menu();
void			tooltips(int x, int y, int width, iflags align, const char* format, ...);
areas			window(rect rc, bool disabled = false);
int				window(int x, int y, int width, const char* string);
}