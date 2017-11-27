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
	Texture background;
};


Inventory newinventory(const Rect g, const size_t size, const Texture bg) {
	Inventory i = malloc(sizeof(struct inventory));
	if(i == NULL)
		return NULL;
	i->sprites = newarray(size);
	i->geom = g;
	i->background = bg;
	verbose("Init inventory with %d slots", size);
	return i;
}

void freeinventory(const Inventory i) {
	afreer(i->sprites, (void(*)(void*))&freesprite);
	free(i);
	verbose("freed %d sprites from inventory", asize(i->sprites));
}


void updateinventory(const CInventory i, const Window win) {
	if(i->background)
		drawtexture(i->background, win, point(i->geom.x, i->geom.y));
	else
		warning("Inventory has no background texture");
	size_t k = asize(i->sprites);
	while(k--)
		updatesprite(aget(i->sprites, k), win);
	//renderwindow(win);
}


size_t inventorysize(const CInventory i) {
	return asize(i->sprites);
}

Sprite getinventorysprite(const CInventory i, const ssize_t n) {
	return aget(i->sprites, n);
}

size_t addinventorysprite(const Inventory i, const Sprite s) {
	const size_t index = aappend(i->sprites, s);
	// TODO set sprite position
	Point dest = point(i->geom.x + SPRITE_RESERVED_SPACE * asize(i->sprites) + SPRITE_RESERVED_SPACE / 2,
	                   i->geom.y + SPRITE_RESERVED_SPACE / 2);
	movecsprite(s, dest);
	return index;
}

bool removeinventorysprite(const Inventory i, const CSprite s) {
	return aremove(i->sprites, s);
}
