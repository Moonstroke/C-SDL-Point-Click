/**
 * \file texture.h
 * \author joH1
 *
 * This file contains the definition of the texture objects.
 */

#ifndef TEXTURES_H
#define TEXTURES_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include <stdbool.h>

/**
 * \brief The structure used to represent a texture.
 *
 * The texture can be for a sprite or the background or a scene or the inventory;
 * it consists of either a loaded picture (BMP format only) or a color-plain
 * texture.
 */
typedef struct texture Texture;

#include "window.h"
#include "types.h"

/**
 * \enum TextureType
 *
 * \brief Constants that represent the type of a texture
 */
typedef enum {
	TYPE_PLAIN, /**< The texture is of plain color */
	TYPE_IMAGE  /**< \brief The texture is an image */
} TextureType;



/**
 * \brief Loads an image file (BitMap format) and wraps it in a SDL texture
          structure.
 *
 * \param[in] filename The file to load
 * \param[in] window   The renderer to load the texture for
 * \param[in] colorkey The colorkey used for transparency (FIXME does not work)
 *
 * \return a newly-loaded texture from given BMP file
 *
 * \sa SDL_Texture
 */
Texture *loadbmptexa(cstr filename, const Window *window, uint32_t colorkey);

/**
 * \brief Loads an image file (BitMap format) in a SDL texture structure,
          ignoring the color key for transparency.
 *
 * \param[in] filename The file to load
 * \param[in] window   The renderer to load the texture for
 *
 * \return loadbmptexa(filename, win, 0)
 *
 * \sa loadbmptexa
 */
inline Texture *loadbmptex(cstr filename, const Window *window) {
	return loadbmptexa(filename, window, 0);
}

/**
 * \brief Loads a color plain texture.
 *
 * FIXME: currently only fills the whole window, doesn not limit to given rect
 *        are geometry's x and y even used?
 * \param[in] window   the window to load the texture for
 * \param[in] geometry the dimension of the texture
 * \param[in] color    the color to give the texture
 *
 * \return a new color plain texture
 */
Texture *plaintex(const Window *window, Rect geometry, Color color);


/**
 * \brief Frees a texture's memory usage.
 *
 * \param[in] self The texture to free
 */
void freetexture(Texture *self);


/**
 * \brief Is the texture color-plain?
 *
 * \param[in] self The texture to get the nature from
 *
 * \return \c true if the texture is color-plain
 */
bool istextureplain(const Texture *self);

/**
 * \brief Is the texture color-plain?
 *
 * \param[in]  self The texture to get texture from
 * \param[out] w    The width of the texture
 * \param[out] h    The height of the texture
 *
 * \return \c true if the Texture \c self is valid
 */
bool gettexturegeom(const Texture *self, int *w, int *h);


/**
 * \brief Draws a texture on screen.
 *
 * \param[in] self   The texture to render
 * \param[in] window The renderer to render the texture to
 * \param[in] pos    The position at which to render the texture
 */
void drawtexture(Texture *self, Window *window, Point pos);


#endif /* TEXTURES_H */
