#include "main.h"

struct resource : gobject, bsenum {
	int				cost;
	int				total;
	bsreq* getmeta() const override;
};

bsreq resource_type[] = {
	BSREQ(resource, id, text_type),
	BSREQ(resource, name, text_type),
	BSREQ(resource, text, text_type),
	BSREQ(resource, cost, number_type),
	BSREQ(resource, total, number_type),
{0}
};

bsreq* resource::getmeta() const {
	return resource_type;
}

static adat<resource, 32> resource_data; BSMETA(resource);