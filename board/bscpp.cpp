#include "crt.h"
#include "io.h"

struct bscpp {

	const char*	p;
	char buffer[256 * 256];

	bool isvalid() {
		return *p != 0;
	}

	bool islinefeed() {
		if(*p == '\n') {
			p++;
			if(*p == '\r')
				p++;
			return true;
		} else if(*p == '\r') {
			p++;
			if(*p == '\n')
				p++;
			return true;
		} else
			return false;
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
		while(*p) {
			if(islinefeed())
				return;
			p++;
		}
	}

	bool iswhitespace() {
		if(*p == '\t' || *p == ' ') {
			p++;
			return true;
		} else
			return false;
	}

	bool iscomment() {
		if(p[0] == '/' && p[1] == '/') {
			p += 2;
			skipline();
			return true;
		}
		return false;
	}

	void skipws() {
		while(*p) {
			if(islinefeed())
				continue;
			if(iswhitespace())
				continue;
			if(iscomment())
				continue;
			if(p[0] == '\\' && (p[1] == 10 || p[1] == 13)) {
				p++;
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

	bscpp(const char* p) : p(p) {
	}

	bool parsemsg(io::stream& po) {
		char class_name[512];
		po << "#include \"bsreq.h\"\r\n";
		po << "#include \"bsdata.h\"\r\n";
		po << "#include \"messages.h\"\r\n";
		po << "\r\n";
		while(isvalid()) {
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
	io::file po(out_url, StreamWrite | StreamText);
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