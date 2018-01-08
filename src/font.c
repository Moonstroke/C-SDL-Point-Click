#include "font.h"

#include <stdio.h> /* for sprintf() and snprintf() */



#define FONTS_DIR "data/fonts"


Font *openFont(const str b, const unsigned int s) {
	const unsigned int l = snprintf(NULL, 0, FONTS_DIR"/%s.ttf", b) + 1;
	if(l < 1)
		return NULL;
	char f[l];
	sprintf(f, FONTS_DIR"/%s.ttf", b);
	return TTF_OpenFont(f, s);
}
