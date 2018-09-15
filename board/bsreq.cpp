#include "bsreq.h"

extern "C" int strcmp(const char* s1, const char* s2);

bsreq any_type[2] = {{"any"}};
bsreq number_type[2] = {{"number"}};
bsreq text_type[2] = {{"text"}};
bsreq bsreq_type[] = {
	BSREQ(bsreq, id, text_type),
	BSREQ(bsreq, offset, number_type),
	BSREQ(bsreq, size, number_type),
	BSREQ(bsreq, lenght, number_type),
	BSREQ(bsreq, count, number_type),
	BSREQ(bsreq, reference, number_type),
	BSREQ(bsreq, type, bsreq_type),
{0}
};

const bsreq* bsreq::getkey() const {
	auto f = find("id", text_type);
	if(!f)
		f = find("name", text_type);
	if(!f)
		f = find("text", text_type);
	return f;
}

const bsreq* bsreq::find(const char* name) const {
	if(!this)
		return 0;
	for(auto p = this; p->id; p++) {
		if(strcmp(p->id, name) == 0)
			return p;
	}
	return 0;
}

const bsreq* bsreq::find(const char* name, const bsreq* type) const {
	if(!this)
		return 0;
	for(auto p = this; p->id; p++) {
		if(p->type != type)
			continue;
		if(strcmp(p->id, name) == 0)
			return p;
	}
	return 0;
}

int bsreq::get(const void* p) const {
	switch(size) {
	case sizeof(char) : return *((char*)p);
	case sizeof(short) : return *((short*)p);
	default: return *((int*)p);
	}
}

void bsreq::set(const void* p, int value) const {
	switch(size) {
	case sizeof(char) : *((char*)p) = value; break;
	case sizeof(short) : *((short*)p) = value; break;
	default: *((int*)p) = value; break;
	}
}

bool bsreq::match(const void* p, const char* name) const {
	auto value = (const char*)get(p);
	if(!value || type != text_type)
		return false;
	for(int i = 0; name[i]; i++) {
		if(value[i] != name[i])
			return false;
	}
	return true;
}

bsval bsval::ptr(const char* name) const {
	if(data && type) {
		for(auto p = type; p->id; p++) {
			if(p->id[0] == 0) {
				bsval v1 = {p->type, (char*)data + p->offset};
				bsval v2 = v1.ptr(name);
				if(v2)
					return v2;
			} else if(strcmp(p->id, name) == 0) {
				bsval v1;
				v1.type = p->type;
				v1.data = (char*)data + p->offset;
				if(p->reference && p->type != text_type)
					v1.data = *((void**)v1.data);
				return v1;
			}
		}
	}
	return {0, 0};
}

int bsval::get() const {
	if(!type || !data)
		return 0;
	switch(type->size) {
	case sizeof(char) : return *((char*)data);
	case sizeof(short) : return *((short*)data);
	default: return *((int*)data);
	}
}

void bsval::set(int value) {
	if(!type || !data)
		return;
	switch(type->size) {
	case sizeof(char) : *((char*)data) = value; break;
	case sizeof(short) : *((short*)data) = value; break;
	default: *((int*)data) = value; break;
	}
}

const char* bsval::gets(const char* name) const {
	auto p = (const char*)get(name);
	return p ? p : "";
}