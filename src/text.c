#include "text.h"


#include <clog.h>
#include <SDL2/SDL_surface.h>
#include <stdlib.h> /* for malloc(), NULL, free() */
#include <string.h> /* for strcmp() */



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


Text *newText(const str s, Font *const f, const Color *const c, const TextRenderType r) {
	Text *const t = malloc(sizeof(Text));
	if(!t)
		return NULL;
	t->txt = s;
	t->font = f;
	t->color = *c;
	t->type = r;
	t->needsupdate = true;
	return t;
}

Text *newTextUIStyle(const str s, const TextRenderType r) {
	Text *t = newText(s, getUIFont(), getUITextColor(), r);
	if(!t)
		return NULL;

	if(r == TEXTRENDER_OPAQUEBG)
		setTextBgColor(t, getUIBgColor());

	return t;
}

void freeText(Text *const t) {
	SDL_DestroyTexture(t->rendered);
	TTF_CloseFont(t->font);
	free(t);
}


void setTextString(Text *const t, const str s) {
	if(strcmp(t->txt, s)) {
		t->txt = s;
		t->needsupdate = true;
	}
}

void setTextBgColor(Text *const t, const Color *const c) {
	t->bg_color = *c;
	t->needsupdate = true;
}

void settextcolor(Text *const t, const Color *const c) {
	t->color = *c;
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

Texture *renderText(Text *const t, Window *const w) {
	if(t->needsupdate) {
		if(strlen(t->txt)) {
			SDL_Surface *const surf = getsurface(t);
			if(!surf) {
				error("Unable to render text \"%s\"", t->txt);
				return NULL;
			}
			Texture *const tex = SDL_CreateTextureFromSurface(getWindowRenderer(w), surf);
			SDL_FreeSurface(surf);
			if(!tex) {
				error("Unable to create texture from rendered text surface");
				return NULL;
			}
			t->rendered = tex;
		} else
			t->rendered = NULL;
		t->needsupdate = false;
	}
	return t->rendered;
}

void drawText(Text *const t, Window *const w, Point p) {
	Texture *tex = renderText(t, w);
	if(tex) {
		drawTexture(tex, w, p);
	}
}

bool getTextGeom(const Text *const t, unsigned int *const w, unsigned int *const h) {
	if(!t->rendered) {
		*w = *h = 0;
		return false;
	} else
		return getTextureGeom(t->rendered, w, h);
}
