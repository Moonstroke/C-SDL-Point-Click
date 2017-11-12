#include "inventory.h"

#include "array.h"
#include "libsdl2.h"
#include "log.h"
#include "texture.h"

#define SPRITE_RESERVED_SPACE 64


struct inventory {
	DRect geom;
	Array sprites;
	Texture background;
};


Inventory newinventory(CRect g, const size_t size, Texture bg) {
	Inventory i = malloc(sizeof(struct inventory));
	if(i == NULL)
		return NULL;
	i->sprites = newarray(size, sizeof(void*));
	i->geom = rect(g->x, g->y, g->w, g->h);
	i->background = bg;
	verbose("Init inventory with %d slots\n", size);
	return i;
}

void freeinventory(Inventory i) {
	freerarray(i->sprites, (void(*)(void*))&freesprite);
	free(i);
	verbose("freed %d sprites from inventory\n", arraysize(i->sprites));
}


void updateinventory(Inventory i, Window win) {
	if(i->background)
		drawtexture(i->background, win, point(i->geom.x, i->geom.y));
	else
		warning("Inventory has no background texture\n");
	size_t k = arraysize(i->sprites);
	while(k--)
		updatesprite(getarrayitem(i->sprites, k), win);
	//renderwindow(win);
}


size_t inventorysize(const Inventory i) {
	return arraysize(i->sprites);
}

Sprite getinventorysprite(const Inventory i, const ssize_t n) {
	return getarrayitem(i->sprites, n);
}

size_t addinventorysprite(Inventory i, Sprite s) {
	const size_t index = addarrayitem(i->sprites, s);
	// TODO set sprite position
	DPoint dest = point(i->geom.x + SPRITE_RESERVED_SPACE * arraysize(i->sprites) + SPRITE_RESERVED_SPACE / 2,
	                    i->geom.y + SPRITE_RESERVED_SPACE / 2);
	movecsprite(s, &dest);
	return index;
}

bool removeinventorysprite(Inventory i, const Sprite s) {
	return removearrayitem(i->sprites, s);
}
