#include "events.h"


#include "log.h"

Point mousepos(void) {
	Point p;
	SDL_GetMouseState(&p.x, &p.y);
	return p;
}

static mousehandler _onmousedown[6];
static mousehandler _onmouseup[6];
static mousehandler _onmousemove;


static inline int validbtn(uint8_t btn) {
	if(btn < 1 || btn > 5) {
		error("Invalid button value: %d\n", btn);
		return 0;
	}
	return 1;
}

// This is the default handler, used when no other one was provided
static void defaulthandler(const Point p) { debug("(%d, %d)\n", p.x, p.y); }

static inline mousehandler gethandler(const uint8_t btn, const mousehandler *handlers) {
	return validbtn(btn) ? (handlers[btn] ? handlers[btn] : &defaulthandler)
			             : NULL;
}


bool set_onmousedown(const uint8_t btn, const mousehandler handler) {
	if(validbtn(btn)) {
		_onmousedown[btn] = handler;
		return 1;
	} else
		return 0;
}
mousehandler onmousedown(const uint8_t btn) { return gethandler(btn, _onmousedown); }

bool set_onmouseup(const uint8_t btn, const mousehandler handler) {
	if(validbtn(btn)) {
		_onmouseup[btn] = handler;
		return 1;
	} else
		return 0;
}
mousehandler onmouseup(const uint8_t btn) { return gethandler(btn, _onmouseup); }

bool set_onmousemove(const mousehandler handler) {
	_onmousemove = handler;
}
mousehandler onmousemove(void) { return _onmousemove; }
