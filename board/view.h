#include "draw.h"
#include "main.h"

#pragma once

struct gui_info {
	unsigned char border;
	unsigned char opacity, opacity_disabled, opacity_hilighted;
	short button_width, window_width, tips_width, hero_width, hero_window_width, hero_window_border, control_border;
	short padding;
};
extern gui_info gui;

namespace draw {
void avatar(int x, int y, const char* id);
bool initializemap();
void report(const char* format);
areas window(rect rc, bool disabled = false, bool hilight = false, int border = 0);
int window(int x, int y, int width, const char* string);
}