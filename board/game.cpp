#include "main.h"

static bsreq game_type[] = {
	BSREQ(game_info, casualties, number_type),
	BSREQ(game_info, map, text_type),
};
game_info game_data; BSMETA(game);