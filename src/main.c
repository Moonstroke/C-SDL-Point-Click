#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "colors.h"
#include "events.h"
#include "log.h"
#include "libsdl2.h"
#include "geom.h"
#include "scene.h"
#include "screen.h"
#include "sprite.h"
#include "texture.h"
#include "window.h"
#include "inventory.h"
#include "layout.h"


/* Static-use objects (mere references) */

static Window *win;
static Screen *screen;
static Scene *scene;
static Inventory *inventory;
static Sprite *earth, *earth2;


/* Dynamic-use objects (can change over time) */

// FIXME can't these be registers?
static Sprite *heldsprite = NULL;
static Point clickpos;


/* Event-handlers functions */

static void leftdown(const Point p);
static void leftup(const Point p);
static void move(const Point p);


/* Functions */

static void initall(void);
static void mainloop(void);



int main(void) {
	log_setfilter(LOGF_ALL);

	info("\nInitializations");
	initall();

	info("\nMain events loop");
	mainloop();

	info("\nClean and Exit");
	freewindow(win);

	return EXIT_SUCCESS;
}


void move(const Point p) {
	if(heldsprite)
		movecsprite(heldsprite, p);
}
void leftdown(const Point p) {
	clickpos = p; //point(p.x, p.y);
	heldsprite = getscenespritepos(scene, p);
}
void leftup(const Point p) {
	if(distance(clickpos, p) < MAX_CLICK_DISTANCE) { // the event is a mouse click
		if(heldsprite) {
			removescenesprite(scene, heldsprite);
			addinventorysprite(inventory, heldsprite);
			debug("sprite pos = (%d, %d)", getspritex(heldsprite), getspritey(heldsprite));
		}
		debug("inventory size = %d", inventorysize(inventory));
		debug("click pos = (%d, %d)", clickpos.x, clickpos.y);
	}

	heldsprite = NULL;
}


void mainloop(void) {
	SDL_Event event;
	bool done = false;
	Point mouse;
	while(!done) {
		while(SDL_PollEvent(&event)) {
			// TODO use SDL_AddEventWatch()?
			mouse = mousepos();
			switch(event.type) {
				case SDL_MOUSEBUTTONDOWN:
					onmousedown(event.button.button)(mouse);
					break;
				case SDL_MOUSEBUTTONUP:
					onmouseup(event.button.button)(mouse);
					break;
				case SDL_MOUSEWHEEL:
					// TODO
					break;
				case SDL_MOUSEMOTION:
					onmousemove()(mouse);
					break;
				case SDL_KEYDOWN:
					// The window can be closed with ESC, CTRL+q or CTRL+w
					switch(event.key.keysym.sym) {
						case SDLK_q:
						case SDLK_w:
							if(!(event.key.keysym.mod & KMOD_CTRL))
								break;
						case SDLK_ESCAPE:
							done = true;
							break;
						default: break;
					}
					break;
				case SDL_QUIT:
					done = true;
					break;
				default: break;
			}
		}
		updatewindow(win);
	}
}
void initall(void) {

	initSDL(SDL_INIT_VIDEO);

	Rect wingeom, scenegeom, inventorygeom;


	/* Window */

	LayoutValues layout = SCENE_INVENTORY_BELOW;

	wingeom = rect(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
	win = newwin("App window", wingeom);

	const int inventh = 80;
	setlayout(win, layout, &scenegeom, &inventorygeom, inventh);


	/* Screen(s) */
	screen = newscreen("Game screen");
	addwindowscreen(win, screen);


	/* Scene(s) */

	Texture *scenebg = loadbmptex("img/background.bmp", win);
	scene = newscene(scenegeom, scenebg, 2, "Scene1");
	setscreenscene(screen, scene);


	/* Inventory */

	Texture *inventbg = NULL; //loadbmptex("img/inventory.bmp", win);
	inventory = newinventory(inventorygeom, 8, inventbg);
	setscreeninventory(screen, inventory);


	/* Sprites */

	Texture *earthtex = loadbmptexa("img/earth.bmp", win, BLACK);
	earth = newsprite(earthtex, point(192, 240), "Earth");
	addsprite(scene, earth);

	Texture *earth2tex = loadbmptex("img/earth2.bmp", win);
	earth2 = newsprite(earth2tex, point(384, 240), "Earth2");
	addsprite(scene, earth2);


	/* Seting handlers */

	set_onmousedown(SDL_BUTTON_LEFT, leftdown);
	set_onmouseup(SDL_BUTTON_LEFT, leftup);
	set_onmousemove(move);


	/* Sandbox */
	debug("\nSANDBOX\n");

	debug("\n/SANDBOX\n");
}
