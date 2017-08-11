#include "main.h"

struct troop : gobject
{

	gobject*	parent;
	gobject*	owner;
	gobject*	province;
	gobject*	moveto;

	xsfield* getmeta() const override;

	const char* getname() const override
	{
		return parent->getname();
	}

	const char* gettext() const override
	{
		return parent->gettext();
	}

	int get(attributes id) const override
	{
		return parent->get(id);
	}

	gobject* getprovince() const override
	{
		return province;
	}

	gobject* getmoveto() const override
	{
		return moveto;
	}

};

xsfield troop_type[] = {
	BSREQ(troop, parent, unit_type),
	BSREQ(troop, owner, player_type),
	BSREQ(troop, province, province_type),
	BSREQ(troop, moveto, province_type),
	{0}
};

xsfield* troop::getmeta() const
{
	return troop_type;
}

static troop troop_data[1024]; BSMETA(troop)