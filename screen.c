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

Screen *newscreen(const str name) {
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
str getscreenname(const Screen *const s) { return s->name; }

void setscreenname(Screen *const s, const str name) {
	const unsigned int l = strlen(name) + 1;
	if(l > NAME_MAX_LEN)
		warning("\"%s\" is too long, will be truncated to %u characters", name, NAME_MAX_LEN);
	strncpy(s->name, name, l);
	s->name[l - 1] = '\0';
}


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

