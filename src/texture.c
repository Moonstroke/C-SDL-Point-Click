#include "texture.h"

#include <SDL2/SDL_rect.h> /* for SDL_Rect */
#include <clog.h>
#include <stdio.h> /* for snprintf */
#include <stdlib.h> /* for NULL */

#include "libsdl2.h"
#include "window.h"
#include "colors.h"



#define IMG_DIR "data/img"



Texture *loadBMPA(const str b, const Window *const w, uint32_t c) {
	const unsigned int l = snprintf(NULL, 0, IMG_DIR"/%s.bmp", b) + 1;
	if(l < 1)
		return NULL;
	char f[l];
	sprintf(f, IMG_DIR"/%s.bmp", b);

	SDL_Surface *bmp = SDL_LoadBMP(f);
	if(!bmp) {
		error("Could not load BMP file \"%s\": %s", f, SDL_GetError());
		return NULL;
	}
	if(c)
		SDL_SetColorKey(bmp, true, c); // FIXME
	Texture *tex = SDL_CreateTextureFromSurface(getWindowRenderer(w), bmp);
	SDL_FreeSurface(bmp); // TODO make sure this won't call SDL_SetError()
	if(!tex) {
		error("Could not load Texture from Surface: %s", SDL_GetError());
		return NULL;
	}
	return tex;
}
extern Texture *loadBMP(str, const Window*);


void freeTexture(Texture *const t) {
	SDL_DestroyTexture(t);
}

void drawTexture(Texture *const t, Window *const w, const Point p) {
	SDL_Rect r = {.x = p.x, .y = p.y};
	SDL_QueryTexture(t, NULL, NULL, &r.w, &r.h);
	SDL_RenderCopy(getWindowRenderer(w), t, NULL, &r);
}

bool getTextureGeom(const Texture *const t, unsigned int *w, unsigned int *h) {
	return SDL_QueryTexture((SDL_Texture*)t, NULL, NULL, (int*)w, (int*)h) == 0;
}
