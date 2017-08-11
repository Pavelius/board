#include "main.h"

struct player : gobject
{

	const char*	id;
	const char*	name;
	const char*	text;
	int			gold;

	xsfield* getmeta() const override;

	const char* getid() const override
	{
		return id;
	}

	const char* getname() const override
	{
		return name;
	}

	const char* gettext() const override
	{
		return text;
	}

	int get(attributes id) const
	{
		switch(id)
		{
		case Gold: return gold;
		default: return 0;
		}
	}

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

static adat<player, player_max> objects;