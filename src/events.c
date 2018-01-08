#include "events.h"


#include <SDL2/SDL_mouse.h> /* for SDL_GetMouseState() */

#include <log.h>



Point mousePos(void) {
	Point p;
	SDL_GetMouseState(&p.x, &p.y);
	return p;
}

static MouseHandler _onMouseDown[6];
static MouseHandler _onMouseUp[6];
static MouseHandler _onMouseMove;


static inline bool validBtn(const uint8_t btn) {
	return btn < 6;
}

// This is the default handler, used when no other one was provided
static void defaultHandler(const Point p) {
	debug("(%d, %d)\n", p.x, p.y);
}

static inline MouseHandler getHandler(const uint8_t btn, const MouseHandler *handlers) {
	return validBtn(btn) ? (handlers[btn] ? handlers[btn] : &defaultHandler)
			             : NULL;
}


bool set_OnMouseDown(const uint8_t btn, const MouseHandler handler) {
	return validBtn(btn) && (_onMouseDown[btn] = handler);
}
MouseHandler onMouseDown(const uint8_t btn) {
	return getHandler(btn, _onMouseDown);
}

bool set_OnMouseUp(const uint8_t btn, const MouseHandler handler) {
	return validBtn(btn) && (_onMouseUp[btn] = handler);
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
