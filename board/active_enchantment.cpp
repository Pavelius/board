#include "main.h"

struct active_enchantment : gobject {
	gobject* type;
	gobject* target;

	operator bool() const {
		return type != 0;
	}

	int get(const char* id) const override {
		return type->get(id);
	}

	bsreq* getmeta() const override;

};

bsreq active_enchantment_type[] = {
	BSREQ(active_enchantment, type, enchantment_type),
	BSREQ(active_enchantment, target, player_type),
	{0}
};

bsreq* active_enchantment::getmeta() const {
	return active_enchantment_type;
}

static adat<active_enchantment, 256> active_enchantment_data; BSMETA(active_enchantment);

int gobject::getbonus(const char* id) const {
	auto result = 0;
	for(auto& e : active_enchantment_data) {
		if(!e.target)
			continue;
		if(!((e.target == this)
			|| (e.target->is(province_type) && e.target == getprovince())))
			continue;
		result += e.get(id);
	}
	return result;
}