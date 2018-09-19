#include "view.h"

using namespace draw;
using namespace draw::dialogs;

units::units(controls::column* c1, controls::column* c2) : d1(a1), d2(a2),
g1(d1, c1), g2(d2, c2) {
}

void units::view(rect rc) {
	dialog::view(rc);
	auto x12 = rc.x1 + (rc.width() - gui_data.padding) / 2;
	auto x21 = rc.x1 + (rc.width() - gui_data.padding) / 2 + gui_data.padding;
	g1.view({rc.x1, rc.y1, x12, rc.y2});
	g1.view({x21, rc.y1, rc.x2, rc.y2});
}