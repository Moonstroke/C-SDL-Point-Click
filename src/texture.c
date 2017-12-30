#include "texture.h"


#include "log.h"
#include "libsdl2.h"
#include "window.h"
#include "colors.h"



Texture *loadBMPA(const str filename, const Window *const win, uint32_t colorkey) {
	SDL_Surface *bmp = SDL_LoadBMP(filename);
	if(!bmp) {
		error("Could not load BMP file \"%s\": %s", filename, SDL_GetError());
		return NULL;
	}
	if(colorkey)
		SDL_SetColorKey(bmp, true, colorkey); // FIXME
	Texture *tex = SDL_CreateTextureFromSurface(getWindowRenderer(win), bmp);
	SDL_FreeSurface(bmp); // TODO make sure this won't call SDL_SetError()
	if(!tex) {
		error("Could not load Texture from Surface: %s", SDL_GetError());
		return NULL;
	}
	return tex;
}
extern Texture *loadBMP(str filename, const Window *win);


void freeTexture(Texture *const t) {
	SDL_DestroyTexture(t);
}

void drawTexture(Texture *const t, Window *const win, const Point pos) {
	Rect r = {.x = pos.x, .y = pos.y};
	SDL_QueryTexture(t, NULL, NULL, &r.w, &r.h);
	SDL_RenderCopy(getWindowRenderer(win), t, NULL, &r);
}

bool getTextureGeom(const Texture *const t, int *w, int *h) {
	return SDL_QueryTexture((SDL_Texture*)t, NULL, NULL, w, h) == 0;
}
