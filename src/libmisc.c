#include "libmisc.h"


#include <stdlib.h>
#include <string.h>



str strcopy(const str restrict orig) {
	if(!orig)
		return NULL;
	const unsigned int l = strlen(orig) + 1;
	char *const new = malloc(l);
	if(!new)
		return NULL;
	memcpy(new, orig, l);
	return new;
}

str strconcat(const str restrict s1, const str restrict s2) {
	if(!s1)
		return NULL;
		
	char *s = (char*)strcopy(s1);
	if(!s)
		return NULL;

	const unsigned int l = strlen(s1) + strlen(s2) + 1;
	char *new_s = realloc(s, l * sizeof(char));
	if(new_s) {
		free(s);
		return NULL;
	}
	strcat(new_s, s2);
	return s;
}

extern int min(int, int);
extern int max(int, int);
