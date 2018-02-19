#include "view.h"

bool cpp_parsemsg(const char* url, const char* out_url);
amap<const char*, draw::surface> resources;

void parse_error(int id, const char* url, int line, int column, const char* format_param) {
}

int main() {
	srand((int)time(0));
	char temp[4096];
	cpp_parsemsg("board/messages.h", "board/messages.cpp");
	bsdata::setparser(parse_error);
	bsdata::read("script/test.txt");
	bsdata::read("script/msgcombat.txt");
	bsdata::read("script/msgmenu.txt");
	if(!draw::initializemap())
		return 0;
	draw::create(-1, -1, 800, 600, WFResize|WFMinmax, 32);
	draw::setcaption(msgmenu.title);
	auto black_wood = gobject::find(province_type, "black_wood");
	auto red = gobject::find(player_type, "red");
	auto green = gobject::find(player_type, "green");
	black_wood->resolve(temp, red, green);
	draw::report(temp);
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}