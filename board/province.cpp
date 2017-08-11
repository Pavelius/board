#include "main.h"

struct province : gobject
{

	const char*		id;
	const char*		name;
	const char*		text;
	gobject*		landscape;
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

	int get(attributes id) const
	{
		return 0;
	}

};

xsfield province_type[] = {
	BSREQ(province, id, text_type),
	BSREQ(province, name, text_type),
	BSREQ(province, text, text_type),
	{0}
};

xsfield* province::getmeta() const
{
	return province_type;
}

static province objects[256];