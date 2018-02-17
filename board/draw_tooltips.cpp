#include "crt.h"
#include "command.h"
#include "view.h"

using namespace draw;


//void tooltips(rect rc, const char* format, ...) {
//	if(hot::key != InputIdle)
//		return;
//	tooltips_rect = rc;
//	szprintv(tooltips_text, format, xva_start(format));
//}


//void tooltips(const char* format, ...) {
//	if(hot::key != InputIdle)
//		return;
//	int x1 = hot::mouse.x;
//	int y1 = hot::mouse.y + 24;
//	tooltips_rect = {x1, y1, x1 + 400, y1};
//	szprintv(tooltips_text, format, xva_start(format));
//}