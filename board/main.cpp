#include "main.h"

int main()
{
	auto u1 = gobject::create(unit_type, "cavalry");
	u1->set("name", "Кавалерия");
	u1->set("text", "Мощная сила эффективная в атаке.");
	auto u2 = gobject::create(player_type);
}