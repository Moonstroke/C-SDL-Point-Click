#include "text.h"


#include <stdlib.h>
#include <string.h>

#include "log.h"



struct text {
	str txt;
	Font *font;
	Color color;
	Color bg_color;
	Texture *rendered;
	TextRenderType type;
	bool needsupdate;
	padding(3);
};


Text *newtext(const str s, Font *const f, const Color tc, TextRenderType ty) {
	Text *const t = malloc(sizeof(Text));
	if(!t)
		return NULL;
	t->txt = s;
	t->font = f;
	t->color = tc;
	t->type = ty;
	t->needsupdate = true;
	return t;
}

void freetext(Text *const t) {
	SDL_DestroyTexture(t->rendered);
	TTF_CloseFont(t->font);
	free(t);
}

void settextstring(Text *const t, const str s) {
	if(strcmp(t->txt, s)) {
		t->txt = s;
		t->needsupdate = true;
	}
}

void settextbgcolor(Text *const t, Color c) {
	t->bg_color = c;
	t->needsupdate = true;
}

void settextcolor(Text *const t, Color c) {
	t->color = c;
	t->needsupdate = true;
}

static inline SDL_Surface *getsurface(const Text *const t) {
	switch(t->type) {
		case TEXTRENDER_FAST:
			return TTF_RenderUTF8_Solid(t->font, t->txt, t->color);
		case TEXTRENDER_OPAQUEBG:
			return TTF_RenderUTF8_Shaded(t->font, t->txt, t->color, t->bg_color);
		case TEXTRENDER_SMOOTH:
			return TTF_RenderUTF8_Blended(t->font, t->txt, t->color);
	}
	return NULL;
}

bool drawtext(Text *const t, Window *const w, Point p) {
	if(t->needsupdate) {
		if(strlen(t->txt)) {
			SDL_Surface *const surf = getsurface(t);
			if(!surf) {
				error("Unable to render text \"%s\"", t->txt);
				return false;
			}
			Texture *const tex = SDL_CreateTextureFromSurface(getwindowrenderer(w), surf);
			SDL_FreeSurface(surf);
			if(!tex) {
				error("Unable to create texture from rendered text surface");
				return false;
			}
			t->rendered = tex;
		} else
			t->rendered = NULL;
		t->needsupdate = false;
	}
	if(t->rendered) {
		drawtexture(t->rendered, w, p);
	}
	return true;
}
