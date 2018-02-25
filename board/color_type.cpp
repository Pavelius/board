#include "color.h"
#include "bsreq.h"

bsreq color_type[] = {
	BSREQ(color, r, number_type),
	BSREQ(color, g, number_type),
	BSREQ(color, b, number_type),
	BSREQ(color, a, number_type),
	{0}
};