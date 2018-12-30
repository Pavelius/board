#include "main.h"

struct action : gobject, bsenum {
	const char*		nameact;
	char			attack, defend, gold, recruit, support, upgrade;
	char			conquer, placeable;
	bsreq*			getmeta() const override;
};
bsreq action_type[] = {
	BSREQ(action, id, text_type),
	BSREQ(action, name, text_type),
	BSREQ(action, text, text_type),
	BSREQ(action, attack, number_type),
	BSREQ(action, defend, number_type),
	BSREQ(action, gold, number_type),
	BSREQ(action, recruit, number_type),
	BSREQ(action, support, number_type),
	BSREQ(action, upgrade, number_type),
	BSREQ(action, conquer, number_type),
	BSREQ(action, placeable, number_type),
	BSREQ(action, nameact, text_type),
{0}
};

bsreq* action::getmeta() const {
	return action_type;
}

static adat<action, 32> action_data; BSMETA(action);