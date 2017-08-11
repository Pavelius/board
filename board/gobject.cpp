#include "xsref.h"
#include "main.h"

void gobject::add(const char* id, int value)
{
	xsref e = {getmeta(), this};
	if(e)
		e.add(id, value);
}

void gobject::set(const char* id, int value)
{
	xsref e = {getmeta(), this};
	if(e)
		e.set(id, value);
}

gobject* gobject::create(const xsfield* meta)
{
	auto m = xsbase::find(meta);
	if(!m)
		return 0;
	return (gobject*)m->add(0);
}