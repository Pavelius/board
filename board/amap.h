#pragma once

void* operator new(unsigned, void*);

template <class T1, class T2>
class amap {
	struct element {
		T1 key;
		T2 value;
	};
	element* data;
	unsigned count;
	unsigned count_maximum;
	void reserve() {
		if(data) {
			if(count_maximum >= count)
				return;
		}
		count_maximum = rmoptimal(count + 1);
		data = rmreserve(data, count_maximum*size);
	}
public:
	typedef T1 key_type;
	typedef T2 value_type;
	amap() : data(0), count(0) {}
	~amap() { clear(); }
	T2& operator[](T1 k) { auto p = find(k); if(!p) p = add; return *p; }
	element* begin() { return data; }
	element* end() { return data + count; }
	T2* add() { reserve(); void* p = data + (count++); auto p2 = new(p) T2; return p2; }
	T2* find(T1 k) {
		for(auto& e : *this) {
			if(e.key == k)
				return &e.value;
		}
		return 0;
	}
};