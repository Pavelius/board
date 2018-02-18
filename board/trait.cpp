#include "main.h"

struct trait : gobject {

	const char* id;
	const char* name;
	const char* text;
	char attack, defend, raid;
	char enemy_casualties, friendly_casualties;
	char gold, gold_upkeep, support, support_upkeep;

	bsreq* getmeta() const override;

};

bsreq trait_type[] = {
	BSREQ(trait, id, text_type),
	BSREQ(trait, name, text_type),
	BSREQ(trait, text, text_type),
	BSREQ(trait, attack, number_type),
	BSREQ(trait, defend, number_type),
	BSREQ(trait, raid, number_type),
	BSREQ(trait, gold, number_type),
	BSREQ(trait, gold_upkeep, number_type),
	BSREQ(trait, support, number_type),
	BSREQ(trait, support_upkeep, number_type),
	BSREQ(trait, enemy_casualties, number_type),
	BSREQ(trait, friendly_casualties, number_type),
	{0}
};

bsreq* trait::getmeta() const {
	return trait_type;
}

static adat<trait, 128> traits; BSDATA(trait, trait_type)