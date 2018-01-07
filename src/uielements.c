#include "uielements.h"

#include <stdlib.h>


#include "text.h"



typedef struct uistyle {
	Color textColor, bgColor;
	Font *font;
} UIStyle;

static UIStyle style = {.textColor = {0}, .bgColor = {0}, .font = NULL};


void setUIFont(Font *const f) {
	style.font = f;
}

Font *getUIFont(void) {
	return style.font;
}

void setUITextColor(const Color *const c) {
	style.textColor = *c;
}

Color *getUITextColor(void) {
	return &style.textColor;
}

void setUIBgColor(const Color *const c) {
	style.bgColor = *c;
}

Color *getUIBgColor(void) {
	return &style.bgColor;
}


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
