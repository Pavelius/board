#include "aref.h"
#include "adat.h"
#pragma once

enum attributes : char {
	Attack, Defence, Mouring, Movement, Raid, Gold, Support,
};
struct gobject
{
	virtual int					get(attributes id) const { return 0; }
	virtual const char*			getavatar() const { return ""; }
	virtual aref<gobject*>		getbonus() const { return {0, 0}; }
	virtual const char*			getid() const { return ""; }
	virtual const char*			getname() const { return ""; }
	virtual gobject*			getowner() const { return 0; }
	virtual aref<gobject*>		getpenalty() const { return {0, 0}; }
	virtual aref<gobject*>		getprovinces() const { return {0, 0}; }
	virtual int					getsupport(gobject* player) const { return 0; }
	virtual const char*			gettext() const { return ""; }
	virtual aref<gobject*>		gettraits() const { return {0, 0}; }
};