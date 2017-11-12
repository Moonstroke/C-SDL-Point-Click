#include "texture.h"

#include "log.h"
#include "libsdl2.h"
#include "window.h"
#include "colors.h"



struct texture {
	/*
	 * 0: plain color
	 * 1: image texture
	 */
	unsigned int type;
	SDL_Texture *texture;
	SDL_Color color;
};


Texture loadbmptexa(const char *filename, Window win, Uint32 colorkey) {
	Texture tex = malloc(sizeof(struct texture));
	if(!tex) {
		error("malloc() failure in loadbmptexa\n");
		return NULL;
	}
	SDL_Surface *bmp = SDL_LoadBMP(filename);
	if(!bmp) {
		error("Could not load BMP file \"%s\": %s\n", filename, SDL_GetError());
		return NULL;
	}
	if(colorkey)
		SDL_SetColorKey(bmp, SDL_TRUE, colorkey); // FIXME
	SDL_Texture *stex = SDL_CreateTextureFromSurface(getwindowrenderer(win), bmp);
	SDL_FreeSurface(bmp); // TODO make sure this won't call SDL_SetError()
	if(!stex) {
		error("Could not load Texture from Surface: %s\n", SDL_GetError());
		return NULL;
	}
	tex->type = TYPE_IMAGE;
	tex->texture = stex;
	tex->color = color(0, 0, 0);
	return tex;
}

Texture plaintex(const Window w, const SDL_Rect *g, const SDL_Color *c) {
	Texture tex = malloc(sizeof(Texture));
	if(!tex) {
		error("malloc() failure in loadbmptexa\n");
		return NULL;
	}
	debug("renderer = %p\n", getwindowrenderer(w));
	SDL_Texture *stex = SDL_CreateTexture(getwindowrenderer(w), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, g->w, g->h);
	if(!stex) {
		error("Could not create (%dx%d) plain texture\n", g->w, g->h);
		return NULL;
	}
	tex->type = TYPE_PLAIN;
	tex->texture = stex;
	tex->color = colora(c->r, c->g, c->b, c->a);
	return tex;
}

void freetexture(Texture texture) {
	SDL_DestroyTexture(texture->texture);
	free(texture);
}

void drawtexture(Texture t, Window win, const SDL_Point pos) {
	SDL_Rect r = {.x = pos.x, .y = pos.y};
	SDL_QueryTexture(t->texture, NULL, NULL, &r.w, &r.h);
	SDL_Color backup;
	SDL_Renderer *ren = getwindowrenderer(win);
	if(t->type = TYPE_PLAIN) {
		SDL_GetRenderDrawColor(ren, &backup.r, &backup.g, &backup.b, &backup.a);
		SDL_SetRenderDrawColor(ren, t->color.r, t->color.g, t->color.b, t->color.a);

	} else
		SDL_RenderCopy(getwindowrenderer(win), t->texture, NULL, &r);
}

bool istextureplain(const Texture t) {
	return t->type == TYPE_PLAIN;
}

bool gettexturegeom(const Texture t, int *w, int *h) {
	return SDL_QueryTexture(t->texture, NULL, NULL, w, h) == 0;
}