#include "main.h"

struct landscape : gobject {

	const char*		id;
	const char*		name;
	const char*		text;

	bsreq* getmeta() const override;

};

bsreq landscape_type[] = {
	BSREQ(landscape, id, text_type),
	BSREQ(landscape, name, text_type),
	BSREQ(landscape, text, text_type),
{0}
};

bsreq* landscape::getmeta() const {
	return landscape_type;
}

static adat<landscape, 32> landscape_data; BSMETA(landscape);