#include "events.h"


#include <SDL2/SDL_mouse.h>

#include "log.h"



Point mousePos(void) {
	Point p;
	SDL_GetMouseState(&p.x, &p.y);
	return p;
}

static MouseHandler _OnMouseDown[6];
static MouseHandler _OnMouseUp[6];
static MouseHandler _OnMouseMove;


static inline int validBtn(uint8_t btn) {
	if(btn < 1 || btn > 5) {
		error("Invalid button value: %d\n", btn);
		return 0;
	}
	return 1;
}

// This is the default handler, used when no other one was provided
static void defaultHandler(const Point p) { debug("(%d, %d)\n", p.x, p.y); }

static inline MouseHandler getHandler(const uint8_t btn, const MouseHandler *handlers) {
	return validBtn(btn) ? (handlers[btn] ? handlers[btn] : &defaultHandler)
			             : NULL;
}


bool set_OnMouseDown(const uint8_t btn, const MouseHandler handler) {
	if(validBtn(btn)) {
		_OnMouseDown[btn] = handler;
		return 1;
	} else
		return 0;
}
MouseHandler onMouseDown(const uint8_t btn) { return getHandler(btn, _OnMouseDown); }

bool set_OnMouseUp(const uint8_t btn, const MouseHandler handler) {
	if(validBtn(btn)) {
		_OnMouseUp[btn] = handler;
		return 1;
	} else
		return 0;
}
MouseHandler onMouseUp(const uint8_t btn) { return getHandler(btn, _OnMouseUp); }

bool set_OnMouseMove(const MouseHandler handler) {
	_OnMouseMove = handler;
	return true;
}
MouseHandler onMouseMove(void) { return _OnMouseMove; }
