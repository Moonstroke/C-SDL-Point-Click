#include "events.h"


#include <log.h>
#include <SDL2/SDL_mouse.h> /* for SDL_GetMouseState() */



Point mousePos(void) {
	Point p;
	SDL_GetMouseState(&p.x, &p.y);
	return p;
}

static MouseButtonHandler _onMouseDown[5];
static MouseButtonHandler _onMouseUp[5];
static MouseMotionHandler _onMouseMove;


static inline bool validBtn(const uint8_t btn) {
	return 0 < btn && btn < 5;
}

/* This is the default handler, used when no other one was provided */
static void defaultHandler(const SDL_MouseButtonEvent *const restrict e) {
	debug("(%d, %d)\n", e->x, e->y);
}

static inline MouseButtonHandler getHandler(const uint8_t btn, const MouseButtonHandler *const restrict handlers) {
	return validBtn(btn) ? (handlers[btn - 1] ? handlers[btn - 1] : &defaultHandler)
	                     : NULL;
}


bool set_OnMouseDown(uint8_t btn, const MouseButtonHandler handler) {
	return validBtn(btn) && (_onMouseDown[btn - 1] = handler);
}

void onMouseDown(const SDL_MouseButtonEvent *const restrict e) {
	getHandler(e->button, _onMouseDown)(e);
}

bool set_OnMouseUp(const uint8_t btn, const MouseButtonHandler handler) {
	return validBtn(btn) && (_onMouseUp[btn - 1] = handler);
}
void onMouseUp(const SDL_MouseButtonEvent *const restrict e) {
	getHandler(e->button, _onMouseUp)(e);
}

bool set_OnMouseMove(const MouseMotionHandler handler) {
	_onMouseMove = handler;
	return true;
}
void onMouseMove(const SDL_MouseMotionEvent *const restrict e) {
	_onMouseMove(e);
}
