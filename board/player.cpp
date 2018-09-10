#include "main.h"

struct player : gobject {

	const char*	id;
	const char*	name;
	const char*	nameof;
	const char*	text;
	int			gold;

	bsreq* getmeta() const override;

	int get(gobject* resource, bsreq* type) {
		auto result = 0;
		for(auto& e : getcol(type)) {
			if(!e)
				continue;
			if(e.getowner() != this)
				continue;
			if(e.getresource() == resource)
				result++;
		}
		return result;
	}

	void refresh_resource(gobject* resource) {
		auto available = get(resource, province_type);
		auto used = get(resource, troop_type);
		gold += resource->get("gold") * (available - used);
	}

	void refresh() override {
		for(auto& e : getcol(resource_type))
			refresh_resource(&e);
	}

};

bsreq player_type[] = {
	BSREQ(player, id, text_type),
	BSREQ(player, name, text_type),
	BSREQ(player, nameof, text_type),
	BSREQ(player, text, text_type),
	BSREQ(player, gold, number_type),
	{0}
};

bsreq* player::getmeta() const {
	return player_type;
}

static adat<player, player_max> player_data; BSMETA(player);