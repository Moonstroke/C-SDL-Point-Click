#include "scene.h"


#include <CODS/array.h>
#include <CODS/array_funcs.h>
#include <clog.h>
#include <stdlib.h>
#include <string.h>

#include "libsdl2.h"
#include "texture.h"



struct scene {
	str name;
	Array *elements;
	Texture *background;
	Rect geom;
	bool isui;
	padding(7);
};


static Scene *newScene(const Rect g, Texture *const bg, const unsigned int n, const str name, bool isUI) {
	Scene *s = malloc(sizeof(Scene));
	if(!s) {
		error("malloc() error in newScene() for scene \"%s\"", name);
		return NULL;
	}

	if(n) {
		Array *const elts = a_new(n);
		if(elts == NULL) {
			error("error in newScene() while creating array for %u sprites", n);
			free(s);
			return NULL;
		}
		s->elements = elts;
	} else
		s->elements = NULL;

	// So that we don't call free() on it
	s->name = NULL;
	setSceneName(s, name);

	s->background = bg;

	s->geom = g; // TODO use it somewhere
	s->isui = isUI;
	verbose("Init (%dx%d) %s scene \"%s\" for %d elements", g.w, g.h, isUI ? "UI " : "game", name, n);
	return s;
}

Scene *newGameScene(const Rect g, Texture *const bg, const unsigned int n, const str name) {
	return newScene(g, bg, n, name, false);
}
Scene *newUIScene(const Rect g, Texture *const bg, const unsigned int n, const str name) {
	return newScene(g, bg, n, name, true);
}

void freeScene(Scene *const s) {
	const unsigned int n = a_size(s->elements);
	const unsigned int l = strlen(s->name) + 1;
	char name[l];
	strcpy(name, s->name);

	if(s->background)
		freeTexture(s->background);
	a_freer(s->elements, s->isui ? (void(*)(void*))freeUIElement
	                            : (void(*)(void*))freeSprite);
	verbose("freed %d sprites from scene\n", n);
	free((char*)s->name);
	free(s);
	verbose("freed scene \"%s\"", name);
}

bool sceneNeedsUpdate(const Scene *const s) {
	bool needsupdate = false;
	unsigned int i = s->elements ? a_size(s->elements) : 0;
	if(s->isui) {
		while(i-- && !needsupdate)
			needsupdate = uielementNeedsUpdate(a_get(s->elements, i));
	} else {
		while(i-- && !needsupdate)
			needsupdate = spriteNeedsUpdate(a_get(s->elements, i));
	}
	return needsupdate;
}

void updateScene(Scene *const s, Window *const w) {
	if(s->background)
		drawTexture(s->background, w, point(s->geom.pos.x, s->geom.pos.y));
}
void updateSceneElements(Scene *const s, Window *const w) {
	unsigned int i = s->elements ? a_size(s->elements) : 0;
	if(s->isui) {
		while(i--)
			updateUIElement(a_get(s->elements, i), w);
	} else {
		while(i--)
			updateSprite(a_get(s->elements, i), w);
	}
}


str getSceneName(const Scene *const s) { return s->name; }

void setSceneName(Scene *const s, const str name) {
	s->name = name;
}

bool isSceneUI(const Scene *const s) {
	return s->isui;
}


static unsigned int addSceneElt(Scene *const s, void *const e, bool isUI) {
	if(s->isui ^ isUI)
		return 0;
	if(!s->elements) {
		Array *arr = a_new(8);
		if(!arr)
			return 0;
		s->elements = arr;
	}
	return a_append(s->elements, e);
}

unsigned int addGameSceneSprite(Scene *const s, Sprite *const sp) {
	return addSceneElt(s, sp, false);
}

unsigned int addUISceneElement(Scene *s, UIElement *e) {
	return addSceneElt(s, e, true);
}


Sprite *getGameSceneSprite(const Scene *const s, const unsigned int i) {
	return s->elements ? a_get(s->elements, i) : NULL;
}


static void *getScenePos(const Scene *const s, const Point p, bool (*const contains)(const void*, Point)) {
	unsigned int i = s->elements ? a_size(s->elements) : 0;
	void *e;
	while(i--) {
		e = a_get(s->elements, i);
		if(contains(e, p)) {
			return e;
		}
	}
	return NULL;
}

Sprite *getGameSceneSpritePos(const Scene *const s, const Point p) {
	return s->isui ? NULL : getScenePos(s, p, (bool(*)(const void*, Point))isPointInSprite);
}

UIElement *getUISceneElementPos(const Scene *s, Point p) {
	return s->isui ? getScenePos(s, p, (bool(*)(const void*, Point))isPointInUIElement) : NULL;
}


bool removeGameSceneSprite(Scene *const s, const Sprite *const sp) {
	return a_remove(s->elements, sp, NULL);
}
