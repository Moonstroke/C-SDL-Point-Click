#include "scene.h"


#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "array_funcs.h"
#include "libsdl2.h"
#include <log.h>
#include "texture.h"



struct scene {
	str name;
	Array *sprites;
	Texture *background;
	Rect geom;
};


Scene *newScene(const Rect g, Texture *const tex, const unsigned int size, const str name) {
	Scene *s = malloc(sizeof(Scene));
	if(!s) {
		error("malloc() error in newScene() for scene \"%s\"", name);
		return NULL;
	}

	if(size) {
		Array *const sprites = newarray(size);
		if(sprites == NULL) {
			error("error in newScene() while creating array for %u sprites", size);
			return NULL;
		}
		s->sprites = sprites;
	} else
		s->sprites = NULL;

	// So that we don't call free() on it
	s->name = NULL;
	setSceneName(s, name);

	s->background = tex;

	s->geom = g; // TODO use it somewhere

	verbose("Init (%dx%d) scene \"%s\" with %d sprite slots", g.w, g.h, name, size);
	return s;
}

void freeScene(Scene *const s) {
	const unsigned int n = asize(s->sprites);
	const unsigned int l = strlen(s->name) + 1;
	char name[l];
	strcpy(name, s->name);

	if(s->background)
		freeTexture(s->background);
	afreer(s->sprites, (void(*)(void*))&freeSprite);
	verbose("freed %d sprites from scene\n", n);
	free((char*)s->name);
	free(s);
	verbose("freed scene \"%s\"", name);
}

bool sceneNeedsUpdate(const Scene *const s) {
	bool needsupdate = false;
	unsigned int i = s->sprites ? asize(s->sprites) : 0;
	while(i-- && !needsupdate)
		needsupdate = spriteNeedsUpdate(aget(s->sprites, i));
	return needsupdate;
}

void updateScene(Scene *const s, Window *const win) {
	if(s->background)
		drawTexture(s->background, win, point(s->geom.x, s->geom.y));
	unsigned int i = s->sprites ? asize(s->sprites) : 0;
	while(i--)
		updateSprite(aget(s->sprites, i), win);
}

str getSceneName(const Scene *const s) { return s->name; }

void setSceneName(Scene *const s, const str name) {
	s->name = name;
}

unsigned int addSprite(Scene *const s, Sprite *const sprite) {
	if(!s->sprites) {
		Array *arr = newarray(8);
		if(!arr)
			return 0;
		s->sprites = arr;
	}
	return aappend(s->sprites, sprite);
}

Sprite *getSprite(const Scene *const s, const unsigned int i) {
	return s->sprites ? aget(s->sprites, i) : NULL;
}

Sprite *getSceneSpritePos(const Scene *const s, const Point p) {
	unsigned int i = s->sprites ? asize(s->sprites) : 0;
	Sprite *sp;
	while(i--) {
		sp = aget(s->sprites, i);
		if(isPointInSprite(sp, p))
			return sp;
	}
	return NULL;
}

bool removeSceneSprite(Scene *const s, const Sprite *const sp) {
	return aremove(s->sprites, sp);
}
