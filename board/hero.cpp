#include "main.h"

struct hero : gobject {

	const char*	id;
	const char*	name;
	const char*	text;
	gobject*	traits[5];

	xsfield* getmeta() const override;

	int get(const char* id) const override {
		auto result = 0;
		for(auto e : gettraits()) {
			if(!e)
				break;
			result += e->get(id);
		}
		result += getbonus(id);
		return result;
	}

	const char* getname() const override {
		return name;
	}

	aref<gobject*> gettraits() const override {
		return {(gobject**)traits, zlen(traits)};
	}

};

xsfield hero_type[] = {
	BSREQ(hero, id, text_type),
	BSREQ(hero, name, text_type),
	BSREQ(hero, text, text_type),
	BSREQ(hero, traits, trait_type),
	{0}
};

xsfield* hero::getmeta() const {
	return hero_type;
}

static hero hero_data[256];  BSMETA(hero);