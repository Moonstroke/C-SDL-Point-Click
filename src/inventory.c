#include "inventory.h"


#include <CODS/fixedarray.h>
#include <CODS/fixedarray_funcs.h> /* for fa_put, fa_cond */
#include <clog.h>



#define SPRITE_RESERVED_SPACE 64


struct inventory {
	Rect geom;
	FixedArray *sprites;
	Texture *background;
};


Inventory *newInventory(const Rect *const g, const unsigned int n, Texture *const bg) {
	Inventory *i = malloc(sizeof(Inventory));
	if(i == NULL)
		return NULL;
	i->sprites = fa_new(n);
	i->geom = *g;
	if(bg == NULL)
		warning("Inventory has no background texture");
	i->background = bg;
	verbose("Init inventory with %u slots", n);
	return i;
}

void freeInventory(Inventory *const i) {
	fa_freer(i->sprites, (void(*)(void*))&freeSprite);
	free(i);
	verbose("freed %d sprites from inventory", fa_size(i->sprites));
}


void updateInventory(Inventory *const i, Window *const w) {
	if(i->background)
		drawTexture(i->background, w, point(i->geom.pos.x, i->geom.pos.y));
}
void updateInventorySprites(Inventory *const i, Window *const w) {
	unsigned int k = fa_size(i->sprites);
	while(k--)
		updateSprite(fa_get(i->sprites, k), w);
}


unsigned int inventorySize(const Inventory *const i) {
	return fa_size(i->sprites);
}

Sprite *getInventorySprite(const Inventory *const i, const int n) {
	return fa_get(i->sprites, n);
}

unsigned int addInventorySprite(Inventory *const i, Sprite *const s) {
	const unsigned int index = fa_put(i->sprites, s);
	Point dest = point(i->geom.pos.x + SPRITE_RESERVED_SPACE * fa_size(i->sprites) + SPRITE_RESERVED_SPACE / 2,
	                   i->geom.pos.y + SPRITE_RESERVED_SPACE / 2);
	moveSpriteC(s, dest);
	return index;
}

bool removeInventorySprite(Inventory *const i, const Sprite *const s) {
	return fa_remove(i->sprites, NULL, s);
}

static bool haspos(const void *item, const void *const pos) {
	return isPointInSprite((Sprite*)item, *(Point*)pos);
}

Sprite *getInventorySpritePos(const Inventory *const i, const Point p) {
	return fa_cond(i->sprites, haspos, &p);
}
