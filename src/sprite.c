#include "sprite.h"


#include <string.h>

#include <log.h>
#include "texture.h"



struct sprite {
	Rect geom;
	Texture *tex;
	str name;
	bool needsupdate;
	padding(7);
};


Sprite *newSprite(Texture *const tex, const Point p, const str name) {
	Sprite *s = malloc(sizeof(Sprite));
	if(!s) {
		error("malloc() error in newSprite() for sprite \"%s\"", name);
		return NULL;
	}

	s->tex = tex;

	getTextureGeom(s->tex, &s->geom.w, &s->geom.h);
	s->geom.x = p.x;
	s->geom.y = p.y;

	// so that we don't call free() on s->name
	s->name = NULL;
	setSpriteName(s, name);

	// This line should preferably be last but if it is, SEGFAULT. Blame gcc
	verbose("new sprite \"%s\" instantiated", s->name);

	s->needsupdate = true;
	return s;
}

void freeSprite(Sprite *const s) {
	// we firstly copy the name of the sprite to print it
	const unsigned int l = strlen(s->name) + 1;
	char name[l];
	strcpy(name, s->name);

	// we do the real deallocation
	freeTexture(s->tex);
	free((char*)s->name);
	free(s);

	verbose("freed sprite \"%s\"", name);
}


bool spriteNeedsUpdate(const Sprite *const s) { return s->needsupdate; }

void updateSprite(Sprite *const s, Window *const win) {
	drawTexture(s->tex, win, point(s->geom.x, s->geom.y));
	s->needsupdate = false;
}


str getSpriteName(const Sprite *const s) { return s->name; }

void setSpriteName(Sprite *const s, const str name) {
	s->name = name;
}

int getSpriteX(const Sprite *const s) { return s->geom.x; }
int getSpriteY(const Sprite *const s) { return s->geom.y; }
int getSpriteW(const Sprite *const s) { return s->geom.w; }
int getSpriteH(const Sprite *const s) { return s->geom.h; }


void moveSprite(Sprite *const s, const Point to) {
	s->geom.x = to.x;
	s->geom.y = to.y;
	s->needsupdate = true;
}
extern void moveSpriteC(Sprite *s, const Point to);

void setSpriteTexture(Sprite *const s, Texture *const tex) {
	s->tex = tex;
	s->needsupdate = true;
}

bool isPointInSprite(const Sprite *const s, const Point p) {
	return isPointInRect(&p, &s->geom);
}
