#include "main.h"

class combatside {

	adat<gobject*, 32> units;
	gobject* general;
	gobject* tactic;
	gobject* owner;
	int strenght;
	int casualties;

public:

	combatside(const gobject* province, gobject* owner) : owner(owner), general(0), tactic(0), strenght(0), casualties(0) {
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
		zshuffle(units.data, units.count);
	}

	operator bool() const {
		return units.getcount();
	}

	int get(const char* id, tipinfo* ti, bool include_number = true) const {
		auto r = 0;
		if(ti && include_number)
			zcpy(ti->result, "[\"");
		if(general)
			r += general->fix(ti, general->get(id) + general->getbonus(id));
		for(auto p : units)
			r += p->fix(ti, p->get(id) + p->getbonus(id));
		if(tactic)
			r += tactic->fix(ti, tactic->get("strenght"));
		if(ti && include_number)
			szprints(zend(ti->result), ti->result_max, "\"%1i]", r);
		return r;
	}

	char* getlead(char* result, const char* result_max) const {
		zcpy(result, getsideof());
		if(result[0])
			zcat(result, " ");
		if(general)
			szprints(zend(result), result_max, msgcombat.lead, general->getname());
		return result;
	}

	char* setstrenght(char* result, const char* result_max, const char* format, const char* id, const char* province_name) {
		char text_lead[260]; text_lead[0] = 0;
		char text_tips[2048]; text_tips[0] = 0;
		tipinfo ti(text_tips, endofs(text_tips));
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
		strenght = get(id, &ti);
		szprints(result, result_max, format, getlead(text_lead, endofs(text_lead)), text_tips, province_name);
		return zend(result);
	}

	int getstrenght() const {
		return strenght;
	}

	const char* getside() const {
		if(owner)
			return owner->getname();
		return "";
	}

	const char* getsideof() const {
		if(owner)
			return owner->getnameof();
		return "";
	}

	gobject* getowner() {
		return owner;
	}

	void setcasualty(char* result, const char* result_max, combatside& enemy) {
		if(game.casualties)
			casualties += (enemy.strenght / game.casualties);
		if(enemy.tactic)
			casualties += enemy.tactic->get("enemy_casualties");
		if(tactic)
			casualties += tactic->get("friendly_casualties");
		if(tactic) {
			zcat(result, " ");
			szprints(zend(result), result_max, tactic->gettext(), getside());
		}
	}

	void applycasualty(char* result, const char* result_max) {
		result[0] = 0;
		auto ps = result;
		for(auto i = 0; i < casualties; i++) {
			if(!result[0]) {
				szprints(result, result_max, "\n%1 %2: ", msgcombat.casualties, getsideof());
				ps = zend(result);
			}
			if(units.count>0) {
				if(ps[0])
					zcat(ps, ", ");
				zcat(result, units.data[units.count - 1]->getname());
				units.count--;
			}
		}
		if(result[0])
			zcat(result, ".");
	}

};

bool gobject::resolve(char* result, const char* result_max, gobject* attacker_player, gobject* defender_player) const {
	auto p = result;
	combatside attackers(this, attacker_player);
	combatside defenders(this, defender_player);
	p = attackers.setstrenght(p, result_max, msgcombat.attacking_force, "attack", getname()); zcat(p, " ");
	p = defenders.setstrenght(zend(p), result_max, msgcombat.defending_force, "defend", getname());
	attackers.setcasualty(zend(p), result_max, defenders);
	defenders.setcasualty(zend(p), result_max, attackers);
	auto& winner = (attackers.getstrenght() > defenders.getstrenght()) ? attackers : defenders;
	zcat(result, " "); szprints(zend(result), result_max, msgcombat.winner, winner.getside());
	attackers.applycasualty(zend(p), result_max);
	defenders.applycasualty(zend(p), result_max);
	addbutton(zend(p), result_max, "accept", msgmenu.accept);
	return &winner == &attackers;
}