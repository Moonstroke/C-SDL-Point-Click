#include "screen.h"


#include "log.h"
#include <stdlib.h>
#include <string.h>

#include "inventory.h"
#include "scene.h"



#define NAME_MAX_LEN 16


struct screen {
	char name[NAME_MAX_LEN];
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
	const unsigned int l = strlen(name) + 1;
	if(l > NAME_MAX_LEN)
		warning("\"%s\" is too long, will be truncated to %u characters", name, NAME_MAX_LEN);
	strncpy(s->name, name, l);
	s->name[l - 1] = '\0';
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

