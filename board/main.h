#include "adat.h"
#include "aref.h"
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
	void						addsupport(gobject* player, int value);
	static gobject*				create(const xsfield* meta);
	virtual int					get(attributes id) const { return 0; }
	int							get(const char* id, int index = 0) const;
	virtual const char*			getavatar() const { return ""; }
	virtual aref<gobject*>		getbonuses() const { return {0, 0}; }
	virtual const char*			getid() const { return ""; }
	int							getindex() const;
	virtual xsfield*			getmeta() const = 0;
	virtual gobject*			getmoveto() const { return (gobject*)get("moveto"); }
	virtual const char*			getname() const { return ""; }
	virtual gobject*			getowner() const { return 0; }
	virtual gobject*			getprovince() const { return 0; }
	virtual aref<gobject*>		getpenalty() const { return {0, 0}; }
	virtual aref<gobject*>		getprovinces() const { return {0, 0}; }
	int							getsupport(gobject* player) const;
	virtual const char*			gettext() const { return ""; }
	virtual aref<gobject*>		gettraits() const { return {0, 0}; }
	void						set(const char* id, int value, int index = 0);
	void						set(const char* id, gobject* value) { set(id, (int)value); }
};
namespace game
{
	void						maketurn(gobject* player);
}
xsfield							event_type[];
xsfield							province_type[];
xsfield							player_type[];
xsfield							troop_type[];
xsfield							unit_type[];