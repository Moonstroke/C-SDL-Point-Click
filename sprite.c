#include "sprite.h"


#include <stdint.h>

#include "log.h"
#include "texture.h"


#define NAME_MAX_LEN 16

struct sprite {
	SDL_Rect geom;
	Texture *tex;
	char name[NAME_MAX_LEN];
	bool needsupdate;
	padding(7);
};


Sprite *newsprite(Texture *const tex, const Point p, const str name) {
	Sprite *s = malloc(sizeof(Sprite));
	if(!s) {
		error("malloc() error in newsprite() for sprite");
		return NULL;
	}
	s->tex = tex;
	gettexturegeom(tex, &s->geom.w, &s->geom.h);
	s->geom.x = p.x;
	s->geom.y = p.y;
	setspritename(s, name);
	// This line should preferably be last but if it is, SEGFAULT. Blame gcc
	verbose("new sprite \"%s\" instantiated", s->name);
	s->needsupdate = true;
	return s;
}

void freesprite(Sprite *const s) {
	freetexture(s->tex);
	char name [NAME_MAX_LEN];
	strncpy(name, s->name, NAME_MAX_LEN);
	free(s);
	verbose("freed sprite \"%s\"", name);
}


bool spriteneedsupdate(const Sprite *const s) { return s->needsupdate; }

void updatesprite(Sprite *const s, Window *const win) {
	drawtexture(s->tex, win, (SDL_Point){s->geom.x, s->geom.y});
	//SDL_RenderCopy(getwindowrenderer(win), s->tex, NULL, &s->geom);
	s->needsupdate = false;
}


str getspritename(const Sprite *const s) { return s->name; }

void setspritename(Sprite *const s, const str name) {
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

int getspritex(const Sprite *const s) { return s->geom.x; }
int getspritey(const Sprite *const s) { return s->geom.y; }
int getspritew(const Sprite *const s) { return s->geom.w; }
int getspriteh(const Sprite *const s) { return s->geom.h; }


void movesprite(Sprite *const s, const Point to) {
	s->geom.x = to.x;
	s->geom.y = to.y;
	s->needsupdate = true;
}
extern void movecsprite(Sprite *s, const Point to);

void setspritetexture(Sprite *const s, Texture *const tex) {
	s->tex = tex;
	s->needsupdate = true;
}

bool isptinsprite(const Sprite *const s, const Point p) {
	return SDL_PointInRect(&p, &s->geom);
}
