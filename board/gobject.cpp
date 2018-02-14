#include "main.h"

void gobject::add(const char* id, int value) {
	auto pf = getmeta();
	if(pf) {
		auto p = pf->ptr(this);
		pf->set(p, pf->get(p) + value);
	}
}

void gobject::add(const char* id, int value, int index) {
	auto pf = getmeta();
	if(pf) {
		auto p = pf->ptr(this, index);
		pf->set(p, pf->get(p) + value);
	}
}

int	gobject::getindex() const {
	if(!this)
		return -1;
	auto m = bsdata::find(getmeta());
	if(!m)
		return -1;
	return m->indexof(this);
}

int	gobject::get(const char* id) const {
	auto pf = getmeta();
	if(!pf)
		return 0;
	return pf->get(pf->ptr(this));
}

int	gobject::get(const char* id, int index) const {
	auto pf = getmeta();
	if(!pf)
		return 0;
	return pf->get(pf->ptr(this, index));
}

void gobject::set(const char* id, int value) {
	auto pf = getmeta();
	if(!pf)
		return;
	pf->set(pf->ptr(this), value);
}

void gobject::set(const char* id, int value, int index) {
	if(index == -1)
		return;
	auto pf = getmeta();
	if(!pf)
		return;
	pf->set(pf->ptr(this, index), value);
}

gobject* gobject::create(const bsreq* meta) {
	auto m = bsdata::find(meta);
	if(!m)
		return 0;
	return (gobject*)m->add();
}

gobject* gobject::create(const bsreq* meta, const char* id) {
	auto m = bsdata::find(meta);
	if(!m)
		return 0;
	auto p = (gobject*)m->find(meta->find("id"), id);
	if(p)
		return p;
	p = (gobject*)m->add();
	p->set("id", id);
	return p;
}

acol<gobject> gobject::getcol(const bsreq* fields) {
	auto m = bsdata::find(fields);
	if(m)
		return {(gobject*)m->data, m->getcount(), m->size};
	return {0, 0, 0};
}

void* gobject::getarray(const char* id) const {
	auto m = getmeta();
	if(!m)
		return 0;
	auto pf = m->find(id);
	if(!pf)
		return 0;
	return (void*)pf->ptr(this);
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
	return &getcol(player_type)[index];
}

bool gobject::is(bsreq* type) const {
	return this && getmeta() == type;
}

void gobject::addloyalty(gobject* province, gobject* player, int value) {
	province->add("support", value, player->getindex());
}