#include "main.h"

struct troop : gobject {

	gobject* parent;
	gobject* owner;
	gobject* province;
	gobject* moveto;

	bsreq* getmeta() const override;

	const char* getname() const override {
		return parent->getname();
	}

	const char* gettext() const override {
		return parent->gettext();
	}

	int get(const char* id) const override {
		return parent->get(id) + getbonus(id);
	}

	gobject* getprovince() const override {
		return province;
	}

	gobject* getmoveto() const override {
		return moveto;
	}

	bool isvalid() const override {
		return parent != 0;
	}

};

bsreq troop_type[] = {
	BSREQ(troop, parent, unit_type),
	BSREQ(troop, owner, player_type),
	BSREQ(troop, province, province_type),
	BSREQ(troop, moveto, province_type),
	{0}
};

bsreq* troop::getmeta() const {
	return troop_type;
}

static adat<troop, 1024> troops; BSDATA(troop, troop_type)