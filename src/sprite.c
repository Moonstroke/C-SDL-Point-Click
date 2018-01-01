#include "sprite.h"


#include <stdint.h>

#include "log.h"
#include "texture.h"


#define NAME_MAX_LEN 16

struct sprite {
	Rect geom;
	Texture *tex;
	char name[NAME_MAX_LEN];
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
	getTextureGeom(tex, &s->geom.w, &s->geom.h);
	s->geom.x = p.x;
	s->geom.y = p.y;
	setSpriteName(s, name);
	// This line should preferably be last but if it is, SEGFAULT. Blame gcc
	verbose("new sprite \"%s\" instantiated", s->name);
	s->needsupdate = true;
	return s;
}

void freeSprite(Sprite *const s) {
	freeTexture(s->tex);
	char name [NAME_MAX_LEN];
	strncpy(name, s->name, NAME_MAX_LEN);
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
	if(name && strlen(name)) {
		int l = strlen(name) + 1;
		if(l > NAME_MAX_LEN) {
			warning("name \"%s\" is too long, will be truncated to %d chars", name, NAME_MAX_LEN);
			l = NAME_MAX_LEN;
		}
		strncpy(s->name, name, l);
	} else
		s->name[0] = '\0';
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
