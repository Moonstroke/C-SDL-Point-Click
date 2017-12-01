/**
 * \file types.h
 * \author joH1
 *
 * This file contains several definitions of types used throughout the whole
 * project.
*/

#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <SDL2/SDL.h>


/* ## SDL-related types ## */

typedef SDL_Renderer Renderer; /**< The rendering structure */
typedef SDL_RendererFlags RenderFlags;
/**< The flags used to initialize the renderer */
typedef SDL_WindowFlags WinFlags; /**< The flags to initialize the window */

typedef SDL_Color Color; /**< A RGBA color structure */

typedef SDL_Point Point; /**< A geometric point, in cartesian coordinates */

typedef SDL_Rect Rect; /**< A geometric rectangle */



/* ## Other uselful types ## */

/* TODO make sure these are useful */
typedef char *str; /**< A simple redefinition of a string */
typedef const char *cstr; /**< A redefinition for constant srings */

typedef FILE *File; /**< A redefinition of the file structure */


#endif /* TYPES_H */
