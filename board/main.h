#include "aref.h"
#include "adat.h"
#pragma once

enum combatprops : char {
	Attack, Defence, Mouring, Movement, Raid
};
enum adminprops : char {
	Gold, Support
};
struct gobject
{
	virtual int					get(combatprops id) const { return 0; }
	virtual int					get(adminprops id) const { return 0; }
	virtual const char*			getid() const { return ""; }
	virtual const char*			getname() const { return ""; }
	virtual gobject*			getowner() const { return 0; }
	virtual aref<gobject*>		getprovinces() const { return {0, 0}; }
	virtual int					getsupport(gobject* player) const { return 0; }
	virtual const char*			gettext() const { return ""; }
	virtual aref<gobject*>		gettraits() const { return {0, 0}; }
};