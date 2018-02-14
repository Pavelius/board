#include "main.h"

gobject* create(bsreq* type, const char* id, const char* name, const char* text = 0) {
	auto p = gobject::create(type, id);
	p->set("name", name);
	p->set("text", text);
	return p;
}

int main() {
	auto pr = create(player_type, "red", "Империя");
	auto pg = create(player_type, "green", "Орки");
	create(unit_type, "nordlings", "Ополчение северян");
	create(unit_type, "southlings", "Ополчение южан");
	create(unit_type, "orcs", "Орки");
}