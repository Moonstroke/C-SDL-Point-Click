#include "text.h"


#include <stdlib.h>



Texture *rendertext_fast(const str t, Font *const f, const Color c, const Window *const w) {
	SDL_Surface *const surf = TTF_RenderUTF8_Solid(f, t, c);
	if(!surf)
		return NULL;
	Texture *const tex = SDL_CreateTextureFromSurface(getwindowrenderer(w), surf);
	SDL_FreeSurface(surf);
	return tex;
}

Texture *rendertext_bg(const str t, Font *const f, const Color cfg, const Color cbg, const Window *const w) {
	SDL_Surface *const surf = TTF_RenderUTF8_Shaded(f, t, cfg, cbg);
	if(!surf)
		return NULL;
	Texture *const tex = SDL_CreateTextureFromSurface(getwindowrenderer(w), surf);
	SDL_FreeSurface(surf);
	return tex;
}

Texture *rendertext_hq(const str t, Font *const f, const Color c, const Window *const w) {
	SDL_Surface *const surf = TTF_RenderUTF8_Blended(f, t, c);
	if(!surf)
		return NULL;
	Texture *const tex = SDL_CreateTextureFromSurface(getwindowrenderer(w), surf);
	SDL_FreeSurface(surf);
	return tex;
}
