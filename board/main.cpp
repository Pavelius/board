#include "main.h"

bool cpp_parsemsg(const char* url, const char* out_url);

int main() {
	char temp[4096];
	cpp_parsemsg("board/messages.h", "board/messages.cpp");
	bsdata::read("script/test.txt");
	bsdata::read("script/msgcombat.txt");
	bsdata::read("script/msgmenu.txt");
	auto black_wood = gobject::find(province_type, "black_wood");
	auto red = gobject::find(player_type, "red");
	auto green = gobject::find(player_type, "green");
	black_wood->resolve(temp, red, green);
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}