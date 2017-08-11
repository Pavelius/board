#include "main.h"

struct province : gobject
{

	const char*		id;
	const char*		name;
	const char*		text;
	gobject*		landscape;
	gobject*		resource;
	short			support[player_max];

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

	aref<gobject*> getbonuses() const
	{
		return {(gobject**)&resource, 1};
	}

};

xsfield province_type[] = {
	BSREQ(province, id, text_type),
	BSREQ(province, name, text_type),
	BSREQ(province, text, text_type),
	BSREQ(province, support, number_type),
	{0}
};

xsfield* province::getmeta() const
{
	return province_type;
}

static province province_data[256]; BSMETA(province);