#include "events.h"


#include <log.h>
#include <SDL2/SDL_mouse.h> /* for SDL_GetMouseState() */
#include <stdlib.h> /* for NULL */



Point mousePos(void) {
	Point p;
	SDL_GetMouseState(&p.x, &p.y);
	return p;
}

static MouseButtonHandler _onMouseDown[5] = {NULL};
static MouseButtonHandler _onMouseUp[5] = {NULL};
static MouseButtonHandler _onMouseClick[5] = {NULL};
static MouseMotionHandler _onMouseMove = NULL;

static Point downPos = {0};


static inline bool validBtn(const uint8_t btn) {
	return 0 < btn && btn < 5;
}

/* This is the default handler, used when no other one was provided */
static void defaultHandler(const SDL_MouseButtonEvent *const restrict e) {
	debug("(%d, %d)\n", e->x, e->y);
}

static inline bool setHandler(const uint8_t btn,
                              const MouseButtonHandler handler,
                              MouseButtonHandler *const restrict handlers) {
	return validBtn(btn) && (handlers[btn - 1] = handler);
}

static inline MouseButtonHandler getHandler(const uint8_t btn, const MouseButtonHandler *const restrict handlers) {
	return validBtn(btn) ? (handlers[btn - 1] ? handlers[btn - 1] : &defaultHandler)
	                     : NULL;
}


bool set_OnMouseDown(uint8_t btn, const MouseButtonHandler handler) {
	return setHandler(btn, handler, _onMouseDown);
}

void onMouseDown(const SDL_MouseButtonEvent *const restrict e) {
	getHandler(e->button, _onMouseDown)(e);
	downPos = point(e->x, e->y);
}

bool set_OnMouseUp(const uint8_t btn, const MouseButtonHandler handler) {
	return setHandler(btn, handler, _onMouseUp);
}
void onMouseUp(const SDL_MouseButtonEvent *const restrict e) {
	getHandler(e->button, _onMouseUp)(e);
	if(distance(downPos, point(e->x, e->y)) < MAX_CLICK_DISTANCE) {
		onMouseClick(e);
	}
}

bool set_OnMouseClick(uint8_t btn, MouseButtonHandler handler) {
	return setHandler(btn, handler, _onMouseClick);
}
void onMouseClick(const SDL_MouseButtonEvent *e) {
	getHandler(e->button, _onMouseClick)(e);
}

bool set_OnMouseMove(const MouseMotionHandler handler) {
	_onMouseMove = handler;
	return true;
}
void onMouseMove(const SDL_MouseMotionEvent *const restrict e) {
	_onMouseMove(e);
}
