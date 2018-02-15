#include "main.h"

class combatside {

	adat<gobject*, 32> units;
	gobject* general;
	gobject* tactic;
	int strenght;
	int casualties;

public:

	combatside(const gobject* province, gobject* owner) : general(0), tactic(0), strenght(0), casualties(0) {
		units.initialize();
		// Get all units in province by one owner
		for(auto& e : gobject::getcol(troop_type)) {
			if(!e.isvalid())
				continue;
			if(e.getowner() != owner)
				continue;
			if(e.getprovince() != province)
				continue;
			units.add(&e);
		}
		// Get all heroes in province and choose one best matched
		for(auto& e : gobject::getcol(hero_type)) {
			if(!e.isvalid())
				continue;
			if(e.getowner() != owner)
				continue;
			if(e.getprovince() != province)
				continue;
			general = &e;
			break;
		}
	}

	operator bool() const {
		return units.getcount();
	}

	int get(const char* id, tipinfo* ti, bool include_number = true) const {
		auto r = 0;
		if(ti && include_number)
			zcpy(ti->result, "[\"");
		if(general)
			r += general->fix(ti, general->getbonus(id));
		for(auto p : units)
			r += p->fix(ti, p->get(id));
		if(ti && include_number)
			szprint(zend(ti->result), "\"%1i]", r);
		return r;
	}

	char* getlead(char* result) const {
		if(general)
			return szprint(result, msgcombat.lead, general->getname());
		return "";
	}

	char* setstrenght(char* result, const char* format, const char* id, const char* province_name) {
		char text_lead[260]; text_lead[0] = 0;
		char text_tips[2048]; text_tips[0] = 0;
		tipinfo ti(text_tips);
		strenght = get(id, &ti);
		if(general)
			tactic = general->gettactic();
		if(!tactic) {
			auto m = bsdata::find(tactic_type);
			if(m) {
				if(m->getcount())
					tactic = (gobject*)m->get(rand() % (m->getcount()));
				else
					tactic = (gobject*)m->get(0);
			}
		}
		if(tactic)
			strenght += tactic->fix(&ti, tactic->get("strenght"));
		szprint(result, format, getlead(text_lead), text_tips, province_name);
		return zend(result);
	}

	int getstrenght() const {
		return strenght;
	}

	void setcasualty(combatside& enemy) {
		if(game.casualties)
			casualties += (enemy.strenght / game.casualties);
		if(enemy.tactic)
			casualties += enemy.tactic->get("enemy_casualties");
		if(tactic)
			casualties += enemy.tactic->get("friendly_casualties");
	}

};

void gobject::resolve(char* result, gobject* attacker_player, gobject* defender_player) const {
	auto p = result;
	combatside attackers(this, attacker_player);
	combatside defenders(this, defender_player);
	p = attackers.setstrenght(p, msgcombat.attacking_force, "attack", getname()); zcat(p, " ");
	p = defenders.setstrenght(zend(p), msgcombat.defending_force, "defence", getname());
	attackers.setcasualty(defenders);
	defenders.setcasualty(attackers);
}