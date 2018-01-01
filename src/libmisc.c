#include "libmisc.h"


#include <stdlib.h>
#include <string.h>



str strdup(const str orig) {
	if(!orig)
		return NULL;
	const unsigned int l = strlen(orig) + 1;
	char *const new = malloc(l);
	if(!new)
		return NULL;
	memcpy(new, orig, l);
	return new;
}
