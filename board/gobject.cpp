#include "main.h"

static int compare(const void* v1, const void* v2) {
	auto e1 = *((gobject**)v1);
	auto e2 = *((gobject**)v2);
	return strcmp(e1->getname(), e2->getname());
}

void gobject::sort(gobject** result, unsigned count) {
	qsort(result, count, sizeof(result[0]), compare);
}

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

int gobject::fix(tipinfo* ti, int value) const {
	if(ti && value) {
		char temp[260];
		zcpy(temp, getname());
		szupper(temp, 1);
		szprints(zend(ti->result), ti->result_max, ti->text, value, temp);
		if(ti->separator)
			zcat(ti->result, ti->separator);
	}
	return value;
}

int	gobject::get(const char* id) const {
	auto pf = getmeta()->find(id);
	if(!pf)
		return 0;
	return pf->get(pf->ptr(this));
}

const char*	gobject::gets(const char* id) const {
	auto pf = getmeta()->find(id, text_type);
	if(!pf)
		return "";
	return (const char*)pf->get(pf->ptr(this));
}

int	gobject::get(const char* id, int index) const {
	auto pf = getmeta()->find(id);
	if(!pf)
		return 0;
	return pf->get(pf->ptr(this, index));
}

void gobject::set(const char* id, int value) {
	auto pf = getmeta()->find(id);
	if(!pf)
		return;
	pf->set(pf->ptr(this), value);
}

void gobject::set(const char* id, int value, int index) {
	if(index == -1)
		return;
	auto pf = getmeta()->find(id);
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
	auto p = (gobject*)m->find(meta->getkey(), id);
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

gobject* gobject::find(bsreq* meta, const char* id) {
	auto m = bsdata::find(meta);
	if(!m)
		return 0;
	return (gobject*)m->find(meta->getkey(), id);
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

bool gobject::is(bsreq* type) const {
	return this && getmeta() == type;
}

void gobject::actv(char* result, const char* format, const char* param) const {
	logs::driver driver;
	driver.name = getname();
	driver.gender = getgender();
	auto p = getprovince();
	if(p)
		driver.province = p->getname();
	driver.printv(result, result + 4096, format, param);
}

void gobject::act(char* result, const char* format, ...) const {
	actv(result, format, xva_start(format));
}

unsigned gobject::getobjects(bsreq* type, gobject** result, unsigned maximum, gobject* province) const {
	auto ps = result;
	auto pe = result + maximum;
	for(auto& e : getcol(type)) {
		if(ps >= pe)
			break;
		if(!e.isvalid())
			continue;
		if(e.getowner() != this)
			continue;
		if(province && e.getprovince() != province)
			continue;
		*ps++ = &e;
	}
	return ps - result;
}

char* gobject::getpresent(char* result, unsigned maximum, gobject** objects, unsigned count) {
	stringcreator sc;
	auto ps = result;
	auto pe = result + maximum;
	ps[0] = 0;
	int count_in_row = 1;
	for(unsigned i = 0; i < count; i++) {
		if(i < count - 1 && strcmp(objects[i]->getname(), objects[i + 1]->getname())==0) {
			count_in_row++;
			continue;
		}
		if(ps != result) {
			sc.prints(ps, pe, "\n");
			ps = zend(ps);
		}
		if(count_in_row == 1)
			sc.prints(ps, pe, objects[i]->getname());
		else
			sc.prints(ps, pe, msgcombat.squads, count_in_row, objects[i]->getnameof());
		szupper(ps, 1);
		ps = zend(ps);
		count_in_row = 1;
	}
	return result;
}

void gobject::addbutton(char* result, const char* result_max, const char* name, const char* label) {
	szprints(result, result_max, "\n$(%1 label=\"%2\")", name, label);
}