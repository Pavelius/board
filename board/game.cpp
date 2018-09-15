#include "main.h"
#include "view.h"

static bsreq game_type[] = {
	BSREQ(game_info, casualties, number_type),
	BSREQ(game_info, map, text_type),
};
game_info game_data; BSMETA(game);

void game::refresh() {
	// Обновим все подчиненные объекты
	const bsreq* game_types[] = {hero_type, player_type};
	for(auto pt : game_types) {
		for(auto& e : gobject::getcol(pt)) {
			if(!e)
				continue;
			e.refresh();
		}
	}
}

void game::turn() {
	refresh();
	// Поочереди все игроки походят
	for(auto& e : gobject::getcol(player_type)) {
		if(!e)
			continue;
		e.setuiactive();
		draw::makemove(&e);
	}
}

static bool dialog(const char* header, armyinfo& v1, armyinfo& v2) {

}