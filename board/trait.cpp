#include "main.h"

struct trait : combatable {

	const char* id;
	const char* name;
	const char* text;

	bsreq* getmeta() const override;

};

bsreq trait_type[] = {
	BSREQ(trait, id, text_type),
	BSREQ(trait, name, text_type),
	BSREQ(trait, text, text_type),
	BSREQ(combatable, attack, number_type),
	BSREQ(combatable, defend, number_type),
	BSREQ(combatable, gold, number_type),
	BSREQ(combatable, gold_upkeep, number_type),
	BSREQ(combatable, support, number_type),
	BSREQ(combatable, support_upkeep, number_type),
	BSREQ(combatable, traits, number_type),
	BSREQ(combatable, enemy_casualties, number_type),
	BSREQ(combatable, firendly_casualties, number_type),
{0}
};

bsreq* trait::getmeta() const {
	return trait_type;
}

static adat<trait, 128> traits; BSDATA(trait, trait_type)