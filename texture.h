#ifndef TEXTURES_H
#define TEXTURES_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include <stdbool.h>


typedef struct texture *Texture;
typedef const struct texture *CTexture;

#include "window.h"
#include "types.h"


#define TYPE_PLAIN 0
#define TYPE_IMAGE 1



/**
 * \brief Loads an image file (BitMap format) and wraps it in a SDL texture structure.
 *
 * \param filename the file to load
 * \param ren      the renderer to load the texture for
 *
 * \return a newly-loaded texture from given BMP file
 *
 * \sa SDL_Texture
 */
Texture loadbmptexa(cstr filename, CWindow win, uint32_t colorkey);
inline Texture loadbmptex(cstr filename, CWindow win) {
	return loadbmptexa(filename, win, 0);
}

/**
 * \brief Loads a color plain texture.
 *
 * FIXME: currently only fills the whole window, doesn not limit to given rect
 *        are geometry's x and y even used?
 * \param renderer the renderer to load the texture for
 * \param geometry the dimension of the texture
 * \param color    the color to give the texture
 *
 * \return a new color plain texture
 */
Texture plaintex(CWindow window, Rect geometry, Color color);


/**
 * \brief Frees a texture's memory usage.
 */
void freetexture(Texture self);


/**
 * \brief Draws a texture on screen.
 *
 * \param texture  the texture to render
 * \param renderer the renderer to render the texture to
 * \param pos      the position at which render the texture
 */
void drawtexture(Texture self, Window window, Point pos);


bool istexplain(CTexture self);

bool gettexturegeom(CTexture self, int *w, int *h);

#endif /* TEXTURES_H */
