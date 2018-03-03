#include "view.h"
#include "io.h"

void generate_help();
bool cpp_parsemsg(const char* url, const char* out_url);
amap<const char*, draw::surface> resources;

static void log_error(const char* url, int line, int column, const char* format, ...) {
	char temp[4096];
	szprintv(temp, temp + sizeof(temp) - 1, format, xva_start(format));
	io::file file("log.txt", StreamWrite | StreamAppend);
	auto b = file.seek(0, SeekEnd);
	file << "Error in '" << url << "', line " << line << ", column " << column << ": ";
	file << temp << "\r\n";
}

static void parse_error(bsparse_error_s id, const char* url, int line, int column, const char** format_param) {
	static struct message_info {
		bsparse_error_s	id;
		const char*		text;
	} msg[] = {{ErrorExpectedIdentifier, "Expected identifier"},
	{ErrorNotFoundBase1p, "Not found database '%1'"},
	{ErrorNotFoundIdentifier1p, "Not found identifier '%1'"},
	{ErrorNotFoundMember1pInBase2p, "Not found member '%1' in database '%2'"},
	{ErrorFile2pNotFound, "Not found file '%2' stored in requisit '%1'"},
	{ErrorExpectedArrayField, "Expected array field"},
	};
	for(auto& e : msg) {
		if(e.id == id) {
			log_error(url, line, column, e.text, format_param[0], format_param[1], format_param[2], format_param[3]);
			break;
		}
	}
}

static bsparse_error_s parse_validate(const char* id, const char* value) {
	if(strcmp(id, "avatar") == 0) {
		if(!io::file::exist(value))
			return ErrorFile2pNotFound;
	}
	return NoParserError;
}

//struct stest {
//	const char* name;
//};
//bsreq stest_type[] = {
//	BSREQ(stest, name, text_type),
//	{}
//};
//stest stest_data1[2] = {"Test1", "Test2"};
//stest stest_data2[4] = {"Test1", "Test2"};
//static bsdata managers[] = {{"stest", stest_data1, stest_type},
//{"stest2", stest_data2, stest_type}
//};

int main() {
	srand((int)time(0));
	char temp[4096];
	cpp_parsemsg("board/messages.h", "board/messages.cpp");
	bsdata::setparser(parse_error);
	bsdata::setparser(parse_validate);
	bsdata::read("script/test.txt");
	bsdata::read("script/msgcombat.txt");
	bsdata::read("script/msgmenu.txt");
#ifdef _DEBUG
	generate_help();
#endif
	if(!draw::initializemap())
		return 0;
	//draw::create(-1, -1, 800, 600, WFResize|WFMinmax, 32);
	draw::setcaption(msgmenu.title);
	auto black_wood = gobject::find(province_type, "black_wood");
	auto red = gobject::find(player_type, "red");
	auto green = gobject::find(player_type, "green");
	auto gordek = gobject::find(hero_type, "gordek");
	gordek->set("province", black_wood);
	black_wood->resolve(temp, endofs(temp), red, green);
	red->setuiactive();
	//draw::report(temp);
	//auto action = draw::getaction(red, gordek);
	//if(action) {
	//	auto province = draw::getprovince(red, gordek, action);
	//}
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}