#include "acol.h"
#include "adat.h"
#include "aref.h"
#include "crt.h"
#include "bsdata.h"

#pragma once

const int player_max = 8;

struct gobject
{
	void						add(const char* id, int value);
	void						add(const char* id, int value, int index);
	void						addloyalty(gobject* province, gobject* player, int value);
	static gobject*				create(const bsreq* meta);
	static gobject*				create(const bsreq* meta, const char* id);
	virtual int					get(const char* id) const;
	virtual int					get(const char* id, int index) const;
	static acol<gobject>		getcol(const bsreq* fields); // Get collection by metadata
	void*						getarray(const char* id) const;
	const char*					getavatar() const { return (const char*)get("avatar");; }
	int							getbonus(const char* id) const;
	virtual aref<gobject*>		getbonuses() const { return aref<gobject*>(); }
	const char*					getid() const { return (const char*)get("id"); }
	int							getindex() const;
	gobject*					getloyalty() const;
	virtual bsreq*			getmeta() const { return 0; }
	virtual gobject*			getmoveto() const { return 0; }
	virtual const char*			getname() const { return (const char*)get("name"); }
	gobject*					getowner() const { return (gobject*)get("owner"); }
	virtual aref<gobject*>		getpenalty() const { return aref<gobject*>(); }
	gobject*					getprovince() const { return (gobject*)get("province"); }
	virtual aref<gobject*>		getprovinces() const { return aref<gobject*>(); }
	virtual const char*			gettext() const { return (const char*)get("text"); }
	virtual aref<gobject*>		gettraits() const { return aref<gobject*>(); }
	bool						is(bsreq* type) const;
	virtual bool				isvalid() const { return true; }
	bool						isoccupied() const;
	void						set(const char* id, int value);
	void						set(const char* id, int value, int index);
	void						set(const char* id, gobject* value) { set(id, (int)value); }
	void						set(const char* id, const char* value) { set(id, (int)value); }
};
bsreq							enchantment_type[];
bsreq							event_type[];
bsreq							hero_type[];
bsreq							province_type[];
bsreq							player_type[];
bsreq							trait_type[];
bsreq							troop_type[];
bsreq							unit_type[];