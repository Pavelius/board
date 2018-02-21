#include "view.h"
#include "io.h"

bool cpp_parsemsg(const char* url, const char* out_url);
amap<const char*, draw::surface> resources;

static void log_error(const char* url, int line, int column, const char* format, ...) {
	char temp[4096];
	szprintv(temp, format, xva_start(format));
	io::file file("log.txt", StreamWrite|StreamAppend);
	auto b = file.seek(0, SeekEnd);
	file << "Error in '" << url << "', line " << line << ", column " << column << ": ";
	file << temp << "\r\n";
}

void parse_error(bsparse_error_s id, const char* url, int line, int column, const char** format_param) {
	switch(id) {
	case ErrorNotFoundIdentifier1p:
		log_error(url, line, column, "Not found identifier '%1'", format_param[0]);
		break;
	case ErrorNotFoundMember1pInBase2p:
		log_error(url, line, column, "Not found member '%1' in database '%2'", format_param[0], format_param[1]);
		break;
	}
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
	auto gordek = gobject::find(hero_type, "gordek");
	gordek->set("province", black_wood);
	black_wood->resolve(temp, red, green);
	red->setuiactive();
	draw::report(temp);
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}