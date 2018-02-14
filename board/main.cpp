#include "main.h"

gobject* create(bsreq* type, const char* id, const char* name, const char* text = 0) {
	auto p = gobject::create(type, id);
	p->set("name", name);
	p->set("text", text);
	return p;
}

static gobject* create_troop(const char* id, gobject* owner, gobject* province) {
	auto p = gobject::create(troop_type);
	p->set("owner", owner);
	p->set("province", province);
	return p;
}

bool cpp_parsemsg(const char* url, const char* out_url);

int main() {
	bsdata::read("script/game.txt");
	cpp_parsemsg("board/messages.h", "board/messages.cpp");
	auto red = create(player_type, "red", "Империя");
	auto green = create(player_type, "green", "Орки");
	create(unit_type, "nordlings", "Ополчение северян");
	create(unit_type, "southlings", "Ополчение южан");
	create(unit_type, "orcs", "Орки");
	auto black_wood = create(province_type, "black_wood", "Черный лес");
	create_troop("nordlings", red, black_wood);
	create_troop("nordlings", red, black_wood);
	create_troop("orcs", green, black_wood);
	create_troop("orcs", green, black_wood);
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}