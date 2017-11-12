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

Window newwindow(const str t, CRect g, const SDL_WindowFlags wf, const SDL_RendererFlags rf) {
	Window w = malloc(sizeof(struct window));
	if(!w) {
		error("malloc() error for window \"%s\"\n", t);
		return NULL;
	}
	SDL_Window *win = SDL_CreateWindow(t, g->x, g->y, g->w, g->h, wf);
	if(!win) {
		error("Could not create SDL window: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, rf);
	if(!ren) {
		error("Could not create renderer: %s\n", SDL_GetError());
		return NULL;
	}
	if(wf & SDL_WINDOW_FULLSCREEN_DESKTOP) {
		verbose("window is fullscreen -- setting resolution logical instead of hardware");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(ren, g->w, g->h);
	}
	w->win = win;
	w->ren = ren;
	w->geom = rect(g->x, g->y, g->w, g->h);
	w->scene = NULL;
	info("Init window \"%s\" (%dx%d) at (%d, %d)\n", t, g->w, g->h, g->x, g->y);
	return w;
}

void freewindow(Window w) {
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
	verbose("freed window \"%s\"\n", title);
}

void updatewindow(Window w) {
	clearwindow(w);
	if(!w->scene) {
		warning("scene of window \"%s\" is not set\n", getwindowtitle(w));
		return;
	} else
		updatescene(w->scene, w);
	if(!w->inventory) {
		warning("inventory of window \"%s\" is not set\n", getwindowtitle(w));
		return;
	} else
		updateinventory(w->inventory, w);
}

bool clearwindow(Window w) {
	return SDL_RenderClear(w->ren) == 0;
}
void renderwindow(Window w) {
	SDL_RenderPresent(w->ren);
}

bool setwindowdrawcolor(Window w, const SDL_Color *color) {
	return SDL_SetRenderDrawColor(w->ren, color->r, color->g, color->b, color->a) == 0;
}

inline void setwindowtitle(Window w, const str title) { SDL_SetWindowTitle(w->win, title); }
inline cstr getwindowtitle(const Window w) { return SDL_GetWindowTitle(w->win); }

inline SDL_Renderer *getwindowrenderer(const Window w) { return w->ren; }

inline void setwindowscene(Window w, Scene s) { w->scene = s; }
inline Scene getwindowscene(const Window w) { return w->scene; }

inline void setwindowinventory(Window w, Inventory i) { w->inventory = i; }
inline Inventory getwindowinventory(const Window w) { return w->inventory; }

inline const size_t getwindoww(const Window w) { return w->geom.w; }
inline const size_t getwindowh(const Window w) { return w->geom.h; }
