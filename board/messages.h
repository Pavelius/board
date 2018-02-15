#pragma once

struct msgmenu_info {
	const char* exit;
	const char* loadgame;
	const char* newgame;
	const char* savegame;
	const char* title;
};
extern msgmenu_info msgmenu;
struct msgcombat_info {
	const char* attacking_force;
	const char* casualties;
	const char* defending_force;
	const char* lead;
	const char* loose;
	const char* win;
};
extern msgcombat_info msgcombat;