#pragma once

template<class T>
class acol {
	class iterator {
		T*					current;
		unsigned			size;
	public:
		constexpr iterator(T* current, unsigned size) : current(current), size(size) {}
		constexpr T&		operator*() const { return *current; }
		constexpr bool		operator!=(const iterator& e) const { return e.current != current; }
		constexpr void		operator++() { current = (T*)((char*)current + size); }
	};
	T*						pbegin;
	T*						pend;
	unsigned				size;
public:
	constexpr acol(T* start, unsigned count, unsigned size) : pbegin(start), pend((T*)((char*)start + size*count)), size(size) {}
	constexpr T& operator[](unsigned index) const { return *((T*)((char*)pbegin + size*index)); }
	iterator				begin() const { return iterator(pbegin, size); }
	iterator				end() const { return iterator(pend, size); }
	T*						get(unsigned index) { return (T*)((char*)pbegin + index*size); }
	unsigned				getcount() { return ((char*)pend - (char*)pbegin) / size; }
};
