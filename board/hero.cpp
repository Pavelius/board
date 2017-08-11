#include "main.h"

struct hero : gobject
{

	const char*	id;
	const char*	name;
	const char*	text;
	gobject*	traits[5];

	xsfield* getmeta() const override;

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
		auto result = 0;
		for(auto e : gettraits())
			result += e->get(id);
		return result;
	}

	aref<gobject*> gettraits() const override
	{
		return {(gobject**)traits, zlen(traits)};
	}

};

xsfield hero_type[] = {
	BSREQ(hero, id, text_type),
	BSREQ(hero, name, text_type),
	BSREQ(hero, text, text_type),
	{0}
};

xsfield* hero::getmeta() const
{
	return hero_type;
}

static hero hero_data[256];  BSMETA(hero);