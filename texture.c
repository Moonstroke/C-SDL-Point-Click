#include "texture.h"


#include "log.h"
#include "libsdl2.h"
#include "window.h"
#include "colors.h"



struct texture {
	unsigned int type; /* 0 => plain color, 1 => image texture */
	Color color;
	SDL_Texture *texture;
};


Texture *loadbmptexa(const cstr filename, const Window *const win, uint32_t colorkey) {
	Texture *tex = malloc(sizeof(Texture));
	if(!tex) {
		error("malloc() failure in loadbmptexa");
		return NULL;
	}
	SDL_Surface *bmp = SDL_LoadBMP(filename);
	if(!bmp) {
		error("Could not load BMP file \"%s\": %s", filename, SDL_GetError());
		return NULL;
	}
	if(colorkey)
		SDL_SetColorKey(bmp, true, colorkey); // FIXME
	SDL_Texture *stex = SDL_CreateTextureFromSurface(getwindowrenderer(win), bmp);
	SDL_FreeSurface(bmp); // TODO make sure this won't call SDL_SetError()
	if(!stex) {
		error("Could not load Texture from Surface: %s", SDL_GetError());
		return NULL;
	}
	tex->type = TYPE_IMAGE;
	tex->texture = stex;
	tex->color = color(0, 0, 0);
	return tex;
}
extern inline Texture *loadbmptex(cstr filename, const Window *win);


Texture *plaintex(const Window *const w, const Rect g, const Color c) {
	Texture *tex = malloc(sizeof(Texture));
	if(!tex) {
		error("malloc() failure in loadbmptexa");
		return NULL;
	}
	debug("renderer = %p", getwindowrenderer(w));
	SDL_Texture *stex = SDL_CreateTexture(getwindowrenderer(w), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, g.w, g.h);
	if(!stex) {
		error("Could not create (%dx%d) plain texture", g.w, g.h);
		return NULL;
	}
	tex->type = TYPE_PLAIN;
	tex->texture = stex;
	tex->color = c;
	return tex;
}

void freetexture(Texture *const t) {
	SDL_DestroyTexture(t->texture);
	free(t);
}

void drawtexture(Texture *const t, Window *const win, const Point pos) {
	Rect r = {.x = pos.x, .y = pos.y};
	SDL_QueryTexture(t->texture, NULL, NULL, &r.w, &r.h);
	Color backup;
	Renderer *ren = getwindowrenderer(win);
	if(t->type = TYPE_PLAIN) {
		SDL_GetRenderDrawColor(ren, &backup.r, &backup.g, &backup.b, &backup.a);
		SDL_SetRenderDrawColor(ren, t->color.r, t->color.g, t->color.b, t->color.a);

	} else
		SDL_RenderCopy(getwindowrenderer(win), t->texture, NULL, &r);
}

bool istextureplain(const Texture *const t) {
	return t->type == TYPE_PLAIN;
}

bool gettexturegeom(const Texture *const t, int *w, int *h) {
	return SDL_QueryTexture(t->texture, NULL, NULL, w, h) == 0;
}