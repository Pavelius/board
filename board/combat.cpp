#include "main.h"

struct parcipant {
	gobject*	unit;
	char		wounds;

	parcipant() : unit(0), wounds(0) {
	}

	parcipant(gobject* unit) : unit(unit), wounds(unit->get("wounds")) {
	}

};

struct combatside {

	adat<parcipant, 32>	units;
	char				roll_black, roll_red, black, red, critical, block;

	combatside() : black(0), red(0), critical(0), block(0) {
	}

	operator bool() const {
		return units.getcount();
	}

	void start() {
		roll_black = roll_red = black = red = critical = block = 0;
		for(auto p : units)
			roll_black += p.unit->get("black");
		for(auto p : units)
			roll_red += p.unit->get("red");
	}

	void roll_tactic() {
		switch(xrand(1, 6)) {
		case 1: block += 1; break;
		case 2: block += 1; break;
		case 3: critical += 1; break;
		case 4: critical += 1; break;
		case 5: block += 2; break;
		case 6: critical += 2; break;
		}
	}

	void roll_dice(char& value) {
		switch(xrand(1, 6)) {
		case 3: value += 1; break;
		case 4: value += 1; break;
		case 5: critical += 1; break;
		case 6: roll_tactic(); break;
		}
	}

	void rolling() {
		for(int i = 0; i < roll_black; i++)
			roll_dice(black);
		roll_black = 0;
		for(int i = 0; i < roll_red; i++)
			roll_dice(red);
		roll_red = 0;
	}

	static int compare_units(const void* p1, const void* p2) {
		auto e1 = (parcipant*)p1;
		auto e2 = (parcipant*)p2;
		if(e1->wounds == e2->wounds)
			return e1->unit->get("wounds") - e2->unit->get("wounds");
		return e1->wounds - e2->wounds;
	}

	void normalize() {
		qsort(units.data, sizeof(units.data) / sizeof(units.data[0]), sizeof(units[0]), compare_units);
	}

};