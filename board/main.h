#include "acol.h"
#include "adat.h"
#include "aref.h"
#include "crt.h"
#include "xsbase.h"

#pragma once

const int player_max = 8;

struct gobject
{
	void						add(const char* id, int value);
	void						addsupport(gobject* player, int value);
	static gobject*				create(const xsfield* meta);
	static gobject*				create(const xsfield* meta, const char* id);
	virtual int					get(const char* id) const;
	virtual int					get(const char* id, int index) const;
	virtual const char*			getavatar() const { return (const char*)get("avatar");; }
	int							getbonus(const char* id) const;
	virtual aref<gobject*>		getbonuses() const { return {0, 0}; }
	virtual const char*			getid() const { return (const char*)get("id"); }
	int							getindex() const;
	virtual xsfield*			getmeta() const = 0;
	gobject*					getmoveto() const { return (gobject*)get("moveto"); }
	virtual const char*			getname() const { return (const char*)get("name"); }
	virtual gobject*			getowner() const { return 0; }
	virtual aref<gobject*>		getpenalty() const { return {0, 0}; }
	virtual gobject*			getprovince() const { return 0; }
	virtual aref<gobject*>		getprovinces() const { return {0, 0}; }
	virtual int					getsupport(gobject* player) const;
	virtual const char*			gettext() const { return (const char*)get("text"); }
	virtual aref<gobject*>		gettraits() const { return {0, 0}; }
	void						set(const char* id, int value, int index = 0);
	void						set(const char* id, gobject* value) { set(id, (int)value); }
	void						set(const char* id, const char* value) { set(id, (int)value); }
};
xsfield							enchantment_type[];
xsfield							event_type[];
xsfield							province_type[];
xsfield							player_type[];
xsfield							trait_type[];
xsfield							troop_type[];
xsfield							unit_type[];

acol<gobject>					getcollection(const xsfield* fields); // Get collection by metadata