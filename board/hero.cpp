#include "main.h"

struct hero : gobject {

	const char*	id;
	const char*	name;
	const char*	text;
	const char*	avatar;
	gobject* traits[5];
	gobject* tactic;

	bsreq* getmeta() const override;

	int get(const char* id) const override {
		auto result = 0;
		for(auto e : getbonuses()) {
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

	const char* getavatar() const override {
		return avatar;
	}

	aref<gobject*> getbonuses() const override {
		return {(gobject**)traits, zlen(traits)};
	}

};

bsreq hero_type[] = {
	BSREQ(hero, id, text_type),
	BSREQ(hero, name, text_type),
	BSREQ(hero, text, text_type),
	BSREQ(hero, avatar, text_type),
	BSREQ(hero, tactic, tactic_type),
	BSREQ(hero, traits, trait_type),
{0}
};

bsreq* hero::getmeta() const {
	return hero_type;
}

static adat<hero, 256> heros; BSDATA(hero, hero_type)