#include "screen.h"


#include "log.h"
#include <stdlib.h>
#include <string.h>

#include "inventory.h"
#include "scene.h"



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
	debug("coucou");
	setScreenName(s, name);
	return s;
}

void freeScreen(Screen *const s) {
	if(s->inventory)
		freeInventory(s->inventory);
	if(s->scene)
		freeScene(s->scene);
	free((char*)s->name);
	free(s);
}


/* ## Getters and setters ## */
str getScreenName(const Screen *const s) { return s->name; }

bool setScreenName(Screen *const s, const str name) {
	if(!name)
		return false;
	str new = strdup(name);
	if(!new) {
		warning("strdup() failed in setScreenName() \"%s\"", name);
		return false;
	}
	if(s->name)
		free((char*)s->name);
	s->name = new;
	return true;
}


Inventory *getScreenInventory(const Screen *const s) { return s->inventory; }

void setScreenInventory(Screen *const s, Inventory *const i) { s->inventory = i; }


Scene *getScreenScene(const Screen *const s) { return s->scene; }
void setScreenScene(Screen *const s, Scene *const scene) { s->scene = scene; }


/* ## Technical functions ## */

void updateScreen(Screen *s, Window *w) {
	if(s->inventory)
		updateInventory(s->inventory, w);
	if(s->scene)
		updateScene(s->scene, w);
}

