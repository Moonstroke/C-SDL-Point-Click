#include "inventory.h"


#include "array.h"
#include "array_funcs.h"
#include "libsdl2.h"
#include <log.h>
#include "geom.h"
#include "texture.h"

#define SPRITE_RESERVED_SPACE 64


struct inventory {
	Rect geom;
	Array *sprites;
	Texture *background;
};


Inventory *newInventory(const Rect g, const size_t size, Texture *const bg) {
	Inventory *i = malloc(sizeof(Inventory));
	if(i == NULL)
		return NULL;
	i->sprites = newarray(size);
	i->geom = g;
	if(bg == NULL)
		warning("Inventory has no background texture");
	i->background = bg;
	verbose("Init inventory with %d slots", size);
	return i;
}

void freeInventory(Inventory *const i) {
	afreer(i->sprites, (void(*)(void*))&freeSprite);
	free(i);
	verbose("freed %d sprites from inventory", asize(i->sprites));
}


void updateInventory(const Inventory *const i, Window *const win) {
	if(i->background)
		drawTexture(i->background, win, point(i->geom.pos.x, i->geom.pos.y));
	size_t k = asize(i->sprites);
	while(k--)
		updateSprite(aget(i->sprites, k), win);
}


size_t inventorySize(const Inventory *const i) {
	return asize(i->sprites);
}

Sprite *getInventorySprite(const Inventory *const i, const ssize_t n) {
	return aget(i->sprites, n);
}

size_t addInventorySprite(Inventory *const i, Sprite *const s) {
	// FIXME sprite does not appear on screen
	const size_t index = aappend(i->sprites, s);
	Point dest = point(i->geom.pos.x + SPRITE_RESERVED_SPACE * asize(i->sprites) + SPRITE_RESERVED_SPACE / 2,
	                   i->geom.pos.y + SPRITE_RESERVED_SPACE / 2);
	moveSpriteC(s, dest);
	return index;
}

bool removeInventorySprite(Inventory *const i, const Sprite *const s) {
	return aremove(i->sprites, s);
}

static Point _pos = {0};
static bool haspos(const void *item) {
	return isPointInSprite((Sprite*)item, _pos);
}

Sprite *getInventorySpritePos(const Inventory *const i, const Point p) {
	_pos = p;
	return acond(i->sprites, haspos);
}
