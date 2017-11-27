#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>

#include <SDL2/SDL.h>

/* ## SDL-related types ## */


typedef SDL_Renderer Renderer;
typedef SDL_RendererFlags RenderFlags;
typedef SDL_WindowFlags WinFlags;

typedef SDL_Color Color;

typedef SDL_Point Point;

typedef SDL_Rect Rect;


#define point(x, y) ((Point){(x), (y)})
#define rect(x, y, w, h) ((Rect){(x), (y), (w), (h)})


/* ## Other uselful types ## */

typedef char *str;
typedef const char *cstr;
typedef FILE *File;


#endif /* TYPES_H */
