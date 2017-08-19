#include "main.h"

struct active_enchantment : gobject
{

	gobject*	type;
	gobject*	target;

	operator bool() const
	{
		return type != 0;
	}

	int get(attributes id) const
	{
		return type->get(id);
	}

	xsfield* getmeta() const override;

};

xsfield active_enchantment_type[] = {
	BSREQ(active_enchantment, type, enchantment_type),
	BSREQ(active_enchantment, target, reference_type),
	{0}
};

xsfield* active_enchantment::getmeta() const
{
	return active_enchantment_type;
}

static active_enchantment active_enchantment_data[256]; BSMETA(active_enchantment);

int gobject::getbonus(attributes id) const
{
	auto result = 0;
	for(unsigned i = 0; i < active_enchantment_manager.count; i++)
	{
		auto& e = active_enchantment_data[i];
		if(!e.target)
			continue;
		if(!((e.target == this)
			|| (e.target->getmeta()==province_type && e.target==getprovince())))
			continue;
		result += e.get(id);
	}
	return result;
}