#include "main.h"

struct player : gobject {

	const char*		id;
	const char*		name;
	const char*		text;
	int				gold;

	bsreq* getmeta() const override;

};

bsreq player_type[] = {
	BSREQ(player, id, text_type),
	BSREQ(player, name, text_type),
	BSREQ(player, text, text_type),
	BSREQ(player, gold, number_type),
	{0}
};

bsreq* player::getmeta() const {
	return player_type;
}

static adat<player, player_max> players; BSDATA(player, player_type);