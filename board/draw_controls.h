#include "draw.h"

#pragma once

extern "C" int			strcmp(const char* s1, const char* s2); // Compare two strings

enum control_s : unsigned char {
	NoControl, Text, Number, Date,
	ControlMask = 0xF
};

namespace draw {
namespace controls {
struct column {
	unsigned			flags;
	const char*			id;
	const char*			title;
	int					width;
	bool operator==(const char* value) const { return value && strcmp(id, value) == 0; }
	explicit operator bool() const { return id != 0; }
	control_s			getcontol() const { return (control_s)(flags&ControlMask); }
};
struct control {
	typedef void		(control::*callback)();
	bool				show_border;
	control();
	void				execute(void (control::*proc)()) const;
	virtual bool		isfocusable() const { return true; }
	bool				isfocused() const;
	bool				ishilited() const;
	virtual void		keydown() {}
	virtual void		keyend() {}
	virtual void		keyenter() {}
	virtual void		keyleft() {}
	virtual void		keyhome() {}
	virtual void		keypageup() {}
	virtual void		keypagedown() {}
	virtual void		keyright() {}
	virtual void		keysymbol(int symbol) {}
	virtual void		keyup() {}
	virtual void		mouseleft(point position); // Default behaivor set focus
	virtual void		mouseleftdbl(point position) {}
	virtual void		mousewheel(point position, int step) {}
	virtual void		view(rect rc);
};
struct list : control {
	int					origin, current, current_hilite;
	int					maximum_width, origin_width;
	int					lines_per_page, pixels_per_line;
	bool				show_grid_lines, show_selection;
	bool				hilite_odd_lines;
	list();
	void				correction();
	void				ensurevisible(); // ensure that current selected item was visible on screen if current 'count' is count of items per line
	int					find(int line, int column, const char* name, int lenght = -1) const;
	virtual int			getcolumn() const { return 0; } // get current column
	inline int			getline() const { return current; } // get current line
	virtual const char* getname(char* result, const char* result_max, int line, int column) const { return 0; }
	virtual int			getmaximum() const { return 0; }
	static int			getrowheight(); // Get default row height for any List Control
	void				hilight(rect rc) const;
	void				keydown() override;
	void				keyend() override;
	void				keyenter() override;
	void				keyhome() override;
	void				keypageup() override;
	void				keypagedown() override;
	void				keysymbol(int symbol) override;
	void				keyup() override;
	void				mouseleftdbl(point position) override;
	void				mousewheel(point position, int step) override;
	void				select(int index);
	virtual void		row(rect rc, int index) const; // Draw single row - part of list
	virtual void		rowhilite(rect rc, int index) const;
	void				view(rect rc) override;
};
struct table : list {
	const column*		columns;
	bool				show_totals;
	bool				show_header;
	table(const column* columns) : columns(columns), show_totals(false), show_header(true) {}
	virtual void		custom(char* buffer, const char* buffer_maximum, rect rc, int line, int column) const {}
	virtual const char*	getheader(char* result, const char* result_maximum, int column) const { return columns[column].title; }
	virtual int			getnumber(int line, int column) const { return 0; }
	virtual int			gettotal(int column) const { return 0; }
	virtual const char*	gettotal(char* result, const char* result_maximum, int column) const { return 0; }
	virtual void		row(rect rc, int index) const; // Draw single row - part of list
	virtual int			rowheader(rect rc) const; // Draw header row
	void				view(rect rc) override;
	void				viewtotal(rect rc) const;
};
}
}