﻿#include "main.h"

bsreq msg_type[] = {
	BSREQ(msg_info, attacking_force, text_type),
	BSREQ(msg_info, casualties, text_type),
	BSREQ(msg_info, defending_force, text_type),
	BSREQ(msg_info, winner, text_type),
	BSREQ(msg_info, lead, text_type),
	BSREQ(msg_info, attack, text_type),
	BSREQ(msg_info, defence, text_type),
	BSREQ(msg_info, raid, text_type),
	BSREQ(msg_info, squads, text_type),
	//
	BSREQ(msg_info, title, text_type),
	BSREQ(msg_info, exit, text_type),
	BSREQ(msg_info, loadgame, text_type),
	BSREQ(msg_info, newgame, text_type),
	BSREQ(msg_info, savegame, text_type),
	BSREQ(msg_info, accept, text_type),
	BSREQ(msg_info, cancel, text_type),
	BSREQ(msg_info, yes, text_type),
	BSREQ(msg_info, no, text_type),
{},
};
msg_info msg_data; BSMETA(msg);