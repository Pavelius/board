#include "main.h"

struct province : gobject {

	const char*		id;
	const char*		name;
	const char*		text;
	gobject*		landscape;
	gobject*		resource;
	gobject*		owner;
	char			level;
	point			position;

	bsreq* getmeta() const override;

	aref<gobject*> getbonuses() const {
		aref<gobject*> result;
		result.data = (gobject**)&result;
		result.count = 1;
		return result;
	}

	point getposition() const override {
		return position;
	}

};

bsreq province_type[] = {
	BSREQ(province, id, text_type),
	BSREQ(province, name, text_type),
	BSREQ(province, text, text_type),
	BSREQ(province, resource, resource_type),
	BSREQ(province, owner, player_type),
	BSREQ(province, landscape, landscape_type),
	BSREQ(province, level, number_type),
	BSREQ(province, position, point_type),
	{0}
};

bsreq* province::getmeta() const {
	return province_type;
}

static adat<province, 256> province_data; BSMETA(province);