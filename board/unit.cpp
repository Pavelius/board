#include "main.h"

struct unit : combatable {

	const char* id;
	const char* name;
	const char* nameof;
	const char* text;

	bsreq* getmeta() const override;

	aref<gobject*> getbonuses() const override {
		aref<gobject*> result;
		result.data = (gobject**)traits;
		result.count = zlen(traits);
		return result;
	}

};

bsreq combatable_type[] = {
	BSREQ(combatable, attack, number_type),
	BSREQ(combatable, defend, number_type),
	BSREQ(combatable, gold, number_type),
	BSREQ(combatable, gold_upkeep, number_type),
	BSREQ(combatable, support, number_type),
	BSREQ(combatable, support_upkeep, number_type),
	BSREQ(combatable, enemy_casualties, number_type),
	BSREQ(combatable, firendly_casualties, number_type),
	BSREQ(combatable, traits, number_type),
{0}
};

bsreq unit_type[] = {
	BSREQ(unit, id, text_type),
	BSREQ(unit, name, text_type),
	BSREQ(unit, nameof, text_type),
	BSREQ(unit, text, text_type),
	//BSINH(unit, combatable),
	BSREQ(combatable, attack, number_type),
	BSREQ(combatable, defend, number_type),
	BSREQ(combatable, gold, number_type),
	BSREQ(combatable, gold_upkeep, number_type),
	BSREQ(combatable, support, number_type),
	BSREQ(combatable, support_upkeep, number_type),
	BSREQ(combatable, enemy_casualties, number_type),
	BSREQ(combatable, firendly_casualties, number_type),
	BSREQ(combatable, traits, number_type),
{0}
};

bsreq* unit::getmeta() const {
	return unit_type;
}

static adat<unit, 256> unit_data; BSMETA(unit);