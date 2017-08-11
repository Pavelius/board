#include "xsref.h"
#include "main.h"

void gobject::add(const char* id, int value)
{
	xsref e = {getmeta(), this};
	if(e)
		e.add(id, value);
}

int	gobject::getindex() const
{
	if(!this)
		return 0;
	auto m = xsbase::find(getmeta());
	if(!m)
		return 0;
	return m->indexof(this);
}

int	gobject::get(const char* id, int index) const
{
	xsref e = {getmeta(), (void*)this};
	if(!e)
		return 0;
	return e.get(id, index);
}

void gobject::set(const char* id, int value, int index)
{
	xsref e = {getmeta(), this};
	if(e)
		e.set(id, value, index);
}

gobject* gobject::create(const xsfield* meta)
{
	auto m = xsbase::find(meta);
	if(!m)
		return 0;
	return (gobject*)m->add(0);
}

gobject* gobject::create(const xsfield* meta, const char* id)
{
	auto m = xsbase::find(meta);
	if(!m)
		return 0;
	auto xr = m->find("id", id);
	if(xr)
		return (gobject*)xr.object;
	xr.object = m->add(0);
	xr.fields = meta;
	xr.set("id", (int)id, 0);
	return (gobject*)xr.object;
}

int gobject::getsupport(gobject* player) const
{
	return get("support", player->getindex());
}

void gobject::addsupport(gobject* player, int value)
{
	set("support", getsupport(player) + value, player->getindex());
}

acol<gobject> getcollection(const xsfield* fields)
{
	auto m = xsbase::find(fields);
	if(m)
		return {(gobject*)m->data, m->count, m->size};
	return {0, 0, 0};
}