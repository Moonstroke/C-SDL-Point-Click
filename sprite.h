#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>


typedef struct sprite *Sprite;

#include "texture.h"
#include "window.h"
#include "types.h"



/**
 * \brief Allocates and instantiates a Sprite.
 *
 * TIP: for perf enhancements, init texture with SDL_TEXTUREACCESS_STREAMING, if ever
 *
 * \param tex	the texture of the Sprite
 * \param point	its position on screen
 * \param name	its name
 *
 * \return a newly-allocated sprite
 */
Sprite newsprite(Texture tex, DPoint point, const char *name);

/**
 * \brief Frees memory of a Sprite.
 */
void freesprite(Sprite sprite);

/**
 * \brief Checks whether the sprite needs to be redrawn on screen.
 */
Uint8 spriteneedsupdate(const Sprite sprite);

/**
 * \brief Updates the Sprite.
 *
 * \param sprite	the sprite to update
 * \param ren		the renderer to update the sprite to
 */
void updatesprite(Sprite sprite, Window window);

/**
 * \brief Retrieves the name of the Sprite.
 */
const char *getspritename(const Sprite sprite);

/**
 * \brief Modifies the name of the sprite.
 *
 * >>> Is it really useful?
 */
void setspritename(Sprite sprite, const char *name);

/**
 * \brief Returns the X position of the sprite.
 */
int getspritex(const Sprite sprite);

/**
 * \brief Returns the Y position of the sprite.
 */
int getspritey(const Sprite sprite);

/**
 * \brief Returns the width of the sprite.
 */
int getspritew(const Sprite sprite);

/**
 * \brief Returns the height of the sprite.
 */
int getspriteh(const Sprite sprite);


/**
 * \brief Moves the sprite to given position.
 */
void movesprite(Sprite sprite, CPoint dest);

/**
 * \brief Moves the Sprite and centers it around given position.
 */
void movecsprite(Sprite sprite, CPoint dest);

/**
 * \brief Changes the texture of the Sprite.
 */
void setspritetexture(Sprite sprite, Texture tex);


/**
 * \brief Checks whether the point resides within the bounds of the Sprite.
 */
int isptinsprite(const Sprite sprite, CPoint point);
#endif /* SPRITE_H */
