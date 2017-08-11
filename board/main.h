#include "aref.h"
#include "adat.h"
#include "crt.h"
#include "xsbase.h"

#pragma once

const int player_max = 8;

enum attributes : char {
	Attack, Defence, Mouring, Movement, Raid, Gold, Support,
};
struct gobject
{
	void						add(const char* id, int value);
	static gobject*				create(const xsfield* meta);
	virtual int					get(attributes id) const { return 0; }
	virtual const char*			getavatar() const { return ""; }
	virtual aref<gobject*>		getbonus() const { return {0, 0}; }
	virtual const char*			getid() const { return ""; }
	virtual xsfield*			getmeta() const = 0;
	virtual gobject*			getmoveto() const { return 0; }
	virtual const char*			getname() const { return ""; }
	virtual gobject*			getowner() const { return 0; }
	virtual gobject*			getprovince() const { return 0; }
	virtual aref<gobject*>		getpenalty() const { return {0, 0}; }
	virtual aref<gobject*>		getprovinces() const { return {0, 0}; }
	virtual int					getsupport(gobject* player) const { return 0; }
	virtual const char*			gettext() const { return ""; }
	virtual aref<gobject*>		gettraits() const { return {0, 0}; }
	void						set(const char* id, int value);
	void						set(const char* id, gobject* value) { set(id, (int)value); }
};
xsfield							event_type[];
xsfield							province_type[];
xsfield							player_type[];
xsfield							troop_type[];
xsfield							unit_type[];