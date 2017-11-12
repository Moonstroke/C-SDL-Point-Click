#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "colors.h"
#include "events.h"
#include "log.h"
#include "libsdl2.h"
#include "math.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "window.h"
#include "inventory.h"
#include "layout.h"

/* Static-use objects (mere references) */

Window win;
Scene scene;
Inventory inventory;
Sprite earth, earth2;


/* Dynamic-use objects (can change over time) */

Sprite heldsprite = NULL;
DPoint clickpos;

/* Event-handlers functions */

void leftdown(CPoint p);
void leftup(CPoint p);
void move(CPoint p);

void move(CPoint p) {
	if(heldsprite)
		movecsprite(heldsprite, p);
}
void leftdown(CPoint p) {
	clickpos = point(p->x, p->y);
	heldsprite = getscenespritepos(scene, p);
}

void leftup(CPoint p) {
	if(distance(&clickpos, p) < MAX_CLICK_DISTANCE) { // the event is a mouse click
		if(heldsprite) {
			removescenesprite(scene, heldsprite);
			addinventorysprite(inventory, heldsprite);
			debug("sprite pos = (%d, %d)\n", getspritex(heldsprite), getspritey(heldsprite));
		}
		debug("inventory size = %d\n", inventorysize(inventory));
	}

	heldsprite = NULL;
}


/* Functions */

void initall(void);
void mainloop(void);

int main(int argc, str argv[]) {
	log_setfilter(ALL);

	info("\nInitializations\n");
	initall();

	info("\nMain events loop\n");
	mainloop();

	info("\nClean and Exit\n");
	freewindow(win);

	return EXIT_SUCCESS;
}

void mainloop(void) {
	SDL_Event event;
	int done = 0;
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
							done = 1;
							break;
						default: break;
					}
					break;
				case SDL_QUIT:
					done = 1;
					break;
				default: break;
			}
		}
		updatewindow(win);
	}
}

void initall(void) {

	initSDL(SDL_INIT_VIDEO);

	/* Window(s) */

	SDL_Rect wingeom, scenegeom, inventorygeom;
	LayoutValues layout = SCENE_ABOVE_INVENTORY;

	wingeom.x = wingeom.y = SDL_WINDOWPOS_CENTERED;
	wingeom.w = 640;
	wingeom.h = 480;
	win = newwin("App window", &wingeom);

	const int inventh = 80;
	setwindowlayout(win, layout, &scenegeom, &inventorygeom, inventh);

	/* Scenes */

	SDL_Rect geom = rect(16, 16, 608, 458);
	Texture scenebg = loadbmptex("img/background.bmp", win);
	scene = newscene(&scenegeom, scenebg, 2, "Scene1");
	setwindowscene(win, scene);

	/* Inventory */

	SDL_Rect inventgeom = rect(0, getwindowh(win) - inventh, getwindoww(win), inventh);
	Texture inventbg = loadbmptex("img/inventory.bmp", win);
	inventory = newinventory(&inventgeom, 8, inventbg);
	setwindowinventory(win, inventory);


	/* Sprites */

	Texture earthtex = loadbmptexa("img/earth.bmp", win, BLACK);
	earth = newsprite(earthtex, point(192, 240), "Earth");
	addsprite(scene, earth);

	Texture earth2tex = loadbmptex("img/earth2.bmp", win);
	earth2 = newsprite(earth2tex, point(384, 240), "Earth2");
	addsprite(scene, earth2);


	/* Seting handlers */

	set_onmousedown(SDL_BUTTON_LEFT, leftdown);
	set_onmouseup(SDL_BUTTON_LEFT, leftup);
	set_onmousemove(move);


	/* Sandbox */
	debug("\nSANDBOX\n");

	debug("\n/SANDBOX\n\n");
}
