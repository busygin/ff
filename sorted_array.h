/*
 * sorted_array.h
 *
 *  Created on: Jun 7, 2014
 *      Author: busygin
 */

#ifndef SORTED_ARRAY_H_
#define SORTED_ARRAY_H_


#include <cstdlib>
#include <algorithm>


// works only with scalars, structs of scalars, and pointers that will be freed elsewhere!
// TODO: use Google's tcmalloc
template<typename T, size_t INIT_ALLOC=0, double EXTRA_ALLOC_FRACTION=0.3>
class sorted_array {
	T* data;
	size_t n;
	size_t alloc_size;

public:
	sorted_array() : data(INIT_ALLOC==0 ? nullptr : (T*)malloc(INIT_ALLOC*sizeof(T))), n(0), alloc_size(INIT_ALLOC) { }
	~sorted_array() { if (data) free(data); }

	size_t size() const { return n; }

	const T& operator[](size_t i) const { return data[i]; }
	T& operator[](size_t i) { return data[i]; }

	T* search_for(const T& elem) const { return std::lower_bound(data, data+n, elem); }
	bool found(const T& elem, T* p) const { return (p-data<n) && (*p==elem); }
	bool exists(const T& elem) const { return found(elem, search_for(elem)); }

	void erase(size_t i) { --n; memmove(data+i, data+(i+1), n-i); }
	void erase(T* p) { --n; memmove(p, p+1, n-(p-data)); }

	void erase_elem(const T& elem) {
		T* p = search_for(elem);
		if(found(elem,p)) erase(p);
	}

	void insert(size_t i, const T& elem) {
		++n;
		if(n>alloc_size)
			reserve(static_cast<size_t>(n*(1.0+EXTRA_ALLOC_FRACTION)));
		T* p = data+i;
		memmove(p+1, p, n-i-1);
		*p = elem;
	}

	void insert(T* p, const T& elem) {
		size_t i = p-data;
		++n;
		if(n>alloc_size) {
			reserve(static_cast<size_t>(n*(1.0+EXTRA_ALLOC_FRACTION)));
			p = data+i;
		}
		memmove(p+1, p, n-i-1);
		*p = elem;
	}

	void insert_elem(const T& elem) { insert(search_for(elem), elem); }

	void reserve(size_t n1) {
		data = realloc(data, n1*sizeof(T));
		alloc_size = n1;
	}
};



#endif /* SORTED_ARRAY_H_ */
