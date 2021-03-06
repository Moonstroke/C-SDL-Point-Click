#include "window.h"


#include <CODS/array.h>
#include <CODS/array_funcs.h>
#include <clog.h>
#include <SDL2/SDL_hints.h> /* for SDL_HINT_RENDER_SCALE_QUALITY */



#define INIT_SCREENS_NUM 4


struct window {
	SDL_Window *win;
	SDL_Renderer *ren;
	Rect geom;
	Array *screens;
	Screen *currentscreen; /* This screen is the one currently displayed, so
	                          the only who should get a graphical update */
	void (*gameloop)(void);
};


/* ## Ctors and dtors ## */


Window *newWindow(const str t, const Rect *const g, const SDL_WindowFlags wf, const SDL_RendererFlags rf) {
	Window *w = malloc(sizeof(Window));
	if(!w) {
		fatal("malloc() error for window \"%s\"", t);
		return NULL;
	}
	SDL_Window *const win = SDL_CreateWindow(t, g->pos.x, g->pos.y, g->w, g->h, wf);
	if(!win) {
		fatal("Could not create SDL window: %s", SDL_GetError());
		free(w);
		return NULL;
	}
	SDL_Renderer *const ren = SDL_CreateRenderer(win, -1, rf);
	if(!ren) {
		fatal("Could not create renderer: %s", SDL_GetError());
		free(w);
		return NULL;
	}
	Array *const screens = a_new(INIT_SCREENS_NUM);
	if(!screens) {
		error("Could not instantiate array for %u screens", INIT_SCREENS_NUM);
	}
	w->screens = screens;
	if(wf & SDL_WINDOW_FULLSCREEN_DESKTOP) {
		verbose("window is fullscreen -- setting resolution logical instead of hardware");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(ren, g->w, g->h);
	}
	w->win = win;
	w->ren = ren;
	w->geom = *g;
	setWindowTitle(w, t);
	w->screens = screens;
	w->currentscreen = NULL;
	info("Init window \"%s\" (%dx%d) at (%d, %d)", t, g->w, g->h, g->pos.x, g->pos.y);
	return w;
}
extern Window *newWin(str, const Rect*);

void freeWindow(Window *const w) {
	const str t = SDL_GetWindowTitle(w->win);
	const int l = strlen(t) + 1;
	char title[l];
	memcpy(title, t, l);
	SDL_DestroyWindow(w->win);
	SDL_DestroyRenderer(w->ren);
	free(w);
	info("freed window \"%s\"", title);
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

unsigned int getWindowWidth(const Window *const w) {
	return w->geom.w;
}

unsigned int getWindowHeight(const Window *const w) {
	return w->geom.h;
}

Screen *getWindowCurrentScreen(Window *const w) {
	return w->currentscreen;
}

static bool cmpscreenname(const void *const item, const void *const name) {
	return strcmp(getScreenName((const Screen*)item), (const char*)name) == 0;
}
bool setWindowCurrentScreen(Window *const w, const str name) {
	Screen *s = a_cond(w->screens, name, cmpscreenname);
	if(s) {
		w->currentscreen = s;
		return true;
	}
	return false;
}

void setWindowGameLoop(Window *const w, void (*const f)(void)) {
	w->gameloop = f;
}



/* ## Technical functions ## */

Sprite *getWindowSpriteAt(const Window *const w, const Point p) {
	return getScreenSpriteAt(w->currentscreen, p);
}

int addWindowScreen(Window *const w, Screen *const s) {
	if(!w->screens && !(w->screens = a_new(INIT_SCREENS_NUM))) {
		error("Could not instantiate array for %u screens", INIT_SCREENS_NUM);
		return -1;
	}
	const int i = a_append(w->screens, s);
	if(i == 0)
		w->currentscreen = s;
	return i;
}

void updateWindow(Window *const w) {
	clearWindow(w);
	if(w->currentscreen) {
		updateScreen(w->currentscreen, w);
	} else {
		error("Window \"%s\" has no current screen", getWindowTitle(w));
	}
}

void renderWindow(Window *const w) {
	SDL_RenderPresent(w->ren);
}

bool clearWindow(Window *const w) {
	return SDL_RenderClear(w->ren) == 0;
}

void windowRun(const Window *const w) {
	if(w->gameloop)
		w->gameloop();
}
