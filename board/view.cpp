#include "view.h"

using namespace draw;

void draw::menu() {
	draw::linw = 5.0;
	while(ismodal()) {
		draw::rectf({0, 0, draw::getwidth(), draw::getheight()}, colors::form);
		draw::line(10, 10, 100, 100);
		auto id = input();
	}
}