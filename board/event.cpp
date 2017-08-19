#include "main.h"

struct event : gobject
{

	const char*	id;
	const char*	name;
	const char*	text;
	gobject*	target;
	char		attack, defend, raid;

	xsfield* getmeta() const override;

	bool isvalid() const
	{
		return id != 0;
	}

};

xsfield event_type[] = {
	BSREQ(event, id, text_type),
	BSREQ(event, name, text_type),
	BSREQ(event, text, text_type),
	BSREQ(event, target, reference_type),
	BSREQ(event, attack, number_type),
	BSREQ(event, defend, number_type),
	BSREQ(event, raid, number_type),
	{0}
};

xsfield* event::getmeta() const
{
	return event_type;
}

static event event_data[256]; BSMETA(event);

int	gobject::getbonus(attributes id) const
{
	auto result = 0;
	for(unsigned i = 0; i < event_manager.count; i++)
	{
		auto& e = event_data[i];
		if(e.target != this)
			continue;
		result += get(id);
	}
	return result;
}