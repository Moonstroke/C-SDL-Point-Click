#include "uielements.h"

#include <stdlib.h>



typedef struct uistyle {
	Color textColor, bgColor;
	Font *font;
} UIStyle;

static UIStyle style = {.textColor = {0}, .bgColor = {0}, .font = NULL};


Sprite *label(const str s, const Point p, Window *const w) {
	return button(s, p, NULL, w);
}

Sprite *button(const str s, const Point p, void (*const f)(void), Window *const w) {
	Sprite *const e = newSprite(NULL, p, s);
	if(!e)
		return NULL;

	if(!style.font) {
		/* If there is no common UI font, we can not create UI elements */
		return NULL;
	}

	const TextRenderType tr = f ? TEXTRENDER_OPAQUEBG : TEXTRENDER_SMOOTH;
	Text *const t = newText(s, style.font, style.textColor, tr);
	if(!t)
		return NULL;
	if(f) {
		/* If f != NULL (ie. the element is a button) we give it a background */
		setTextBgColor(t, style.bgColor);
	}
	Texture *tex = renderText(t, w);
	if(!tex)
		return NULL;
	setSpriteTexture(e, tex);
	return e;
}
