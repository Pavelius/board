#include "view.h"

using namespace draw::controls;

const char* grid::getname(char* result, const char* result_max, int line, int column) const {
	auto& e = columns[column];
	auto p = *((gobject**)source.get(line));
	return (const char*)p->get(e.id);
}