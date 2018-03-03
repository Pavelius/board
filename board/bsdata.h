#include "bsreq.h"
#include "collection.h"

#pragma once

#define BSMETA(c) \
bsdata c##_manager(#c, c##_data, sizeof(c##_data[0]), sizeof(c##_data)/sizeof(c##_data[0]), c##_type);
#define BSDATA(c, c_type) \
bsdata c##_manager(#c, c##s.data, c##s.count, sizeof(c##s.data[0]), sizeof(c##s.data)/sizeof(c##s.data[0]), c_type);
#define BSGLOB(c) \
bsdata c##_manager(#c, &c, 1, sizeof(c), c##_type);

enum bsparse_error_s {
	NoParserError,
	ErrorExpectedIdentifier, ErrorExpectedArrayField,
	ErrorNotFoundBase1p, ErrorNotFoundType, ErrorNotFoundIdentifier1p, ErrorNotFoundMember1pInBase2p,
	ErrorFile2pNotFound,
};

struct bsdata : collection {
	const char*			id;
	const bsreq*		fields;
	void*				data;
	unsigned			size;
	bsdata*				next;
	static bsdata*		first;
	//
	template<class T, unsigned N> bsdata(const char* id, T(&data)[N], const bsreq* fields) : id(id), fields(fields), data(&data), size(sizeof(T)), count(current_count), current_count(0), next(0), maximum_count(N) {}
	bsdata(const char* id, void* data, unsigned size, unsigned maximum_count, const bsreq* fields);
	bsdata(const char* id, void* data, unsigned& count, unsigned size, unsigned maximum_count, const bsreq* fields);
	//
	void*				add() override;
	char*				begin() const { return (char*)data; }
	void				clear() override { count = 0; }
	char*				end() const { return (char*)data + size*count; }
	void*				get(int index) const override { return (char*)data + index*size; }
	unsigned			getcount() const override { return count; }
	unsigned			getmaxcount() const override { return maximum_count; }
	unsigned			getsize() const override { return size; }
	int					indexof(const void* element) const override;
	static bsdata*		find(const char* id);
	static bsdata*		find(const bsreq* id);
	void*				find(const bsreq* id, const char* value);
	static bsdata*		findbyptr(const void* object);
	static void			read(const char* url, bsdata** custom = 0);
	void				remove(int index, int count = 1) override;
	void				setcount(unsigned value) { count = value; }
	static void			setparser(void(*error_callback)(bsparse_error_s id, const char* url, int line, int column, const char** format_param));
	static void			setparser(bsparse_error_s(*validate_callback)(const char* id, const char* value));
	static void			write(const char* url, const char** baseids, bool(*comparer)(void* object, const bsreq* type) = 0);
	static void			write(const char* url, const char* baseid);
private:
	unsigned			maximum_count;
	unsigned			current_count;
	unsigned&			count;
};