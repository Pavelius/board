#include "bsreq.h"
#include "bsdata.h"
#include "messages.h"

static bsreq msgmenu_type[] = {
	BSREQ(msgmenu_info, exit, text_type),
	BSREQ(msgmenu_info, loadgame, text_type),
	BSREQ(msgmenu_info, newgame, text_type),
	BSREQ(msgmenu_info, savegame, text_type),
	BSREQ(msgmenu_info, title, text_type),
};
msgmenu_info msgmenu; BSGLOB(msgmenu);
static bsreq msgcombat_type[] = {
	BSREQ(msgcombat_info, attacking_force, text_type),
	BSREQ(msgcombat_info, defending_force, text_type),
	BSREQ(msgcombat_info, lead, text_type),
	BSREQ(msgcombat_info, squads, text_type),
	BSREQ(msgcombat_info, casualties, text_type),
};
msgcombat_info msgcombat; BSGLOB(msgcombat);
