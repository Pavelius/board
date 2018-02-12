#include "xsref.h"
#include "main.h"

void gobject::add(const char* id, int value) {
	xsref e = {getmeta(), this};
	if(e)
		e.add(id, value);
}

void gobject::add(const char* id, int value, int index) {
	xsref e = {getmeta(), this};
	if(e)
		e.set(id, e.get(id, index) + value, index);
}

int	gobject::getindex() const {
	if(!this)
		return -1;
	auto m = xsbase::find(getmeta());
	if(!m)
		return -1;
	return m->indexof(this);
}

int	gobject::get(const char* id) const {
	xsref e = {getmeta(), (void*)this};
	if(!e)
		return 0;
	return e.get(id);
}

int	gobject::get(const char* id, int index) const {
	xsref e = {getmeta(), (void*)this};
	if(!e)
		return 0;
	return e.get(id, index);
}

void gobject::set(const char* id, int value) {
	xsref e = {getmeta(), this};
	if(e)
		e.set(id, value);
}

gobject* gobject::create(const xsfield* meta) {
	auto m = xsbase::find(meta);
	if(!m)
		return 0;
	return (gobject*)m->add(0);
}

gobject* gobject::create(const xsfield* meta, const char* id) {
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

acol<gobject> getcollection(const xsfield* fields) {
	auto m = xsbase::find(fields);
	if(m)
		return {(gobject*)m->data, m->count, m->size};
	return {0, 0, 0};
}

void* gobject::getarray(const char* id) const {
	auto pm = getmeta();
	if(!pm)
		return 0;
	auto pf = pm->find(id);
	if(!pf)
		return 0;
	return (void*)pf->get(this);
}

gobject* gobject::getloyalty() const {
	auto p = (short*)getarray("support");
	if(!p)
		return 0;
	int index = 0;
	for(int i = 0; i < player_max; i++) {
		if(p[index] < p[i])
			index = i;
	}
	if(p[index] < 10)
		return 0;
	return &getcollection(player_type)[index];
}

bool gobject::isoccupied() const {
	for(auto u : getcollection(troop_type)) {
		if(u.getprovince() == this)
			return getloyalty() != u.getowner();
	}
	return false;
}

bool gobject::is(xsfield* type) const {
	return this && getmeta() == type;
}

void gobject::addloyalty(gobject* province, gobject* player, int value) {
	province->add("support", value, player->getindex());
}