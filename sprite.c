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


Sprite newsprite(Texture tex, SDL_Point p, const char *name) {
	Sprite s = malloc(sizeof(struct sprite));
	if(!s) {
		error("malloc() error in newsprite() for sprite\n");
		return NULL;
	}
	s->tex = tex;
	gettexturegeom(tex, &s->geom.w, &s->geom.h);
	s->geom.x = p.x;
	s->geom.y = p.y;
	setspritename(s, name);
	// This line should preferably be last but if it is, SEGFAULT. Blame gcc
	verbose("new sprite \"%s\" instantiated\n", s->name);
	s->needsupdate = 1;
}

void freesprite(Sprite s) {
	freetexture(s->tex);
	char name [NAME_MAX_LEN];
	strncpy(name, s->name, NAME_MAX_LEN);
	//debug("freeing Sprite %p\n", s);
	free(s);
	s = NULL;
	verbose("freed sprite \"%s\"\n", name);
}


uint8_t spriteneedsupdate(const Sprite s) { return s->needsupdate; }

void updatesprite(Sprite s, Window win) {
	drawtexture(s->tex, win, (SDL_Point){s->geom.x, s->geom.y});
	//SDL_RenderCopy(getwindowrenderer(win), s->tex, NULL, &s->geom);
	s->needsupdate = 0;
}


const char *getspritename(const Sprite s) { return s->name; }

void setspritename(Sprite s, const char* name) {
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

int getspritex(const Sprite s) { return s->geom.x; }
int getspritey(const Sprite s) { return s->geom.y; }
int getspritew(const Sprite s) { return s->geom.w; }
int getspriteh(const Sprite s) { return s->geom.h; }


void movesprite(Sprite s, CPoint to) {
	s->geom.x = to->x;
	s->geom.y = to->y;
	s->needsupdate = 1;
}

void movecsprite(Sprite s, CPoint to) {
	SDL_Point dest = {.x = to->x - s->geom.w / 2, .y = to->y - s->geom.h / 2};
	movesprite(s, &dest);
}

void setspritetexture(Sprite s, Texture tex) {
	s->tex = tex;
	s->needsupdate = 1;
}

int isptinsprite(const Sprite s, CPoint p) {
	return SDL_PointInRect(p, &s->geom);
}
