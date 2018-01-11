#include "inventory.h"


#include <array.h>
#include <array_funcs.h>
#include <log.h>



#define SPRITE_RESERVED_SPACE 64


struct inventory {
	Rect geom;
	Array *sprites;
	Texture *background;
};


Inventory *newInventory(const Rect *const g, const unsigned int n, Texture *const bg) {
	Inventory *i = malloc(sizeof(Inventory));
	if(i == NULL)
		return NULL;
	i->sprites = newarray(n);
	i->geom = *g;
	if(bg == NULL)
		warning("Inventory has no background texture");
	i->background = bg;
	verbose("Init inventory with %u slots", n);
	return i;
}

void freeInventory(Inventory *const i) {
	afreer(i->sprites, (void(*)(void*))&freeSprite);
	free(i);
	verbose("freed %d sprites from inventory", asize(i->sprites));
}


void updateInventory(Inventory *const i, Window *const w) {
	if(i->background)
		drawTexture(i->background, w, point(i->geom.pos.x, i->geom.pos.y));
}
void updateInventorySprites(Inventory *const i, Window *const w) {
	unsigned int k = asize(i->sprites);
	while(k--)
		updateSprite(aget(i->sprites, k), w);
}


unsigned int inventorySize(const Inventory *const i) {
	return asize(i->sprites);
}

Sprite *getInventorySprite(const Inventory *const i, const int n) {
	return aget(i->sprites, n);
}

unsigned int addInventorySprite(Inventory *const i, Sprite *const s) {
	const unsigned int index = aappend(i->sprites, s);
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
