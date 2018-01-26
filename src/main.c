#include <log.h>
#include <SDL2/SDL.h> /* for SDL_INIT_VIDEO */
#include <SDL2/SDL_events.h> /* for SDL_Event, SDL_EventType */
#include <stdbool.h>
#include <stdlib.h> /* for EXIT_SUCCESS */

#include "colors.h"
#include "geom.h"
#include "inventory.h"
#include "layout.h"
#include "libsdl2.h"
#include "mouse.h"
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

static void leftdown(const SDL_MouseButtonEvent*);
static void leftup(const SDL_MouseButtonEvent*);
static void leftclick(const SDL_MouseButtonEvent*);
static void move(const SDL_MouseMotionEvent*);


/* GUI actions */

static void startgame(void);
static void pausegame(void);


/* Functions */

static bool initall(void);
static void mainloop(void);



int main(void) {
	bool status = true;
	log_setfilter(LOGF_ALL);

	info("\nInitializations");
	status = initall();
	if(status) {
		info("\nMain events loop");
		windowRun(win);
	}

	info("\nClean and Exit");
	if(win)
		freeWindow(win);
	if(tooltip)
		freeText(tooltip);

	return status ? EXIT_SUCCESS : EXIT_FAILURE;
}


void move(const SDL_MouseMotionEvent *const restrict e) {
	const Point p = point(e->x, e->y);
	if(heldsprite) {
		moveSpriteC(heldsprite, p);
		setTextString(tooltip, "");
	} else {
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

void leftdown(const SDL_MouseButtonEvent *const restrict e) {
	const Point p = point(e->x, e->y);
	clickpos = p;
	Screen *const scr = getWindowCurrentScreen(win);
	Scene *const scn = getScreenScene(scr);
	if(isSceneUI(scn)) {
		UIElement *const el = getUISceneElementPos(scn, p);
		if(el)
			btnDown(el);
	} else {
		Inventory *const inv = getScreenInventory(scr);
		if(inv)
			heldsprite = getInventorySpritePos(inv, p);
	}
}
void leftup(const SDL_MouseButtonEvent *const restrict e) {
	const Point p = point(e->x, e->y);
	Screen *const scr = getWindowCurrentScreen(win);
	Scene *const scn = getScreenScene(scr);
	if(isSceneUI(scn)) {
		UIElement *const el = getUISceneElementPos(scn, p);
		if(el)
			btnUp(el);
	} else if(heldsprite) {
		Inventory *const inv = getScreenInventory(scr);
		removeInventorySprite(inv, heldsprite);
		addGameSceneSprite(scn, heldsprite);
		heldsprite = NULL;
	}
}
void leftclick(const SDL_MouseButtonEvent *const restrict e) {
	Screen *const scr = getWindowCurrentScreen(win);
	Scene *const scn = getScreenScene(scr);
	Inventory *const inv = getScreenInventory(scr);
	const Point pos = point(e->x, e->y);
	if(isSceneUI(scn)) {
		UIElement *const el = getUISceneElementPos(scn, pos);
		if(el) {
			btnUp(el);
			btnClick(el);
		}
	} else {
		Sprite *const spr = getGameSceneSpritePos(scn, pos);
		if(spr) {
			removeGameSceneSprite(scn, spr);
			addInventorySprite(inv, spr);
		}
	}
}
void startgame(void) {
	setWindowCurrentScreen(win, "Game screen");
}
void pausegame(void) {
	Screen *const scr = getWindowCurrentScreen(win);
	Scene *const scn = getScreenScene(scr);
	if(!isSceneUI(scn) && heldsprite) {
		Inventory *const inv = getScreenInventory(scr);
		removeInventorySprite(inv, heldsprite);
		addGameSceneSprite(scn, heldsprite);
		heldsprite = NULL;
	}
	setTextString(tooltip, "");
	setWindowCurrentScreen(win, "Menu screen");
}
void mainloop(void) {
	logSDLRendererInfo(getWindowRenderer(win));
	SDL_Event event;
	bool done = false;
	Point mouse;
	while(!done) {
		mouseUpdate();
		while(SDL_PollEvent(&event)) {
			// TODO use SDL_AddEventWatch()?
			mouse = mousePos();
			switch(event.type) {
				case SDL_MOUSEBUTTONDOWN:
					mouseDown(&event.button);
					break;
				case SDL_MOUSEBUTTONUP:
					mouseUp(&event.button);
					break;
				case SDL_MOUSEWHEEL:
					// TODO
					break;
				case SDL_MOUSEMOTION:
					mouseMove(&event.motion);
					break;
				case SDL_KEYDOWN:
					/* The window can be closed with CTRL+q or CTRL+w */
					switch(event.key.keysym.sym) {
						case SDLK_w:
							if(!(event.key.keysym.mod & KMOD_CTRL))
								break;
						case SDLK_q:
							done = true;
						/* Esc pauses the game (returns to menu screen) */
						case SDLK_ESCAPE:
							pausegame();
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
		drawText(tooltip, win, point(mouse.x + 16, mouse.y));
		renderWindow(win);
	}
}
bool initall(void) {

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
		return false;
	}
	setUIFont(ubuntu);
	setUITextColor(&black);
	setUIBgColor(&white);


	/* Window */

	wingeom = rect(640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	win = newWin("App window", &wingeom);
	if(!win) {
		return false;
	}
	setMouseForWindow(win);


	/* Layouts */

	const LayoutValues menulayout = SCENE_ONLY,
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
	gamescene = newGameScene(gamescenegeom, gamescenebg, 2, "Game");
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


	/* Event handlers */
	onMouseDown(MOUSE_BUTTON_LEFT, leftdown);
	onMouseUp(MOUSE_BUTTON_LEFT, leftup);
	onMouseClick(MOUSE_BUTTON_LEFT, leftclick);
	onMouseMove(move);

	/* Main game loop */
	setWindowGameLoop(win, mainloop);


	/* Sandbox */
	debug("\nSANDBOX\n");

	debug("\n/SANDBOX\n");

	return true;
}
