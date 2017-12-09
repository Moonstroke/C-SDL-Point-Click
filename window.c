#include "window.h"


#include <SDL2/SDL_hints.h>

#include "array.h"
#include "array_funcs.h"
#include "inventory.h"
#include "log.h"
#include "libsdl2.h"
#include "screen.h"



struct window {
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Rect geom;
	Array *screens; // TODO
	Screen *currentscreen; // This screen is the one currently displayed, so the only
	                      // who should get a graphical update
};


/* ## Ctors and dtors ## */


Window *newwindow(const cstr t, const Rect g, const WinFlags wf, const RenderFlags rf) {
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
	SDL_Renderer *const ren = SDL_CreateRenderer(win, -1, rf);
	if(!ren) {
		error("Could not create renderer: %s", SDL_GetError());
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
	// TODO screens
	w->currentscreen = NULL;
	info("Init window \"%s\" (%dx%d) at (%d, %d)", t, g.w, g.h, g.x, g.y);
	return w;
}
extern Window *newwin(cstr title, Rect geometry);

void freewindow(Window *const w) {
	cstr t = SDL_GetWindowTitle(w->win);
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

void setwindowtitle(Window *const w, const cstr title) { SDL_SetWindowTitle(w->win, title); }
cstr getwindowtitle(const Window *const w) { return SDL_GetWindowTitle(w->win); }

Renderer *getwindowrenderer(const Window *const w) { return w->ren; }

size_t getwindoww(const Window *const w) { return w->geom.w; }
size_t getwindowh(const Window *const w) { return w->geom.h; }


/* ## Technical functions ## */

bool setwindowcurrentscreen(Window *const w, const cstr name) {
	bool pred(const void *const item) {
		Screen *const s = (Screen*)item;
		return strcmp(getscreenname(s), name) == 0;
	}
	Screen *s = acond(w->screens, pred);
	if(s == NULL) {
		return false;
	}
	w->currentscreen = s;
	return true;
}

void updatewindow(Window *const w) {
	clearwindow(w);
	if(!w->currentscreen) {
		warning("Window \"%s\" has no current screen", getwindowtitle(w));
		return;
	} else
		updatescreen(w->currentscreen, w);
}

bool clearwindow(Window *const w) {
	return SDL_RenderClear(w->ren) == 0;
}
void renderwindow(Window *const w) {
	SDL_RenderPresent(w->ren);
}
