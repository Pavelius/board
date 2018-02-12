#include "main.h"

struct trait : gobject {

	const char* id;
	const char* name;
	const char* text;
	char attack, defend, raid;

	xsfield* getmeta() const override;

};

xsfield trait_type[] = {
	BSREQ(trait, id, text_type),
	BSREQ(trait, name, text_type),
	BSREQ(trait, text, text_type),
	BSREQ(trait, attack, number_type),
	BSREQ(trait, defend, number_type),
	BSREQ(trait, raid, number_type),
	{0}
};

xsfield* trait::getmeta() const {
	return trait_type;
}

static trait trait_data[256]; BSMETA(trait);