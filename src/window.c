#include "window.h"


#include <SDL2/SDL_hints.h>

#include "array.h"
#include "array_funcs.h"
#include "inventory.h"
#include "log.h"
#include "screen.h"



#define INIT_SCREENS_NUM 4


struct window {
	SDL_Window *win;
	SDL_Renderer *ren;
	Rect geom;
	Array *screens; // TODO
	Screen *currentscreen; // This screen is the one currently displayed, so the only
	                      // who should get a graphical update
	void (*gameloop)(void);
};


/* ## Ctors and dtors ## */


Window *newWindow(const str t, const Rect g, const SDL_WindowFlags wf, const SDL_RendererFlags rf) {
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
	setWindowTitle(w, t);
	w->screens = screens;
	w->currentscreen = NULL;
	info("Init window \"%s\" (%dx%d) at (%d, %d)", t, g.w, g.h, g.x, g.y);
	return w;
}
extern Window *newWin(str title, Rect geometry);

void freeWindow(Window *const w) {
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


bool setWindowDrawColor(Window *const w, const Color c) {
	return SDL_SetRenderDrawColor(w->ren, c.r, c.g, c.b, c.a) == 0;
}

void setWindowTitle(Window *const w, const str title) {
	SDL_SetWindowTitle(w->win, title);
}

str getWindowTitle(const Window *const w) {
	return SDL_GetWindowTitle(w->win);
}

SDL_Renderer *getWindowRenderer(const Window *const w) {
	return w->ren;
}

size_t getWindowWidth(const Window *const w) {
	return w->geom.w;
}

size_t getWindowHeight(const Window *const w) {
	return w->geom.h;
}


/* ## Technical functions ## */

ssize_t addWindowScreen(Window *const w, Screen *const s) {
	const ssize_t i = aappend(w->screens, s);
	if(i == 0)
		w->currentscreen = s;
	return i;
}

static str _name = "";
static bool cmpscreenname(const void *const item) {
	return strcmp(getScreenName((Screen*)item), _name) == 0;
}

bool setWindowCurrentScreen(Window *const w, const str name) {
	_name = name;
	Screen *s = acond(w->screens, cmpscreenname);
	if(s) {
		w->currentscreen = s;
		return true;
	}
	return false;
}

void updateWindow(Window *const w) {
	clearWindow(w);
	if(w->currentscreen) {
		updateScreen(w->currentscreen, w);
		return;
	}
	warning("Window \"%s\" has no current screen", getWindowTitle(w));
}

void renderWindow(Window *const w) {
	SDL_RenderPresent(w->ren);
}

bool clearWindow(Window *const w) {
	return SDL_RenderClear(w->ren) == 0;
}

void setWindowGameLoop(Window *const w, void (*const f)(void)) {
	w->gameloop = f;
}

void windowRun(const Window *const w) {
	if(w->gameloop)
		w->gameloop();
}
