#include "mouse.h"

#include <log.h>
#include <SDL2/SDL_mouse.h> /* for SDL_GetMouseState() */
#include <stdlib.h> /* for NULL */

#include "libmisc.h" /* for padding() */



static void default_downhandler(const SDL_MouseButtonEvent *const e) {
	debug("button #%d down at (%d, %d)", e->button, e->x, e->y);
}
static void default_uphandler(const SDL_MouseButtonEvent *const e) {
	debug("button #%d up at (%d, %d)", e->button, e->x, e->y);
}
static void default_clickhandler(const SDL_MouseButtonEvent *const e) {
	debug("button #%d click at (%d, %d)", e->button, e->x, e->y);
}
static void default_wheelhandler(const SDL_MouseWheelEvent *const e) {
	debug("wheel event by (%d, %d)", e->x, e->y);
}
static void default_movehandler(const SDL_MouseMotionEvent *const e) {
	debug("mouse move to (%d, %d) with delta of (%d, %d)", e->x, e->y, e->xrel, e->yrel);
}


struct mouse {
	Point pos, delta;
	MouseButtonHandler *downhandlers[5];
	MouseButtonHandler *uphandlers[5];
	MouseButtonHandler *clickhandlers[5];
	MouseWheelHandler *wheelhandlers[4];
	MouseMotionHandler *movehandler;
	MouseButton btnstate;
	padding(4);
};

static struct mouse mouse = {
	.pos = {0},
	.delta = {0},
	.downhandlers = {default_downhandler},
	.uphandlers = {default_uphandler},
	.clickhandlers = {default_clickhandler},
	.wheelhandlers = {default_wheelhandler},
	.movehandler = default_movehandler,
	.btnstate = MOUSE_BUTTON_NONE,
};



Point mousePos(void) {
	return mouse.pos;
}
Point mousePosDelta(void) {
	return mouse.delta;
}


MouseButton mouseUpdate(void) {
	mouse.btnstate = SDL_GetMouseState(&mouse.pos.x, &mouse.pos.y);
	SDL_GetRelativeMouseState(&mouse.delta.x, &mouse.delta.y);
	// TODO
	return mouse.btnstate;
}



/* ## Mouse button events ## */


static inline bool validbtn(const uint8_t btn) {
	return 0 < btn && btn < 5;
}
static inline bool sethandler(const uint8_t btn, MouseButtonHandler *const handler, MouseButtonHandler *handlers[]) {
	return validbtn(btn) && (handlers[btn] = handler) != NULL;
}

/* empty function to avoid SEGFAULTs with instructions like gethandler(...)(event) */
static void noop() {}
static inline MouseButtonHandler *gethandler(const uint8_t btn, MouseButtonHandler *const handlers[]) {
	return validbtn(btn) ? handlers[btn] : noop;
}

bool onMouseDown(const uint8_t btn, MouseButtonHandler *const handler) {
	return sethandler(btn, handler, mouse.downhandlers);
}

void mouseDown(const SDL_MouseButtonEvent *const e) {
	gethandler(e->button, mouse.downhandlers)(e);

}

bool onMouseUp(const uint8_t btn, MouseButtonHandler *const handler) {
	return sethandler(btn, handler, mouse.uphandlers);
}
void mouseUp(const SDL_MouseButtonEvent *const e) {
	gethandler(e->button, mouse.uphandlers)(e);
	if(distance(mouse.pos, point(e->x, e->y)) < MAX_CLICK_DISTANCE) {
		debug("clic");
		mouseClick(e);
	}
}

bool onMouseClick(const uint8_t btn, MouseButtonHandler *const handler) {
	return sethandler(btn, handler, mouse.clickhandlers);
}
void mouseClick(const SDL_MouseButtonEvent *const e) {
	gethandler(e->button, mouse.clickhandlers)(e);
}



/* ## Mouse motion events ## */


bool onMouseMove(MouseMotionHandler *const handler) {
	mouse.movehandler = handler;
	return true;
}
void mouseMove(const SDL_MouseMotionEvent *const e) {
	mouse.movehandler(e);
}
