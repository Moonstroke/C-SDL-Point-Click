#include "uielements.h"


#include <log.h>
#include <stdlib.h> /* for malloc(), NULL and free() */

#include "libmisc.h"
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



struct uielement {
	Text *text;
	str hint;
	Point pos;
	void (*action)(void);
	bool needsupdate;
	padding(7);
};


UIElement *label(const str s, const Point p) {
	return button(s, p, NULL);
}

UIElement *button(const str s, const Point p, void (*const f)(void)) {
	if(!style.font) {
		/* If there is no common UI font, we can not create UI elements */
		return NULL;
	}

	UIElement *const e = malloc(sizeof(UIElement));
	if(!e)
		return NULL;

	const TextRenderType r = f ? TEXTRENDER_OPAQUEBG : TEXTRENDER_SMOOTH;
	Text *const t = newText(s, style.font, &style.textColor, r);
	if(!t) {
		free(e);
		return NULL;
	}
	if(f) {
		/* If f != NULL (ie. the element is a button) we give it a background */
		setTextBgColor(t, &style.bgColor);
	}

	e->text = t;
	e->hint = "";
	e->pos = p;
	e->action = f;

	return e;
}


void freeUIElement(UIElement *const e) {
	freeText(e->text);
	free(e);
}


bool uielementNeedsUpdate(const UIElement *const e) {
	return e->needsupdate;
}

void updateUIElement(UIElement *const e, Window *const w) {
	drawText(e->text, w, e->pos);
	e->needsupdate = false;
}

bool isPointInUIElement(const UIElement *const e, const Point p) {
	unsigned int w, h;
	if(!getTextGeom(e->text, &w, &h))
		return false;
	const Rect r = posRect(w, h, e->pos.x, e->pos.y);
	return isPointInRect(p, &r);
}


void btnHover(UIElement *const e) {
	(void)e;// TODO brighten button (radial gradient?)
}

void btnDown(UIElement *const e) {
	if(e->action) { /* <=> e is a button */
		e->pos.y += 1;
	}
}

void btnUp(UIElement *const e) {
	if(e->action) { /* <=> e is a button */
		e->pos.y -= 1;
	}
}

void btnClick(const UIElement *const b) {
	if(b->action)
		b->action();
}
