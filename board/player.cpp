#include "main.h"

struct player : gobject
{

	const char*		id;
	const char*		name;
	const char*		text;
	int				gold;

	xsfield* getmeta() const override;

};

xsfield player_type[] = {
	BSREQ(player, id, text_type),
	BSREQ(player, name, text_type),
	BSREQ(player, text, text_type),
	BSREQ(player, gold, number_type),
	{0}
};

xsfield* player::getmeta() const
{
	return player_type;
}

static player player_data[player_max]; BSMETA(player);