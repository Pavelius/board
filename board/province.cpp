#include "main.h"

struct province : gobject {

	const char*		id;
	const char*		name;
	const char*		text;
	gobject*		landscape;
	gobject*		resource;
	char			level;
	point			position;

	bsreq* getmeta() const override;

	aref<gobject*> getbonuses() const {
		return {(gobject**)&resource, 1};
	}

	point getposition() const override {
		return position;
	}

};

bsreq province_type[] = {
	BSREQ(province, id, text_type),
	BSREQ(province, name, text_type),
	BSREQ(province, text, text_type),
	BSREQ(province, level, number_type),
	BSREQ(province, position, point_type),
	{0}
};

bsreq* province::getmeta() const {
	return province_type;
}

static adat<province, 256> province_data; BSMETA(province);