#include "events.h"


#include <SDL2/SDL_mouse.h> /* for SDL_GetMouseState() */

#include <log.h>



Point mousePos(void) {
	Point p;
	SDL_GetMouseState(&p.x, &p.y);
	return p;
}

static MouseHandler _onMouseDown[5];
static MouseHandler _onMouseUp[5];
static MouseHandler _onMouseMove;


static inline bool validBtn(const uint8_t btn) {
	return 0 < btn && btn < 5;
}

// This is the default handler, used when no other one was provided
static void defaultHandler(const Point p) {
	debug("(%d, %d)\n", p.x, p.y);
}

static inline MouseHandler getHandler(const uint8_t btn, const MouseHandler *handlers) {
	return validBtn(btn) ? (handlers[btn - 1] ? handlers[btn - 1] : &defaultHandler)
	                     : NULL;
}


bool set_OnMouseDown(const uint8_t btn, const MouseHandler handler) {
	return validBtn(btn) && (_onMouseDown[btn - 1] = handler);
}
MouseHandler onMouseDown(const uint8_t btn) {
	return getHandler(btn, _onMouseDown);
}

bool set_OnMouseUp(const uint8_t btn, const MouseHandler handler) {
	return validBtn(btn) && (_onMouseUp[btn - 1] = handler);
}
MouseHandler onMouseUp(const uint8_t btn) {
	return getHandler(btn, _onMouseUp);
}

bool set_OnMouseMove(const MouseHandler handler) {
	_onMouseMove = handler;
	return true;
}
MouseHandler onMouseMove(void) {
	return _onMouseMove;
}
