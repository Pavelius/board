#include "main.h"

struct combatside {

	adat<gobject*, 32> units;
	gobject* general;

	combatside(gobject* province, gobject* owner) {
		// Get all units in province by one owner
		for(auto e : gobject::getcol(troop_type)) {
			if(!e.isvalid())
				continue;
			if(e.getowner() != owner)
				continue;
			if(e.getprovince() != province)
				continue;
			units.add(&e);
		}
		// Get all heroes in province and choose one best matched
		for(auto e : gobject::getcol(hero_type)) {
			if(!e.isvalid())
				continue;
			if(e.getowner() != owner)
				continue;
			if(e.getprovince() != province)
				continue;
			general = &e;
			break;
		}
	}

	operator bool() const {
		return units.getcount();
	}

	int get(int (gobject::*proc)() const) const {
		auto r = 0;
		if(general)
			r += (general->*proc)();
		for(auto p : units)
			r += (p->*proc)();
		return r;
	}

};

void calculate(gobject* attacker_player, gobject* defender_player, gobject* province) {
	combatside attackers(province, attacker_player);
	combatside defenders(province, defender_player);
}