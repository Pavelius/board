#include "main.h"

struct unit : gobject
{

	const char*	id;
	const char*	name;
	const char*	text;
	char		attack, raid, defend;

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
		case Attack: return attack;
		case Raid: return raid;
		case Defence: return defend;
		default: return 0;
		}
	}

};

static adat<unit, 1024> objects;