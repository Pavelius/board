#include "main.h"

struct tactic : gobject {
	
	const char* id;
	const char* name;
	const char* text;
	char strenght, enemy_casualty, friendly_casualty;

	bsreq* getmeta() const override;

};

bsreq tactic_type[] = {
	BSREQ(tactic, id, text_type),
	BSREQ(tactic, name, text_type),
	BSREQ(tactic, text, text_type),
	BSREQ(tactic, strenght, number_type),
	BSREQ(tactic, enemy_casualty, number_type),
	BSREQ(tactic, friendly_casualty, number_type),
	{0}
};

bsreq* tactic::getmeta() const {
	return tactic_type;
}

static adat<tactic, 3> tactics; BSDATA(tactic, tactic_type)