#include "main.h"

struct player : gobject {

	const char*	id;
	const char*	name;
	const char*	nameof;
	const char*	text;
	int			gold;

	bsreq* getmeta() const override;

	void refresh_resource(gobject* resource) {
		auto available = getcount(province_type, &gobject::getresource, resource);
		auto used = getcount(troop_type, &gobject::getresource, resource);
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