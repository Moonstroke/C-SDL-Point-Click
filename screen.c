#include "screen.h"


#include <stdlib.h>

#include "inventory.h"
#include "scene.h"



struct screen {
	const char *name;
	Inventory *inventory;
	Scene *scene;
	// TODO
};


/* ## Ctors and dtors ## */

Screen *newscreen(const char *name) {
	Screen *s = malloc(sizeof(Screen));
	if(s == NULL)
		return NULL;
	s->inventory = NULL;
	s->scene = NULL;
	setscreenname(s, name);
	return s;
}

void freescreen(Screen *const s) {
	if(s->inventory != NULL)
		freeinventory(s->inventory);
	if(s->scene != NULL)
		freescene(s->scene);
	free(s);
}


/* ## Getters and setters ## */

const char *getscreenname(const Screen *const s) { return s->name; }

void setscreenname(Screen *const s, const char *name) { s->name = name; } // FIXME strcpy?


Inventory *getscreeninventory(const Screen *const s) { return s->inventory; }

void setscreeninventory(Screen *const s, Inventory *const i) { s->inventory = i; }


Scene *getscreenscene(const Screen *const s) { return s->scene; }
void setscreenscene(Screen *const s, Scene *const scene) { s->scene = scene; }


/* ## Technical functions ## */

void updatescreen(Screen *s, Window *w) {
	if(s->inventory != NULL)
		updateinventory(s->inventory, w);
	if(s->scene != NULL)
		updatescene(s->scene, w);
}

