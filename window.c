#include "window.h"


#include <SDL2/SDL_hints.h>

#include "libsdl2.h"
#include "log.h"
#include "inventory.h"


struct window {
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Rect geom;
	Scene *scene;
	Inventory *inventory;
};

Window *newwindow(const cstr t, const Rect g, const WinFlags wf, const RenderFlags rf) {
	Window *w = malloc(sizeof(Window));
	if(!w) {
		error("malloc() error for window \"%s\"", t);
		return NULL;
	}
	if(!initwindow(w, t, g, wf, rf))
		return NULL;
	info("Init window \"%s\" (%dx%d) at (%d, %d)", t, g.w, g.h, g.x, g.y);
	return w;
}
extern Window *newwin(cstr title, Rect geometry);

bool initwindow(Window *const w, const cstr t, const Rect g, const WinFlags wf, const RenderFlags rf) {
	SDL_Window *const win = SDL_CreateWindow(t, g.x, g.y, g.w, g.h, wf);
	if(!win) {
		error("Could not create SDL window: %s", SDL_GetError());
		return false;
	}
	SDL_Renderer *const ren = SDL_CreateRenderer(win, -1, rf);
	if(!ren) {
		error("Could not create renderer: %s", SDL_GetError());
		return false;
	}
	if(wf & SDL_WINDOW_FULLSCREEN_DESKTOP) {
		verbose("window is fullscreen -- setting resolution logical instead of hardware");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(ren, g.w, g.h);
	}
	w->win = win;
	w->ren = ren;
	w->geom = g; //rect(g.x, g.y, g.w, g.h);
	w->scene = NULL;
	return true;
}
extern bool initwin(Window *w, cstr t, Rect g);

void freewindow(Window *const w) {
	cstr t = SDL_GetWindowTitle(w->win);
	const int l = strlen(t) + 1;
	char title[l];
	strncpy(title, t, l);
	SDL_DestroyWindow(w->win);
	SDL_DestroyRenderer(w->ren);
	if(w->scene)
		freescene(w->scene);
	if(w->inventory)
		freeinventory(w->inventory);
	free(w);
	verbose("freed window \"%s\"", title);
}

void updatewindow(Window *const w) {
	clearwindow(w);
	if(!w->scene) {
		warning("scene of window \"%s\" is not set", getwindowtitle(w));
		return;
	} else
		updatescene(w->scene, w);
	if(!w->inventory) {
		warning("inventory of window \"%s\" is not set", getwindowtitle(w));
		return;
	} else
		updateinventory(w->inventory, w);
}

bool clearwindow(Window *const w) {
	return SDL_RenderClear(w->ren) == 0;
}
void renderwindow(Window *const w) {
	SDL_RenderPresent(w->ren);
}

bool setwindowdrawcolor(Window *const w, const Color color) {
	return SDL_SetRenderDrawColor(w->ren, color.r, color.g, color.b, color.a) == 0;
}

void setwindowtitle(Window *const w, const cstr title) { SDL_SetWindowTitle(w->win, title); }
cstr getwindowtitle(const Window *const w) { return SDL_GetWindowTitle(w->win); }

Renderer *getwindowrenderer(const Window *const w) { return w->ren; }

void setwindowscene(Window *const w, Scene *const s) { w->scene = s; }
Scene *getwindowscene(const Window *const w) { return w->scene; }

void setwindowinventory(Window *const w, Inventory *const i) { w->inventory = i; }
Inventory *getwindowinventory(const Window *const w) { return w->inventory; }

size_t getwindoww(const Window *const w) { return w->geom.w; }
size_t getwindowh(const Window *const w) { return w->geom.h; }
