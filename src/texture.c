#include "texture.h"


#include "log.h"
#include "libsdl2.h"
#include "window.h"
#include "colors.h"



Texture *loadBMPA(const str f, const Window *const w, uint32_t c) {
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
extern Texture *loadBMP(str f, const Window *w);


void freeTexture(Texture *const t) {
	SDL_DestroyTexture(t);
}

void drawTexture(Texture *const t, Window *const w, const Point p) {
	Rect r = {.x = p.x, .y = p.y};
	SDL_QueryTexture(t, NULL, NULL, &r.w, &r.h);
	SDL_RenderCopy(getWindowRenderer(w), t, NULL, &r);
}

bool getTextureGeom(const Texture *const t, int *w, int *h) {
	return SDL_QueryTexture((SDL_Texture*)t, NULL, NULL, w, h) == 0;
}
