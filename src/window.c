#include "window.h"


#include <SDL2/SDL_hints.h>

#include "array.h"
#include "array_funcs.h"
#include "inventory.h"
#include "log.h"
#include "libsdl2.h"
#include "screen.h"
#include "types.h"



#define INIT_SCREENS_NUM 4


struct window {
	SDL_Window *win;
	Renderer *ren;
	Rect geom;
	Array *screens; // TODO
	Screen *currentscreen; // This screen is the one currently displayed, so the only
	                      // who should get a graphical update
};


/* ## Ctors and dtors ## */


Window *newwindow(const str t, const Rect g, const WinFlags wf, const RenderFlags rf) {
	Window *w = malloc(sizeof(Window));
	if(!w) {
		error("malloc() error for window \"%s\"", t);
		return NULL;
	}
	SDL_Window *const win = SDL_CreateWindow(t, g.x, g.y, g.w, g.h, wf);
	if(!win) {
		error("Could not create SDL window: %s", SDL_GetError());
		return NULL;
	}
	Renderer *const ren = SDL_CreateRenderer(win, -1, rf);
	if(!ren) {
		error("Could not create renderer: %s", SDL_GetError());
		return NULL;
	}
	Array *const screens = newarray(INIT_SCREENS_NUM);
	if(!screens) {
		error("Could not instantiate array for %u screens", INIT_SCREENS_NUM);
		return NULL;
	}
	if(wf & SDL_WINDOW_FULLSCREEN_DESKTOP) {
		verbose("window is fullscreen -- setting resolution logical instead of hardware");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(ren, g.w, g.h);
	}
	w->win = win;
	w->ren = ren;
	w->geom = g;
	setwindowtitle(w, t);
	w->screens = screens;
	w->currentscreen = NULL;
	info("Init window \"%s\" (%dx%d) at (%d, %d)", t, g.w, g.h, g.x, g.y);
	return w;
}
extern Window *newwin(str title, Rect geometry);

void freewindow(Window *const w) {
	const str t = SDL_GetWindowTitle(w->win);
	const int l = strlen(t) + 1;
	char title[l];
	strncpy(title, t, l);
	SDL_DestroyWindow(w->win);
	SDL_DestroyRenderer(w->ren);
	// TODO
	free(w);
	verbose("freed window \"%s\"", title);
}


/* ## Getters and setters ## */


bool setwindowdrawcolor(Window *const w, const Color color) {
	return SDL_SetRenderDrawColor(w->ren, color.r, color.g, color.b, color.a) == 0;
}

void setwindowtitle(Window *const w, const str title) { SDL_SetWindowTitle(w->win, title); }
str getwindowtitle(const Window *const w) { return SDL_GetWindowTitle(w->win); }

Renderer *getwindowrenderer(const Window *const w) { return w->ren; }

size_t getwindoww(const Window *const w) { return w->geom.w; }
size_t getwindowh(const Window *const w) { return w->geom.h; }


/* ## Technical functions ## */

ssize_t addwindowscreen(Window *const w, Screen *const s) {
	const ssize_t i = aappend(w->screens, s);
	if(i == 0)
		w->currentscreen = s;
	return i;
}

static str _name = "";
static bool cmpscreenname(const void *const item) {
	return strcmp(getscreenname((Screen*)item), _name) == 0;
}

bool setwindowcurrentscreen(Window *const w, const str name) {
	_name = name;
	Screen *s = acond(w->screens, cmpscreenname);
	if(s) {
		w->currentscreen = s;
		return true;
	}
	return false;
}

void updatewindow(Window *const w) {
	clearwindow(w);
	if(w->currentscreen) {
		updatescreen(w->currentscreen, w);
		return;
	}
	warning("Window \"%s\" has no current screen", getwindowtitle(w));
}

bool clearwindow(Window *const w) {
	return SDL_RenderClear(w->ren) == 0;
}
void renderwindow(Window *const w) {
	SDL_RenderPresent(w->ren);
}
