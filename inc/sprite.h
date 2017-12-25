/**
 * \file sprite.h
 * \author joH1
 *
 * This file contains the definition of the Sprite type, that represents an
 * interactible item in the game.
*/

#ifndef SPRITE_H
#define SPRITE_H


#include "math.h"
#include "types.h"


/**
 * \brief This structure represents a game sprite (ie. an item with which the
 *        player can interact).
 */
typedef struct sprite Sprite;

#include "texture.h"
#include "window.h"



/**
 * \brief Allocates and instantiates a Sprite.
 *
 * \note for perf enhancements, init texture with SDL_TEXTUREACCESS_STREAMING, if
 * ever needed
 *
 * \param tex   The texture of the Sprite
 * \param point Its position on screen
 * \param name  Its name
 *
 * \return a newly-allocated sprite
 */
Sprite *newsprite(Texture *tex, Point point, str name);

/**
 * \brief Frees memory of a Sprite.
 *
 * \param[in] self The sprite to free
 */
void freesprite(Sprite *self);

/**
 * \brief Checks whether the sprite needs to be redrawn on screen.
 *
 * \param[in] self The sprite to check
 */
bool spriteneedsupdate(const Sprite *self);

/**
 * \brief Updates the Sprite.
 *
 * \param[in] self   the sprite to update
 * \param[in] window the renderer to update the sprite to
 */
void updatesprite(Sprite *self, Window *window);

/**
 * \brief Retrieves the name of the Sprite.
 *
 * \param[in] self The sprite to get the name from
 *
 * \return The name of the sprite
 */
str getspritename(const Sprite *self);

/**
 * \brief Modifies the name of the sprite.
 *
 * \param[in] self The sprite to update the name of
 * \param[in] name The name to give to the sprite
 */
void setspritename(Sprite *self, str name);

/**
 * \brief Returns the X position of the sprite.
 *
 * \param[in] self The sprite to retrieve X dimension from
 *
 * \return The abscissa of the sprite
 */
int getspritex(const Sprite *self);

/**
 * \brief Returns the Y position of the sprite.
 *
 * \param[in] self The sprite to retrieve Y dimension from
 *
 * \return The ordinate of the sprite
 */
int getspritey(const Sprite *self);

/**
 * \brief Returns the width of the sprite.
 *
 * \param[in] self The sprite to retrieve the width from
 *
 * \return The width of the sprite
 */
int getspritew(const Sprite *self);

/**
 * \brief Returns the height of the sprite.
 *
 * \param[in] self The sprite to retrieve the height from
 *
 * \return The height of the sprite
 */
int getspriteh(const Sprite *self);


/**
 * \brief Moves the sprite to given position.
 *
 * \param[in] self The sprite to displace
 * \param[in] to   The destination of the displacement (left-upper corner)
 */
void movesprite(Sprite *self, Point to);

/**
 * \brief Moves the sprite and centers it around given position.
 *
 * \param[in] self The sprite to displace
 * \param[in] to   The destination of the displacement (center of the sprite)
 */
inline void movecsprite(Sprite *self, Point to) {
	movesprite(self, point(to.x - getspritew(self) / 2, to.y - getspriteh(self) / 2));
}

/**
 * \brief Changes the texture of the Sprite.
 *
 * \param[in] self The sprite to set the texture to
 * \param[in] tex  The texture to set to the sprite
 */
void setspritetexture(Sprite *self, Texture *tex);


/**
 * \brief Checks whether the point resides within the bounds of the Sprite.
 *
 * \param[in] self  The sprite to check if point belongs to
 * \param[in] point The point to check if belongs in sprite
 *
 * \return \c true if the point is geometrically within the bounds of the sprite
 */
bool isptinsprite(const Sprite *self, Point point);


#endif /* SPRITE_H */
