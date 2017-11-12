#ifndef SCENE_H
#define SCENE_H


#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct scene *Scene;

#include "sprite.h"
#include "texture.h"
#include "types.h"
#include "window.h"


/**
 * \brief Instantiates a scene for n_sprites Sprites
 *
 * TIP: for better performances, load the texture with SDL_TEXTUREACCESS_STATIC, if ever
 * >>> or SDL_TEXTUREACCESS_TARGET?
 *
 * \param n_sprites		the number of sprites the scene will contain
 * \param background	the background texture for the scene
 * \param name			the name of the scene
 *
 * \return a scene
 */
Scene newscene(CRect geom, Texture background, const size_t n_sprites, const str name);

/**
 * \brief Liberates the memory used by the scene, and its contained sprites
 */
void freescene(Scene scene);

/**
 * \brief Verifies whether the scene needs to be redrawn on screen.
 * "Has it or any contained sprite changed?"
 *
 * \param scene	the scene to check for update
 *
 * \return 1 if the scene needs an update, 0 otherwise
 */
bool sceneneedsupdate(const Scene scene);

/**
 * \brief Updates the scene on screen.
 *
 * \param scene		the scene to update
 * \param renderer	the renderer to update the scene to
 */
void updatescene(Scene scene, Window window);

/**
 * \brief Retrieves the name of the scene.
 */
const str getscenename(const Scene scene);

/**
 * \brief Modifies the name of the scene.
 *
 * >>> is it really useful?
 */
void setscenename(Scene scene, const str name);

/**
 * \brief Adds a Sprite to the scene.
 * \return the index of the sprite in the scene
 */
size_t addsprite(Scene scene, Sprite sprite);

/**
 * \brief Retrieves a Sprite by its index in the scene.
 *
 * \return the  index-th Sprite of the scene
 */
Sprite getsprite(const Scene scene, const size_t index);

/**
 * \brief Retrieves a Sprite by its position on screen
 *
 * \return a Sprite from the scene that contains the given position or
 *         NULL if none does
 */
Sprite getscenespritepos(const Scene scene, CPoint point);

/**
 * \brief Remove a sprite from the scene
 *
 * \return TRUE if the scene contained the sprite and it has been succesfully
 *         removed
 */
bool removescenesprite(Scene scene, Sprite sprite);


#endif /* SCENE_H */
