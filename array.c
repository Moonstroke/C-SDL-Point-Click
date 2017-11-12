#include "array.h"

#include <string.h>


struct array {
	uint capacity;
	uint size;
	data *items;
};


Array newarray(const size_t s, const size_t is) {
	Array a = malloc(sizeof(struct array));
	if(a == NULL)
		return NULL;
	// Using calloc() instead of malloc() here is preferred, as the array might
	// be left only half-full for some time
	data *items = calloc(s, sizeof(is));
	if(items == NULL)
		return NULL;
	a->items = items;
	a->capacity = s;
	a->size = 0;
	return a;
}

void freerarray(Array a, void(*f)(data)) {
	if(f) {
		size_t i = a->size;
		while(i--)
			f(a->items[i]);
	}
	free(a->items);
	free(a);
	a = NULL;
}

inline uint arraysize(const Array a) {
	return a->size;
}

int addarrayitem(Array a, data item) {
	const int c = a->capacity;
	if(a->size == c) {
		void *items = realloc(a->items, a->capacity += (c / 2 + c % 2));
		if(items == NULL) {
			return -1;
		}
	}
	a->items[a->size++] = item;
	return a->size;
}

inline void *getarrayitem(const Array a, const ssize_t i) {
	return i < 0 ? a->items[a->size + i] : i < a->size ? a->items[i] : NULL;
	/* ungolfed:
	if(i < 0) {
		i = a->size + i;
	}
	// here, necessarily index < a->size
	if(i < 0)
		return NULL;
	return items[i];
	*/
}

data droparrayitem(Array a, const ssize_t index) {
	const size_t n = a->size,
	             i = index < 0 ? n + index : index;
	data it;

	if(i < 0 || i > n)
		return NULL;
	it = a->items[i];
	a->items[i] = NULL;
	uint k;
	for(k = i; k < n - 1; ++k)
		a->items[k] = a->items[k + 1];
	a->size--;
	return it;
}

bool removearrayitem(Array a, const data item) {
	size_t i;
	const size_t l = arraysize(a);
	for(i = 0; i < l; i++) {
		if(a->items[i] == item) {
			return droparrayitem(a, i) != NULL;
		}
	}
}
