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
#include "text.h"


/* Static-use objects (mere references) */

static Window *win;
static Screen *screen;
static Scene *scene;
static Inventory *inventory;
static Sprite *earth, *earth2;
static Text *tooltip;


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
	freeWindow(win);
	return EXIT_SUCCESS;
}


void move(const Point p) {
	if(heldsprite)
		moveSpriteC(heldsprite, p);
	else {
		Sprite *const s = getSceneSpritePos(scene, p);
		setTextString(tooltip, s ? getSpriteName(s) : "");
	}
}

void leftdown(const Point p) {
	clickpos = p; //point(p.x, p.y);
	heldsprite = getSceneSpritePos(scene, p);
}
void leftup(const Point p) {
	if(distance(clickpos, p) < MAX_CLICK_DISTANCE) { // the event is a mouse click
		if(heldsprite) {
			removeSceneSprite(scene, heldsprite);
			addInventorySprite(inventory, heldsprite);
			debug("sprite pos = (%d, %d)", getSpriteX(heldsprite), getSpriteY(heldsprite));
		}
		debug("inventory size = %d", inventorySize(inventory));
		debug("click pos = (%d, %d)", clickpos.x, clickpos.y);
	}

	heldsprite = NULL;
}


void mainloop(void) {
	//renderwindow(win);
	logSDLRendererInfo(getWindowRenderer(win));
	SDL_Event event;
	bool done = false;
	Point mouse;
	while(!done) {
		while(SDL_PollEvent(&event)) {
			// TODO use SDL_AddEventWatch()?
			mouse = mousePos();
			switch(event.type) {
				case SDL_MOUSEBUTTONDOWN:
					onMouseDown(event.button.button)(mouse);
					break;
				case SDL_MOUSEBUTTONUP:
					onMouseUp(event.button.button)(mouse);
					break;
				case SDL_MOUSEWHEEL:
					// TODO
					break;
				case SDL_MOUSEMOTION:
					onMouseMove()(mouse);
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
		updateWindow(win);
		if(!drawText(tooltip, win, point(mouse.x + 16, mouse.y)))
			error("ouch");
		renderWindow(win);
	}
}
void initall(void) {

	initSDL(SDL_INIT_VIDEO);

	Rect wingeom, scenegeom, inventorygeom;


	/* Window */

	LayoutValues layout = SCENE_INVENTORY_BELOW;

	wingeom = rect(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
	win = newWin("App window", wingeom);

	const int inventh = 80;
	setLayout(win, layout, &scenegeom, &inventorygeom, inventh);


	/* Screen(s) */
	screen = newScreen("Game screen");
	addWindowScreen(win, screen);


	/* Scene(s) */

	Texture *scenebg = loadBMP("img/background.bmp", win);
	scene = newScene(scenegeom, scenebg, 2, "Scene1");
	setScreenScene(screen, scene);


	/* Inventory */

	Texture *inventbg = NULL; //loadbmp("img/inventory.bmp", win);
	inventory = newInventory(inventorygeom, 8, inventbg);
	setScreenInventory(screen, inventory);


	/* Sprites */

	Texture *earthtex = loadBMPA("img/earth.bmp", win, BLACK);
	earth = newSprite(earthtex, point(192, 240), "Earth");
	addSprite(scene, earth);

	Texture *earth2tex = loadBMP("img/earth2.bmp", win);
	earth2 = newSprite(earth2tex, point(384, 240), "Earth2");
	addSprite(scene, earth2);


	/* Texts */
	Font *ubuntu = TTF_OpenFont("fonts/ubuntu_mono-regular.ttf", 16);
	if(!ubuntu) {
		fatal("Font could not be loaded: %s", TTF_GetError());
		exit(1);
	}
	tooltip = newText("", ubuntu, color(0xff, 0xff, 0xff), TEXTRENDER_FAST);
	/* Seting handlers */

	set_OnMouseDown(SDL_BUTTON_LEFT, leftdown);
	set_OnMouseUp(SDL_BUTTON_LEFT, leftup);
	set_OnMouseMove(move);


	/* Sandbox */
	debug("\nSANDBOX\n");

	debug("\n/SANDBOX\n");
}
