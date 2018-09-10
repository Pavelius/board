#include "main.h"

struct player : gobject {

	const char*	id;
	const char*	name;
	const char*	nameof;
	const char*	text;
	int			gold;

	bsreq* getmeta() const override;

	void refresh_resource() {
		for(auto& e : getcol(province_type)) {
			if(!e)
				continue;
			if(e.getowner() != this)
				continue;
		}
	}

	void refresh() override {
		refresh_resource();
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