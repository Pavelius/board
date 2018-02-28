#pragma once

struct msgmenu_info {
	const char* title;
	const char* exit;
	const char* loadgame;
	const char* newgame;
	const char* savegame;
	const char* accept;
	const char* cancel;
	const char* yes;
	const char* no;
};
extern msgmenu_info msgmenu;
struct msgcombat_info {
	const char* attacking_force;
	const char* casualties;
	const char* defending_force;
	const char* winner;
	const char* lead;
	const char* attack;
	const char* defence;
	const char* raid;
	const char* squads;
};
extern msgcombat_info msgcombat;