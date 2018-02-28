#include "bsdata.h"
#include "messages.h"

bsreq msgmenu_type[] = {
	BSREQ(msgmenu_info, title, text_type),
	BSREQ(msgmenu_info, exit, text_type),
	BSREQ(msgmenu_info, loadgame, text_type),
	BSREQ(msgmenu_info, newgame, text_type),
	BSREQ(msgmenu_info, savegame, text_type),
	BSREQ(msgmenu_info, accept, text_type),
	BSREQ(msgmenu_info, cancel, text_type),
	BSREQ(msgmenu_info, yes, text_type),
	BSREQ(msgmenu_info, no, text_type),
{},
};
msgmenu_info msgmenu; BSGLOB(msgmenu);
bsreq msgcombat_type[] = {
	BSREQ(msgcombat_info, attacking_force, text_type),
	BSREQ(msgcombat_info, casualties, text_type),
	BSREQ(msgcombat_info, defending_force, text_type),
	BSREQ(msgcombat_info, winner, text_type),
	BSREQ(msgcombat_info, lead, text_type),
	BSREQ(msgcombat_info, attack, text_type),
	BSREQ(msgcombat_info, defence, text_type),
	BSREQ(msgcombat_info, raid, text_type),
	BSREQ(msgcombat_info, squads, text_type),
{},
};
msgcombat_info msgcombat; BSGLOB(msgcombat);
