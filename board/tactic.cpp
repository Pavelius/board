#include "main.h"

struct tactic : gobject, bsenum {
	
	char strenght, enemy_casualties, friendly_casualties;

	bsreq* getmeta() const override;

};

bsreq tactic_type[] = {
	BSREQ(tactic, id, text_type),
	BSREQ(tactic, name, text_type),
	BSREQ(tactic, text, text_type),
	BSREQ(tactic, strenght, number_type),
	BSREQ(tactic, enemy_casualties, number_type),
	BSREQ(tactic, friendly_casualties, number_type),
	{0}
};

bsreq* tactic::getmeta() const {
	return tactic_type;
}

static adat<tactic, 3> tactic_data; BSMETA(tactic)