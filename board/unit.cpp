#include "main.h"

struct unit : gobject {

	const char*	id;
	const char*	name;
	const char*	text;
	char		attack, raid, defence;
	gobject*	bonus[5];
	gobject*	penalty[5];

	xsfield* getmeta() const override;

	aref<gobject*> getbonuses() const override {
		return {(gobject**)bonus, zlen(bonus)};
	}

	aref<gobject*> getpenalty() const override {
		return {(gobject**)penalty, zlen(bonus)};
	}

};

xsfield unit_type[] = {
	BSREQ(unit, id, text_type),
	BSREQ(unit, name, text_type),
	BSREQ(unit, text, text_type),
	BSREQ(unit, attack, number_type),
	BSREQ(unit, defence, number_type),
	BSREQ(unit, raid, number_type),
	{0}
};

xsfield* unit::getmeta() const {
	return unit_type;
}

static unit unit_data[256];  BSMETA(unit);