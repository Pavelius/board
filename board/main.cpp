#include "main.h"

gobject* create(bsreq* type, const char* id, const char* name, const char* text = 0) {
	auto p = gobject::create(type, id);
	p->set("name", name);
	p->set("text", text);
	return p;
}

int main() {
	auto pr = create(player_type, "red", "�������");
	auto pg = create(player_type, "green", "����");
	create(unit_type, "nordlings", "��������� �������");
	create(unit_type, "southlings", "��������� ����");
	create(unit_type, "orcs", "����");
}