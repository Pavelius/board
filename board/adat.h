#include "initializer_list.h"

#pragma once

// Use when we don't want use allocator and must have static data
// Beware - it's not have constructors and destructor
template<class T, int count_max = 128>
struct adat {
	unsigned count;
	T data[count_max];
	constexpr adat() : count(0) {}
	constexpr adat(const std::initializer_list<T>& list) : count(0) {
		for(auto& e : list)
			data[count++] = e;
	}
	constexpr const T& operator[](int index) const {
		return data[index];
	}
	constexpr T& operator[](int index) {
		return data[index];
	}
	T* add() {
		if(count < count_max)
			return data + (count++);
		return 0;
	}
	void add(const T& e) {
		if(count < count_max)
			data[count++] = e;
	}
	constexpr T* begin() { return data; }
	constexpr const T* begin() const { return data; }
	void clear() { count = 0; }
	constexpr T* end() { return data + count; }
	constexpr const T* end() const { return data + count; }
	template<class Z> T* find(Z id) { auto e1 = data + count; for(T* e = data; e < e1; e++) { if(e->id == id) return e; } return 0; }
	constexpr int getcount() const { return count; }
	constexpr int indexof(const T* e) const {
		if(e >= data && e <= data + count)
			return e - data;
		return -1;
	}
	int indexof(const T t) const {
		for(unsigned i = 0; i < count; i++)
			if(data[i] == t)
				return i;
		return -1;
	}
	bool is(const T t) const {
		for(unsigned i = 0; i < count; i++)
			if(data[i] == t)
				return true;
		return false;
	}
	void remove(int index, int remove_count = 1) {
		if(index < 0)
			return;
		if(index<int(count - 1))
			memcpy(data + index, data + index + 1, sizeof(data[0])*(count - index - 1));
		count--;
	}
};