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
	void						add(const char* id, int value, int index);
	void						addloyalty(gobject* province, gobject* player, int value);
	static gobject*				create(const xsfield* meta);
	static gobject*				create(const xsfield* meta, const char* id);
	virtual int					get(const char* id) const;
	virtual int					get(const char* id, int index) const;
	void*						getarray(const char* id) const;
	const char*					getavatar() const { return (const char*)get("avatar");; }
	int							getbonus(const char* id) const;
	virtual aref<gobject*>		getbonuses() const { return {0, 0}; }
	const char*					getid() const { return (const char*)get("id"); }
	int							getindex() const;
	gobject*					getloyalty() const;
	virtual xsfield*			getmeta() const { return 0; }
	virtual gobject*			getmoveto() const { return 0; }
	virtual const char*			getname() const { return (const char*)get("name"); }
	gobject*					getowner() const { return (gobject*)get("owner"); }
	virtual aref<gobject*>		getpenalty() const { return {0, 0}; }
	gobject*					getprovince() const { return (gobject*)get("province"); }
	virtual aref<gobject*>		getprovinces() const { return {0, 0}; }
	virtual const char*			gettext() const { return (const char*)get("text"); }
	virtual aref<gobject*>		gettraits() const { return {0, 0}; }
	bool						isoccupied() const;
	void						set(const char* id, int value);
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