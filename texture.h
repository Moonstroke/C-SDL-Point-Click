#ifndef TEXTURES_H
#define TEXTURES_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include <stdbool.h>


typedef struct texture *Texture;

#include "window.h"


#define TYPE_PLAIN 0
#define TYPE_IMAGE 1



/**
 * \brief Loads an image file (BitMap format) and wraps it in a SDL texture structure.
 *
 * \param filename the file to load
 * \param ren      the renderer to load the texture for
 *
 * \return a newly-loaded texture from given BMP file
 */
#define loadbmptex(filename, win) (loadbmptexa(filename, win, 0))
Texture loadbmptexa(const char *filename, Window win, Uint32 colorkey);

/**
 * \brief Loads a color plain texture.
 *
 * FIXME: currently only fills the whole window, doesn not limit to given rect
 *        are geometry's x and y used?
 * \param renderer the renderer to load the texture for
 * \param geometry the dimension of the texture
 * \param color    the color to give the texture
 *
 * \return a new color plain texture
 */
Texture plaintex(const Window window, const SDL_Rect *geometry, const SDL_Color *color);

/**
 * \brief Draws a texture on screen.
 *
 * \param texture  the texture to render
 * \param renderer the renderer to render the texture to
 * \param pos      the position at which render the texture
 */
void drawtexture(Texture texture, Window window, const SDL_Point pos);


void freetexture(Texture texture);

bool istextureplain(const Texture texture);

bool gettexturegeom(const Texture texture, int *w, int *h);

#endif /* TEXTURES_H */
