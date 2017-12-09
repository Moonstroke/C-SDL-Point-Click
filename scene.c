#include "scene.h"


#include <string.h>

#include "array.h"
#include "array_funcs.h"
#include "libsdl2.h"
#include "log.h"
#include "texture.h"


#define NAME_MAX_LEN 16


struct scene {
	char name[NAME_MAX_LEN];
	Array *sprites;
	Texture *background;
	Rect geom;
};


Scene *newscene(const Rect g, Texture *const tex, const size_t size, const cstr name) {
	Scene *s = malloc(sizeof(Scene));
	if(!s) {
		error("malloc() error in newscene() for scene \"%s\"", name);
		return NULL;
	}
	Array *sprites = newarray(size);
	if(sprites == NULL) {
		error("while creating array for %d sprites", size);
		return NULL;
	}
	setscenename(s, name);
	s->sprites = sprites;
	s->background = tex;
	s->geom = g; // TODO use it somewhere
	verbose("Init (%dx%d) scene \"%s\" with %d sprite slots", g.w, g.h, name, size);
	return s;
}

void freescene(Scene *const s) {
	if(s->background)
		freetexture(s->background);
	const size_t n = asize(s->sprites);
	afreer(s->sprites, (void(*)(void*))&freesprite);
	verbose("freed %d sprites from scene\n", n);
	char name[NAME_MAX_LEN];
	strncpy(name, s->name, NAME_MAX_LEN);
	free(s);
	verbose("freed scene \"%s\"", name);
}

bool sceneneedsupdate(const Scene *const s) {
	bool update = 0;
	size_t i = asize(s->sprites);
	while(--i)
		update += spriteneedsupdate(aget(s->sprites, i));
	return update;
}

void updatescene(Scene *const s, Window *const win) {
	if(s->background)
		drawtexture(s->background, win, point(s->geom.x, s->geom.y));
	size_t i = asize(s->sprites);
	while(i--)
		updatesprite(aget(s->sprites, i), win);
	renderwindow(win);
}

cstr getscenename(const Scene *const s) { return s->name; }

void setscenename(Scene *const s, const cstr name) {
	if(name && strlen(name)) {
		size_t l = strlen(name) + 1;
		if(l > NAME_MAX_LEN) {
			warning("name \"%s\" is too long, will be truncated to %d chars", name, NAME_MAX_LEN);
			l = NAME_MAX_LEN;
		}
		strncpy(s->name, name, l);
	} else
		s->name[0] = '\0';
}

size_t addsprite(Scene *const s, Sprite *const sprite) {
	return aappend(s->sprites, sprite);
}

Sprite *getsprite(const Scene *const s, const size_t i) {
	return aget(s->sprites, i);
}

Sprite *getscenespritepos(const Scene *const s, const Point p) {
	size_t i = asize(s->sprites);
	Sprite *sp;
	while(i--) {
		sp = aget(s->sprites, i);
		if(isptinsprite(sp, p))
			return sp;
	}
	return NULL;
}

bool removescenesprite(Scene *const s, const Sprite *const sp) {
	return aremove(s->sprites, sp);
}
