#include "events.h"

#include "log.h"

Point mousepos(void) {
	static DPoint p;
	SDL_GetMouseState(&p.x, &p.y);
	return &p;
}

mousehandler _onmousedown[6];
mousehandler _onmouseup[6];
mousehandler _onmousemove;


static inline int validbtn(Uint8 btn) {
	if(btn < 1 || btn > 5) {
		error("Invalid button value: %d\n", btn);
		return 0;
	}
	return 1;
}

static void defaulthandler(CPoint p) { debug("(%d, %d)\n", p->x, p->y); }

static inline mousehandler gethandler(Uint8 btn, mousehandler *handlers) {
	return validbtn(btn) ? (handlers[btn] ? handlers[btn] : &defaulthandler)
			             : NULL;
}


bool set_onmousedown(Uint8 btn, mousehandler handler) {
	if(validbtn(btn)) {
		_onmousedown[btn] = handler;
		return 1;
	} else
		return 0;
}
mousehandler onmousedown(Uint8 btn) { return gethandler(btn, _onmousedown); }

bool set_onmouseup(Uint8 btn, mousehandler handler) {
	if(validbtn(btn)) {
		_onmouseup[btn] = handler;
		return 1;
	} else
		return 0;
}
mousehandler onmouseup(Uint8 btn) { return gethandler(btn, _onmouseup); }

bool set_onmousemove(mousehandler handler) {
	_onmousemove = handler;
}
mousehandler onmousemove(void) { return _onmousemove; }
