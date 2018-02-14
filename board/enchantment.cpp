#include "main.h"

struct enchantment : gobject {

	const char*	id;
	const char*	name;
	const char*	text;
	char		attack, defend, raid;

	bsreq* getmeta() const override;

};

bsreq enchantment_type[] = {
	BSREQ(enchantment, id, text_type),
	BSREQ(enchantment, name, text_type),
	BSREQ(enchantment, text, text_type),
	BSREQ(enchantment, attack, number_type),
	BSREQ(enchantment, defend, number_type),
	BSREQ(enchantment, raid, number_type),
	{0}
};

bsreq* enchantment::getmeta() const {
	return enchantment_type;
}

static enchantment enchantment_data[256]; BSMETA(enchantment);