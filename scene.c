#include "scene.h"

#include <string.h>
#include "array.h"
#include "libsdl2.h"
#include "log.h"
#include "texture.h"


#define NAME_MAX_LEN 16


struct scene {
	char name[NAME_MAX_LEN];
	Array sprites;
	Texture background;
	SDL_Rect geom;
};


Scene newscene(CRect geom, Texture tex, const size_t size, const str name) {
	Scene s = malloc(sizeof(struct scene));
	if(!s) {
		error("malloc() error in newscene() for scene \"%s\"\n", name);
		return NULL;
	}
	Array sprites = newarray(size, sizeof(Sprite));
	if(sprites == NULL) {
		error("while creating array for %d sprites\n", size);
		return NULL;
	}
	setscenename(s, name);
	s->sprites = sprites;
	s->background = tex;
	s->geom = rect(geom->x, geom->y, geom->w, geom->h); // TODO use it somewhere
	verbose("Init (%dx%d) scene \"%s\" with %d sprite slots\n", geom->w, geom->h, name, size);
	return s;
}

void freescene(Scene s) {
	if(s->background)
		freetexture(s->background);
	const ushort n = arraysize(s->sprites);
	freerarray(s->sprites, (void(*)(void*))&freesprite);
	verbose("freed %d sprites\n", n);
	char name [NAME_MAX_LEN];
	strncpy(name, s->name, NAME_MAX_LEN);
	free(s);
	s = NULL;
	verbose("freed scene \"%s\"\n", name);
}

bool sceneneedsupdate(const Scene s) {
	ushort update = 0;
	ushort i = arraysize(s->sprites);
	while(i--)
		update += spriteneedsupdate(getarrayitem(s->sprites, i));
	return update;
}

void updatescene(Scene s, Window win) {
	if(s->background)
		drawtexture(s->background, win, (SDL_Point){s->geom.x, s->geom.y});
	ushort i = arraysize(s->sprites);
	while(i--)
		updatesprite(getarrayitem(s->sprites, i), win);
	renderwindow(win);
}

const str getscenename(const Scene s) { return s->name; }

void setscenename(Scene s, const str name) {
	if(name && strlen(name)) {
		int l = strlen(name) + 1;
		if(l > NAME_MAX_LEN) {
			warning("name \"%s\" is too long, will be truncated to %d chars\n", name, NAME_MAX_LEN);
			l = NAME_MAX_LEN;
		}
		strncpy(s->name, name, l);
	} else
		s->name[0] = '\0';
}

size_t addsprite(Scene s, Sprite sprite) {
	return addarrayitem(s->sprites, sprite);

}

Sprite getsprite(const Scene s, const size_t i) {
	return getarrayitem(s->sprites, i);
}

Sprite getscenespritepos(const Scene s, CPoint p) {
	size_t i = arraysize(s->sprites);
	Sprite sp;
	while(i--) {
		sp = getarrayitem(s->sprites, i);
		if(isptinsprite(sp, p))
			return sp;
	}
	return NULL;
}

bool removescenesprite(Scene s, Sprite sp) {
	return removearrayitem(s->sprites, sp) >= 0;
}
