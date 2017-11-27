#include "window.h"


#include <SDL2/SDL_hints.h>

#include "libsdl2.h"
#include "log.h"
#include "inventory.h"


struct window {
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Rect geom;
	Scene scene;
	Inventory inventory; // TODO getter and setter and free
};

Window newwindow(const cstr t, const Rect g, const WinFlags wf, const RenderFlags rf) {
	Window w = malloc(sizeof(struct window));
	if(!w) {
		error("malloc() error for window \"%s\"", t);
		return NULL;
	}
	SDL_Window *win = SDL_CreateWindow(t, g.x, g.y, g.w, g.h, wf);
	if(!win) {
		error("Could not create SDL window: %s", SDL_GetError());
		return NULL;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, rf);
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
	w->geom = g; //rect(g.x, g.y, g.w, g.h);
	w->scene = NULL;
	info("Init window \"%s\" (%dx%d) at (%d, %d)", t, g.w, g.h, g.x, g.y);
	return w;
}

void freewindow(const Window w) {
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

void updatewindow(const Window w) {
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

bool clearwindow(const Window w) {
	return SDL_RenderClear(w->ren) == 0;
}
void renderwindow(const Window w) {
	SDL_RenderPresent(w->ren);
}

bool setwindowdrawcolor(const Window w, const Color color) {
	return SDL_SetRenderDrawColor(w->ren, color.r, color.g, color.b, color.a) == 0;
}

void setwindowtitle(const Window w, const cstr title) { SDL_SetWindowTitle(w->win, title); }
cstr getwindowtitle(const CWindow w) { return SDL_GetWindowTitle(w->win); }

Renderer *getwindowrenderer(const CWindow w) { return w->ren; }

void setwindowscene(const Window w, const Scene s) { w->scene = s; }
Scene getwindowscene(const CWindow w) { return w->scene; }

void setwindowinventory(const Window w, const Inventory i) { w->inventory = i; }
Inventory getwindowinventory(const CWindow w) { return w->inventory; }

size_t getwindoww(const CWindow w) { return w->geom.w; }
size_t getwindowh(const CWindow w) { return w->geom.h; }
