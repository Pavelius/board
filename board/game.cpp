#include "main.h"

static bsreq game_type[] = {
	BSREQ(game_info, casualties, number_type),
};
game_info game; BSGLOB(game);