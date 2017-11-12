#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>

#include <SDL2/SDL.h>

/* ## SDL-related types ## */

typedef SDL_Point *Point;
typedef const SDL_Point *CPoint;
typedef SDL_Point DPoint;

typedef SDL_Rect *Rect;
typedef const SDL_Rect *CRect;
typedef SDL_Rect DRect;


#define point(x, y) ((DPoint){(x), (y)})
#define rect(x, y, w, h) ((DRect){(x), (y), (w), (h)})


/* ## Other uselful types ## */

typedef char *str;
typedef const char *cstr;
typedef FILE *File;


#endif /* TYPES_H */
