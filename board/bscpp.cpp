#include "bsdata.h"
#include "crt.h"
#include "io.h"

struct bscpp {

	const char*	p;
	char buffer[128 * 256];

	bool islinefeed() const {
		return *p == 13 || *p == 10;
	}

	void skip() {
		p++;
	}

	bool skip(char sym) {
		if(*p != sym)
			return false;
		p++;
		skipws();
		return true;
	}

	bool skip(const char* sym) {
		auto i = 0;
		while(sym[i]) {
			if(p[i] != sym[i])
				return false;
			i++;
		}
		p += i;
		return true;
	}

	bool skipws(const char* sym) {
		if(!skip(sym))
			return false;
		skipws();
		return true;
	}

	void skipline() {
		while(p[0] && p[0] != 10 && p[0] != 13)
			p++;
	}

	void skipws() {
		while(*p) {
			if(*p == '\n') {
				p++;
				if(*p == '\r')
					p++;
				continue;
			} else if(*p == '\r') {
				p++;
				if(*p == '\n')
					p++;
				continue;
			} else if(p[0] == 9 || p[0] == 0x20) {
				p++;
				continue;
			} else if(p[0] == '\\') {
				p++;
				if(!(p[0] == 10 || p[0] == 13))
					p++;
				continue;
			} else if(p[0] == '/' && p[1] == '/') {
				// Comments
				p += 2;
				skipline();
				continue;
			}
			break;
		}
	}

	bool readidentifier() {
		if((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z')) {
			auto ps = buffer;
			auto pe = ps + sizeof(buffer) / sizeof(buffer[0]) - 1;
			while(*p && ((*p >= '0' && *p <= '9') || *p == '_' || ischa(*p))) {
				if(ps < pe)
					*ps++ = *p;
				p++;
			}
			ps[0] = 0;
		} else
			return false;
		return true;
	}

public:

	bscpp(const char* p) : p(p) {
	}

	bool parsemsg(io::stream& po) {
		char class_name[512];
		po << "#include \"bsreq.h\"\r\n";
		po << "#include \"bsdata.h\"\r\n";
		po << "#include \"messages.h\"\r\n";
		po << "\r\n";
		while(*p) {
			if(skip("#") || skip("extern")) {
				skipline();
				skipws();
				continue;
			}
			if(!skipws("struct"))
				return false;
			if(!readidentifier())
				return false;
			skipws();
			if(true) {
				zcpy(class_name, buffer);
				char* pz = (char*)zchr(class_name, '_');
				if(pz)
					pz[0] = 0;
			}
			po << "static bsreq " << class_name << "_type[] = {\r\n";
			if(!skipws("{"))
				return false;
			while(*p) {
				if(!skipws("const char*"))
					return false;
				if(!readidentifier())
					return false;
				po << "\tBSREQ(" << class_name << "_info, " << buffer << ", text_type),\r\n";
				if(!skipws(";"))
					return false;
				if(*p == '}') {
					p++; skipws();
					break;
				}
			}
			if(!skipws(";"))
				return false;
			po << "};\r\n" << class_name << "_info " << class_name << "; BSGLOB(" << class_name << ");\r\n";
		}
		return true;
	}

};

bool cpp_parsemsg(const char* url, const char* out_url) {
	io::file po(out_url, StreamWrite|StreamText);
	if(!po)
		return false;
	auto p = loadt(url);
	if(!p)
		return false;
	bscpp e(p);
	e.skipws();
	e.parsemsg(po);
	delete p;
	return true;
}