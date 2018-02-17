#include "draw.h"
#include "main.h"

#pragma once

struct gui_info {
	unsigned char border;
	unsigned char opacity, opacity_disabled;
	short window_width;
	short tips_width;
	short padding;
};
extern gui_info gui;

namespace draw {
bool			initializemap();
void			menu();
void			report(const char* format);
void			tooltips(int x, int y, int width, iflags align, const char* format, ...);
areas			window(rect rc, bool disabled = false);
int				window(int x, int y, int width, const char* string);
}