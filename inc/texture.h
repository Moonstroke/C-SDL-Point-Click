/**
 * \file texture.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief The textures, or graphical data (images) loaded to display sprites or
 *        e.g. a scene's background.
 *
 * This file contains the definition of the texture objects.
 */

#ifndef TEXTURES_H
#define TEXTURES_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include <stdbool.h>

#include "types.h"


/**
 * \brief The structure used to represent a texture.
 *
 * The texture can be for a sprite or the background or a scene or the inventory;
 * it consists of a loaded picture (BMP format only).
 */
typedef SDL_Texture Texture;

#include "window.h"



/**
 * \brief Loads an image file (BitMap format) and wraps it in a SDL texture
          structure.
 *
 * \param[in] fileName The file to load
 * \param[in] window   The renderer to load the texture for
 * \param[in] colorKey The colorkey used for transparency (FIXME does not work)
 *
 * \return a newly-loaded texture from given BMP file
 *
 * \sa SDL_Texture
 */
Texture *loadBMPA(str fileName, const Window *window, uint32_t colorKey);

/**
 * \brief Loads an image file (BitMap format) in a SDL texture structure,
          ignoring the color key for transparency.
 *
 * \param[in] fileName The file to load
 * \param[in] window   The renderer to load the texture for
 *
 * \return loadbmptexa(filename, win, 0)
 *
 * \sa loadbmptexa
 */
inline Texture *loadBMP(str fileName, const Window *window) {
	return loadBMPA(fileName, window, 0);
}


/**
 * \brief Frees a texture's memory usage.
 *
 * \param[in] self The texture to free
 */
void freeTexture(Texture *self);


/**
 * \brief Retrieve the geometry values of the texture: width and height.
 *
 * \param[in]  self The texture to get texture from
 * \param[out] w    The width of the texture
 * \param[out] h    The height of the texture
 *
 * \return \c true if the Texture \c self is valid and has valid geometry
 */
bool getTextureGeom(const Texture *self, int *w, int *h);


/**
 * \brief Draws a texture on screen.
 *
 * \param[in] self   The texture to render
 * \param[in] window The renderer to render the texture to
 * \param[in] pos    The position at which to render the texture
 */
void drawTexture(Texture *self, Window *window, Point pos);


#endif // TEXTURES_H
