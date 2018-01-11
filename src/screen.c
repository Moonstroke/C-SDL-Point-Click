#include "screen.h"


#include <log.h>
#include <stdlib.h> /* for malloc(), free(), NULL */



struct screen {
	str name;
	Inventory *inventory;
	Scene *scene;
};


/* ## Ctors and dtors ## */

Screen *newScreen(const str name) {
	Screen *s = malloc(sizeof(Screen));
	if(s == NULL)
		return NULL;
	s->inventory = NULL;
	s->scene = NULL;
	s->name = NULL;
	setScreenName(s, name);
	return s;
}

void freeScreen(Screen *const s) {
	if(s->inventory)
		freeInventory(s->inventory);
	if(s->scene)
		freeScene(s->scene);
	free(s);
}


/* ## Getters and setters ## */
str getScreenName(const Screen *const s) { return s->name; }

void setScreenName(Screen *const s, const str name) {
	s->name = name;
}


Inventory *getScreenInventory(const Screen *const s) { return s->inventory; }

void setScreenInventory(Screen *const s, Inventory *const i) { s->inventory = i; }


Scene *getScreenScene(const Screen *const s) { return s->scene; }
void setScreenScene(Screen *const s, Scene *const scene) { s->scene = scene; }


/* ## Technical functions ## */

void updateScreen(Screen *s, Window *w) {
	updateScene(s->scene, w);
	if(s->inventory)
		updateInventory(s->inventory, w);
	updateSceneElements(s->scene, w);
	if(s->inventory)
		updateInventorySprites(s->inventory, w);
}
