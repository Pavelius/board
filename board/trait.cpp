#include "main.h"

struct trait : combatable, bsenum {
	bsreq*			getmeta() const override;
};

bsreq trait_type[] = {
	BSREQ(trait, id, text_type),
	BSREQ(trait, name, text_type),
	BSREQ(trait, text, text_type),
	BSREQ(trait, attack, number_type),
	BSREQ(trait, defend, number_type),
	BSREQ(trait, gold, number_type),
	BSREQ(trait, gold_upkeep, number_type),
	BSREQ(trait, support, number_type),
	BSREQ(trait, support_upkeep, number_type),
	BSREQ(trait, traits, number_type),
	BSREQ(trait, enemy_casualties, number_type),
	BSREQ(trait, firendly_casualties, number_type),
{}};
bsreq* trait::getmeta() const {
	return trait_type;
}

static adat<trait, 128> trait_data; BSMETA(trait)