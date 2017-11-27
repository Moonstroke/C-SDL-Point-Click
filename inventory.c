#include "inventory.h"


#include "array.h"
#include "array_funcs.h"
#include "libsdl2.h"
#include "log.h"
#include "texture.h"

#define SPRITE_RESERVED_SPACE 64


struct inventory {
	Rect geom;
	Array sprites;
	Texture *background;
};


Inventory *newinventory(const Rect g, const size_t size, Texture *const bg) {
	Inventory *i = malloc(sizeof(Inventory));
	if(i == NULL)
		return NULL;
	i->sprites = newarray(size);
	i->geom = g;
	i->background = bg;
	verbose("Init inventory with %d slots", size);
	return i;
}

void freeinventory(Inventory *const i) {
	afreer(i->sprites, (void(*)(void*))&freesprite);
	free(i);
	verbose("freed %d sprites from inventory", asize(i->sprites));
}


void updateinventory(const Inventory *const i, Window *const win) {
	if(i->background)
		drawtexture(i->background, win, point(i->geom.x, i->geom.y));
	else
		warning("Inventory has no background texture");
	size_t k = asize(i->sprites);
	while(k--)
		updatesprite(aget(i->sprites, k), win);
}


size_t inventorysize(const Inventory *const i) {
	return asize(i->sprites);
}

Sprite *getinventorysprite(const Inventory *const i, const ssize_t n) {
	return aget(i->sprites, n);
}

size_t addinventorysprite(Inventory *const i, Sprite *const s) {
	// FIXME sprite does not appear on screen
	const size_t index = aappend(i->sprites, s);
	Point dest = point(i->geom.x + SPRITE_RESERVED_SPACE * asize(i->sprites) + SPRITE_RESERVED_SPACE / 2,
	                   i->geom.y + SPRITE_RESERVED_SPACE / 2);
	movecsprite(s, dest);
	return index;
}

bool removeinventorysprite(Inventory *const i, const Sprite *const s) {
	return aremove(i->sprites, s);
}
