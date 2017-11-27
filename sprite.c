#include "sprite.h"


#include <stdint.h>

#include "log.h"
#include "texture.h"


#define NAME_MAX_LEN 16

struct sprite {
	SDL_Rect geom;
	Texture tex;
	char name[NAME_MAX_LEN];
	bool needsupdate;
};


Sprite newsprite(Texture tex, SDL_Point p, const str name) {
	Sprite s = malloc(sizeof(struct sprite));
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
}

void freesprite(Sprite s) {
	freetexture(s->tex);
	char name [NAME_MAX_LEN];
	strncpy(name, s->name, NAME_MAX_LEN);
	//debug("freeing Sprite %p\n", s);
	free(s);
	s = NULL;
	verbose("freed sprite \"%s\"", name);
}


bool spriteneedsupdate(const CSprite s) { return s->needsupdate; }

void updatesprite(const Sprite s, const Window win) {
	drawtexture(s->tex, win, (SDL_Point){s->geom.x, s->geom.y});
	//SDL_RenderCopy(getwindowrenderer(win), s->tex, NULL, &s->geom);
	s->needsupdate = false;
}


cstr getspritename(const CSprite s) { return s->name; }

void setspritename(Sprite s, const str name) {
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

int getspritex(const CSprite s) { return s->geom.x; }
int getspritey(const CSprite s) { return s->geom.y; }
int getspritew(const CSprite s) { return s->geom.w; }
int getspriteh(const CSprite s) { return s->geom.h; }


void movesprite(const Sprite s, const Point to) {
	s->geom.x = to.x;
	s->geom.y = to.y;
	s->needsupdate = true;
}
extern void movecsprite(Sprite s, Point to);

void setspritetexture(const Sprite s, const Texture tex) {
	s->tex = tex;
	s->needsupdate = true;
}

bool isptinsprite(const CSprite s, const Point p) {
	return SDL_PointInRect(&p, &s->geom);
}
