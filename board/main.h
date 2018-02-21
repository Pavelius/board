#include "acol.h"
#include "adat.h"
#include "amap.h"
#include "aref.h"
#include "bsdata.h"
#include "crt.h"
#include "messages.h"
#include "point.h"
#include "stringcreator.h"

#pragma once

//#ifdef _DEBUG
//#define dbgcheck(...) dlgerr("Check this", __VA_ARGS__);
//#else
//#define dbgcheck(...)
//#endif

const int player_max = 8;
bsreq enchantment_type[];
bsreq event_type[];
bsreq hero_type[];
bsreq msgcombat_type[];
bsreq point_type[];
bsreq province_type[];
bsreq player_type[];
bsreq tactic_type[];
bsreq trait_type[];
bsreq troop_type[];
bsreq unit_type[];

enum gender_s : unsigned char {
	Male, Female,
};
struct tipinfo {
	char*						result;
	const char*					text;
	const char*					separator;
	tipinfo(char* result) :result(result), text("%+1i %2"), separator("\r\n:::") { result[0] = 0; }
};
struct gobject {
	void						act(char* result, const char* format, ...) const;
	void						actv(char* result, const char* format, const char* param) const;
	void						add(const char* id, int value);
	void						add(const char* id, int value, int index);
	static gobject*				create(const bsreq* meta);
	static gobject*				create(const bsreq* meta, const char* id);
	static gobject*				find(bsreq* type, const char* id);
	int							fix(tipinfo* ti, int value) const;
	virtual int					get(const char* id) const;
	virtual int					get(const char* id, int index) const;
	const char*					gets(const char* id) const;
	static acol<gobject>		getcol(const bsreq* fields); // Get collection by metadata
	void*						getarray(const char* id) const;
	virtual const char*			getavatar() const { return gets("avatar");; }
	int							getbonus(const char* id) const;
	virtual aref<gobject*>		getbonuses() const { return aref<gobject*>(); }
	virtual gender_s			getgender() const { return Male; }
	unsigned					getheroes(gobject** result, unsigned maximum, gobject* province) const { return getobjects(hero_type, result, maximum, province); }
	const char*					getid() const { return gets("id"); }
	int							getindex() const;
	virtual bsreq*				getmeta() const { return 0; }
	virtual gobject*			getmoveto() const { return 0; }
	virtual const char*			getname() const { return gets("name"); }
	virtual const char*			getnameof() const { return gets("nameof"); }
	unsigned					getobjects(bsreq* type, gobject** result, unsigned maximum, gobject* province) const;
	virtual gobject*			getowner() const { return (gobject*)get("owner"); }
	virtual aref<gobject*>		getpenalty() const { return aref<gobject*>(); }
	virtual point				getposition() const { return {0, 0}; }
	static char*				getpresent(char* result, unsigned maximum, gobject** objects, unsigned count);
	virtual gobject*			getprovince() const { return (gobject*)get("province"); }
	virtual aref<gobject*>		getprovinces() const { return aref<gobject*>(); }
	virtual gobject*			gettactic() const { return (gobject*)get("tactic"); }
	virtual const char*			gettext() const { return gets("text"); }
	unsigned					gettropps(gobject** result, unsigned maximum, gobject* province) const { return getobjects(troop_type, result, maximum, province); }
	bool						is(bsreq* type) const;
	bool						isready() const { return getprovince() == 0; }
	virtual bool				isvalid() const { return this != 0; }
	bool						resolve(char* result, gobject* attacker_player, gobject* defender_player) const;
	void						set(const char* id, int value);
	void						set(const char* id, int value, int index);
	void						set(const char* id, gobject* value) { set(id, (int)value); }
	void						set(const char* id, const char* value) { set(id, (int)value); }
	void						setuiactive();
	static void					sort(gobject** result, unsigned count);
};
struct combatable : gobject {
	char						attack, defend;
	char						enemy_casualties, firendly_casualties;
	char						gold, gold_upkeep, support, support_upkeep;
	gobject*					traits[5];
};
struct game_info {
	char						casualties; // One casualties per this strenght value
	const char*					map;
};
extern game_info game;
namespace logs {
struct driver : stringcreator {
	const char*					name;
	const char*					province;
	gender_s					gender;
	driver() : name(""), province(""), gender(Male) {}
	void						parseidentifier(char* result, const char* result_max, const char* identifier) override;
};
}