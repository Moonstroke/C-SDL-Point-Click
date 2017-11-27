#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>


typedef struct sprite Sprite;

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
Sprite *newsprite(Texture *tex, Point point, str name);

/**
 * \brief Frees memory of a Sprite.
 */
void freesprite(Sprite *self);

/**
 * \brief Checks whether the sprite needs to be redrawn on screen.
 */
bool spriteneedsupdate(const Sprite *self);

/**
 * \brief Updates the Sprite.
 *
 * \param sprite	the sprite to update
 * \param ren		the renderer to update the sprite to
 */
void updatesprite(Sprite *self, Window *window);

/**
 * \brief Retrieves the name of the Sprite.
 */
cstr getspritename(const Sprite *self);

/**
 * \brief Modifies the name of the sprite.
 *
 * >>> Is really useful?
 */
void setspritename(Sprite *self, str name);

/**
 * \brief Returns the X position of the sprite.
 */
int getspritex(const Sprite *self);

/**
 * \brief Returns the Y position of the sprite.
 */
int getspritey(const Sprite *self);

/**
 * \brief Returns the width of the sprite.
 */
int getspritew(const Sprite *self);

/**
 * \brief Returns the height of the sprite.
 */
int getspriteh(const Sprite *self);


/**
 * \brief Moves the sprite to given position.
 */
void movesprite(Sprite *self, const Point to);

/**
 * \brief Moves the Sprite and centers it around given position.
 */
inline void movecsprite(Sprite *self, const Point to) {
	movesprite(self, point(to.x - getspritew(self) / 2, to.y - getspriteh(self) / 2));
}

/**
 * \brief Changes the texture of the Sprite.
 */
void setspritetexture(Sprite *self, Texture *tex);


/**
 * \brief Checks whether the point resides within the bounds of the Sprite.
 */
bool isptinsprite(const Sprite *self, Point point);


#endif /* SPRITE_H */
