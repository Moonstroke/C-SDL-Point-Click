#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdbool.h>


typedef void *data;

/**
 * Opaque type definition
 */
typedef struct array *Array;

/**
 * Initializer method
 * Constructs an array of `size` slots, with `size` times `itemsize` allocated
 * memory
 */
Array newarray(const size_t size, const size_t itemsize);


/**
 * Frees an array, also frees items using given function if not NULL.
 * If one makes an array of user-defined type, an own freemytype(MyType*) func
 * will be defined and cast to 'void (*)(void*)' there.
 *
 * NOTE: function pointers casts arre usually undefined behavior, but if the
 * suitable function is provided, a cast to void* should not cause undefined
 * behaviour.
 */
void freerarray(Array array, void (*freeitems)(data));

inline void freearray(Array array) { freerarray(array, NULL); }


/**
 * Gives the size of an array
 */
unsigned int arraysize(const Array array);

/**
 * Adds an item to an array
 * Returns its position in the elements (index starting from 0) or -1 if
 * an error occurred (memory allocation failed)
 */
int addarrayitem(Array array, data item);

/**
 * Retrieves an element of an array from its index or NULL if index is invalid
 * An index is valid if and only if:
 *     -arraysize(array) <= index < -1 || 0 <= index < arraysize(array)
 */
data getarrayitem(const Array array, const ssize_t index);

/**
 * Removes an element from an array
 * Returns -1 if index is invalid (see above) or the new size of the array,
 * which can be 0
 */
data droparrayitem(Array array, const ssize_t index);

bool removearrayitem(Array array, const data item);

#endif /* ARRAY_H */
