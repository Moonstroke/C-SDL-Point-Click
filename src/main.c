#include <log.h>
#include <SDL2/SDL.h> /* for SDL_INIT_VIDEO */
#include <SDL2/SDL_events.h> /* for SDL_Event, SDL_EventType */
#include <stdbool.h>
#include <stdlib.h> /* for EXIT_SUCCESS */

#include "colors.h"
#include "events.h"
#include "geom.h"
#include "inventory.h"
#include "layout.h"
#include "libsdl2.h"
#include "scene.h"
#include "screen.h"
#include "sprite.h"
#include "text.h"
#include "texture.h"
#include "uielements.h"
#include "window.h"


/* Static-use objects (mere references) */

static Window *win;
static Text *tooltip;


/* Dynamic-use objects (can change over time) */

static Sprite *heldsprite = NULL;
static Point clickpos;


/* Event-handlers functions */

static void leftdown(const Point p);
static void leftup(const Point p);
static void move(const Point p);


/* GUI actions */

static void startgame(void);


/* Functions */

static void initall(void);
static void mainloop(void);



int main(void) {
	log_setfilter(LOGF_ALL);

	info("\nInitializations");
	initall();

	info("\nMain events loop");
	windowRun(win);

	info("\nClean and Exit");
	freeWindow(win);
	freeText(tooltip);

	return EXIT_SUCCESS;
}


void move(const Point p) {
	if(heldsprite)
		moveSpriteC(heldsprite, p);
	else {
		Screen *const scr = getWindowCurrentScreen(win);
		Scene *const sce = getScreenScene(scr);
		if(isSceneUI(sce)) {
			UIElement *const el = getUISceneElementPos(sce, p);
			if(el)
				btnHover(el);
		} else {
			Inventory *const inv = getScreenInventory(scr);
			if(inv) {
				Sprite *const s = getInventorySpritePos(inv, p);
				setTextString(tooltip, s ? getSpriteName(s) : "");
			}
		}
	}
}

void leftdown(const Point p) {
	clickpos = p;
	Scene *const scene = getScreenScene(getWindowCurrentScreen(win));
	if(isSceneUI(scene)) {
		UIElement *const el = getUISceneElementPos(scene, p);
		if(el)
			btnDown(el);
	} else
		heldsprite = getGameSceneSpritePos(scene, p);
}
void leftup(const Point p) {
	Scene *const scene = getScreenScene(getWindowCurrentScreen(win));
	Inventory *const inv = getScreenInventory(getWindowCurrentScreen(win));
	if(distance(clickpos, p) < MAX_CLICK_DISTANCE) {
		/* The event is a mouse click */
		if(isSceneUI(scene)) {
			UIElement *const el = getUISceneElementPos(scene, p);
			if(el) {
				btnUp(el);
				btnClick(el);
			}
		} else if(heldsprite && inv) {
			removeGameSceneSprite(scene, heldsprite);
			addInventorySprite(inv, heldsprite);
			debug("sprite pos = (%d, %d)", getSpriteX(heldsprite), getSpriteY(heldsprite));
		}
		debug("inventory size = %d", inv ? (signed)inventorySize(inv) : -1);
		debug("click pos = (%d, %d)", clickpos.x, clickpos.y);
	}

	heldsprite = NULL;
}

void startgame(void) {
	setWindowCurrentScreen(win, "Game screen");
}

void mainloop(void) {
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

	Screen *menu, *game;
	Scene *menuscene, *gamescene;
	Inventory *gameinventory;
	Sprite *earth, *earth2;
	UIElement *startBtn;


	initSDL(SDL_INIT_VIDEO);

	Rect wingeom, menuscenegeom, gamescenegeom, gameinventorygeom;
	const Color white = color(0xff, 0xff, 0xff),
	            black = color(0, 0, 0);


	Font *ubuntu = openFont("ubuntu_mono-regular", 16);
	if(!ubuntu) {
		fatal("Font could not be loaded: %s", TTF_GetError());
		exit(1);
	}
	setUIFont(ubuntu);
	setUITextColor(&black);
	setUIBgColor(&white);


	/* Window */

	wingeom = rect(640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	win = newWin("App window", &wingeom);


	/* Layouts */

	LayoutValues menulayout = SCENE_ONLY,
	             gamelayout = SCENE_INVENTORY_BELOW;

	setLayout(win, menulayout, &menuscenegeom, NULL, 0);

	const int inventh = 80;
	setLayout(win, gamelayout, &gamescenegeom, &gameinventorygeom, inventh);


	/* Screen(s) */

	menu = newScreen("Menu screen");
	addWindowScreen(win, menu);

	game = newScreen("Game screen");
	addWindowScreen(win, game);


	/* Scene(s) */

	Texture *menuscenebg = loadBMP("menuscene_bg", win);
	menuscene = newUIScene(menuscenegeom, menuscenebg, 0, "Menu");
	setScreenScene(menu, menuscene);

	Texture *gamescenebg = loadBMP("gamescene_bg", win);
	gamescene = newGameScene(gamescenegeom, gamescenebg, 2, "Scene1");
	setScreenScene(game, gamescene);


	/* Inventory */

	Texture *inventbg = loadBMP("gameinventory_bg", win);
	gameinventory = newInventory(&gameinventorygeom, 8, inventbg);
	setScreenInventory(game, gameinventory);


	/* Sprites */

	startBtn = button("Start game", point(32, 64), startgame);
	addUISceneElement(menuscene, startBtn);

	Texture *earthtex = loadBMPA("earth", win, BLACK);
	earth = newSprite(earthtex, point(192, 240), "Earth");
	addGameSceneSprite(gamescene, earth);

	Texture *earth2tex = loadBMP("earth2", win);
	earth2 = newSprite(earth2tex, point(384, 240), "Earth2");
	addGameSceneSprite(gamescene, earth2);


	/* Texts */
	tooltip = newText("", ubuntu, &white, TEXTRENDER_FAST);
	/* Seting handlers */

	set_OnMouseDown(SDL_BUTTON_LEFT, leftdown);
	set_OnMouseUp(SDL_BUTTON_LEFT, leftup);
	set_OnMouseMove(move);
	setWindowGameLoop(win, mainloop);

	/* Sandbox */
	debug("\nSANDBOX\n");

	debug("\n/SANDBOX\n");
}
